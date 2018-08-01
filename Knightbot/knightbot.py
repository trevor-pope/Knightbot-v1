import sys
import os
import pyaudio
import wave
import uuid
import serial
import time
import glob
import signal
import snowboydecoder
from detect_intent_audio import detect_intent_audio
sys.path.append('/home/pi/assistant-sdk-python/google-assistant-sdk/googlesamples/assistant/grpc/')
import pushtotalk
import concurrent.futures
import json
import logging
import pathlib2 as pathlib
import click
import grpc
import google.auth.transport.grpc
import google.auth.transport.requests
import google.oauth2.credentials

from google.assistant.embedded.v1alpha2 import (
    embedded_assistant_pb2,
    embedded_assistant_pb2_grpc
)

import assistant_helpers
import audio_helpers
import device_helpers

audio_sample_rate = audio_helpers.DEFAULT_AUDIO_SAMPLE_RATE
audio_sample_width = audio_helpers.DEFAULT_AUDIO_SAMPLE_WIDTH
audio_iter_size = audio_helpers.DEFAULT_AUDIO_ITER_SIZE
audio_block_size = audio_helpers.DEFAULT_AUDIO_DEVICE_BLOCK_SIZE
audio_flush_size = audio_helpers.DEFAULT_AUDIO_DEVICE_FLUSH_SIZE
api_endpoint = 'embeddedassistant.googleapis.com'
END_OF_UTTERANCE = embedded_assistant_pb2.AssistResponse.END_OF_UTTERANCE
DIALOG_FOLLOW_ON = embedded_assistant_pb2.DialogStateOut.DIALOG_FOLLOW_ON
CLOSE_MICROPHONE = embedded_assistant_pb2.DialogStateOut.CLOSE_MICROPHONE
#PLAYING = embedded_assistant_pb2.ScreenOutConfig.PLAYING     #Uncommenting may cause errors, be careful
grpc_deadline = 60 * 3 + 5

credentials = "credentials.json" #credentials.json must be in this directory
session_id = str(uuid.uuid4())
project_id = "knightbot-c9389"
device_id = "lizard"
device_model_id = "KnightbotModelID"
audio_path = "/home/pi/snowboy/examples/Python3/input.wav" #File recorded to
input_audio_file = "input.wav"
output_audio_file = "output.wav"
lang = "en-US"
model = ["Knightbot.pmdl"] #snowboy model file
mic_sensitivity=0.6        #sensitivity for hotword, higher = more sensitive. I've noticed that 0.5 will work on a good day, and .7 is too high.
interrupted = False

""" send(Eyes.Head.Wheels)

Eyes:
    0 - Off
    1 - Regular
    2 - Error
    3 - Happy
    4 - Loading

Head:

    0: Off
    1: Turn Right
    2: Turn left
    3: Nod
    4: Shake

Wheels:

    0: Straight Line
    1: Stop
    2: Circle
    3: Forward and Backward
"""


def signal_handler(signal, frame):
    global interrupted
    interrupted = True
                            #Snowboy requires the signal_handler and interrupt_callback functions
def interrupt_callback():
    global interrupted
    return interrupted

def find_ports():
    ports = glob.glob('/dev/ttyACM[0-9]*')

    res = []
    for port in ports:
        try:
            s = serial.Serial(port)
            s.close()
            res.append(port)
        except:
            pass
    return res

def send(data):
    arduinoSerialData.write(data.encode())

def play_audio_file(fname):             #taken from Snowboy

    ding_wav = wave.open(fname, 'rb')
    ding_data = ding_wav.readframes(ding_wav.getnframes())
    stream_out = audio.open(
        format=audio.get_format_from_width(ding_wav.getsampwidth()),
        channels=ding_wav.getnchannels(),
        rate=ding_wav.getframerate(), input=False, output=True)
    stream_out.start_stream()
    stream_out.write(ding_data)
    time.sleep(0.2)
    stream_out.stop_stream()
    stream_out.close()

def record():

    FORMAT = pyaudio.paInt16
    CHANNELS = 1
    RATE = 16000
    CHUNK = 6400
    RECORD_SECONDS = 3
    WAVE_OUTPUT_FILENAME = "input.wav"

    # start Recording
    stream = audio.open(format=FORMAT, channels=CHANNELS,
                    rate=RATE, input=True,
                    frames_per_buffer=CHUNK)
    print ("recording...")
    frames = []

    for i in range(0, int(RATE / CHUNK * RECORD_SECONDS)):
        data = stream.read(CHUNK)
        frames.append(data)
    print ("finished recording")


    # stop Recording
    stream.stop_stream()
    stream.close()

    waveFile = wave.open(WAVE_OUTPUT_FILENAME, 'wb')
    waveFile.setnchannels(CHANNELS)
    waveFile.setsampwidth(audio.get_sample_size(FORMAT))
    waveFile.setframerate(RATE)
    waveFile.writeframes(b''.join(frames))

    waveFile.close()


def handle_response(response):

    if response.query_result.action == "ask_for_hours":
        if response.query_result.fulfillment_text == "What is the professor?":
            send('2.4.1')
        else:
            send('3.3.1')

    if response.query_result.action == "rotate_servo":
        send('1.4.1')

    if response.query_result.action == "ask_for_event":
       send('3.3.1')

    if response.query_result.fulfillment_text == "What was that?":
        send('4.0.1')

        #Setup audio for GoogleAssistant API
        audio_source = audio_helpers.WaveSource(
            open(input_audio_file, 'rb'),sample_rate=audio_sample_rate,sample_width=audio_sample_width)
        audio_sink = audio_helpers.WaveSink(
            open(output_audio_file, 'wb'),sample_rate=audio_sample_rate,sample_width=audio_sample_width)
        conversation_stream = audio_helpers.ConversationStream(
            source=audio_source,sink=audio_sink,iter_size=audio_iter_size,sample_width=audio_sample_width)
        #Create Assistant object from pushtotalk.py
        KnightAssistant = pushtotalk.SampleAssistant(lang, device_model_id, device_id,
                                     conversation_stream, grpc_channel, grpc_deadline, device_handler)
        KnightAssistant.assist()      #Run the assistant
        send('1.0.3')
        play_audio_file('output.wav') #Play response
        listen()
    else:   #For some reason this else statement is always called, even though it shouldn't be. I wouldn't change it
        os.system("./simple_google_tts en \"" + response.query_result.fulfillment_text + "\"")
        send('1.0.3')
        listen()


def listen():
    print("Listening...")
    play_audio_file("dong.wav")       #The detector object below is what snowboy uses to detect the keyword
    detector.start(detected_callback=detector.terminate,
                   interrupt_check=interrupt_callback,
                   sleep_time=.03)
    send('1.0.1')
    play_audio_file("ding.wav")
    record()
    response = detect_intent_audio(project_id,session_id,audio_path,lang)
    handle_response(response)


if __name__ == "__main__":

    logging.basicConfig(level=logging.DEBUG)
    p = find_ports()
    arduinoSerialData = serial.Serial(p[0], 9600)
    os.system("export GOOGLE_APPLICATION_CREDENTIALS='/home/pi/Knightbot-233e2659a37a.json'")
    #Setup for the Google Assistant API
    with open(credentials, 'r') as f:                                #Grab those Credentials (must be in this directory)
            credentials = google.oauth2.credentials.Credentials(token=None, **json.load(f))
            http_request = google.auth.transport.requests.Request()
            credentials.refresh(http_request)
    grpc_channel = google.auth.transport.grpc.secure_authorized_channel(  #Request a grpc channel with those Credentials
            credentials, http_request, api_endpoint)
    logging.info('Connecting to %s', api_endpoint)
    device_handler = device_helpers.DeviceRequestHandler(device_id)

    audio = pyaudio.PyAudio()
    play_audio_file("startup.wav")
    signal.signal(signal.SIGINT, signal_handler)
    detector = snowboydecoder.HotwordDetector(model,sensitivity=mic_sensitivity)
    send('1.0.0')
    listen()
