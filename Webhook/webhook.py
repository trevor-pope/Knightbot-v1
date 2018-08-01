from flask import Flask
from flask_assistant import Assistant, ask, tell
import logging
import sys
import os
from get_office_hours import give_office_hours
from get_event_data import give_event_data
logging.getLogger('flask_assistant').setLevel(logging.DEBUG)

app = Flask(__name__)
assist = Assistant(app, '/')

#I would include the credentials file inside the same directory as this file,
#just to be safe. Google's OAuth can be a little finicky.



@assist.action('greeting')
def greet_and_start():
    speech = "Hey! What can I help you with?"
    return ask(speech)

@assist.action('get-office-hours')
def ask_for_hours(professor):
    speech = give_office_hours(professor)
    return tell(speech)

@assist.action('get-event-data')
def ask_for_event(event):
    speech = give_event_data(event)
    return tell(speech)

@assist.action('blink')
def rotate_servo():
    speech = "Blinking"
    return tell(speech)

@assist.action('rotate')
def rotate_servo():
    speech = "Rotating servo"
    return tell(speech)

@assist.action('fallback', is_fallback = True)
def confused():
    speech =  "What was that?"
    return tell(speech)




if __name__ == '__main__':
    app.run(debug=True)
