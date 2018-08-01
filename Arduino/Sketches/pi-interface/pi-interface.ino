
#include <Servo.h>

#include <Head.h>

#include <happyFace.h>

#include <errorFace.h>

#include <blink001.h>

#include <LedControl.h>

#define E1 10  // Enable Pin for motor 1

#define E2 11  // Enable Pin for motor 2

#define I1 8  // Control pin 1 for motor 1

#define I2 9  // Control pin 2 for motor 1

#define I3 12  // Control pin 1 for motor 2

#define I4 13  // Control pin 2 for motor 2

/*
  This arduino file was created to accept a specific input from a raspberry pi. The current interface involves receiving values between
  0 - 9 from a raspberry pi and responding according to the switch statement below.
*/
int incomingByte = 0;

int pupilBlink[8] = {255, 255, 255, 255, 255, 255, 255, 255};

int trigPin = 6;
int echoPin = 7;

int DIN = 46;
int CS = 50;
int CLK = 48;

int eye_selection = 0;
int head_selection = 0;
int wheel_selection = 0;

long randA = 0;
long randB = 0;
long randC = 0;
long randD = 0;
long randE = 0;
long randF = 0;
long randG = 0;
long randH = 0;
/*
   false = down
   true = up
*/

LedControl lc = LedControl(DIN, CLK, CS, 2);
Servo horiz = Servo();
Servo vertic = Servo();

blink001 blink1 = blink001();
happyFace happy = happyFace();
errorFace error = errorFace();
Head head = Head();

void setup() {
  // put your setup code here, to run once:

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(E1, OUTPUT);
  pinMode(E2, OUTPUT);
  pinMode(I1, OUTPUT);
  pinMode(I2, OUTPUT);
  pinMode(I3, OUTPUT);
  pinMode(I4, OUTPUT);

  lc.shutdown(0, false);
  lc.setIntensity(0, 0.1);

  lc.shutdown(1, false);
  lc.setIntensity(1, 0.1);

  horiz.attach(4);
  vertic.attach(5);

  Serial.begin(9600);
}

void loop() {

  //Checking to see if input is available
  if (Serial.available()) {

    /*
      eye_selection(), head_selection(), Serial.parseInt(), and wheel_selection() are
      being used to parse/translate the input recieved from the Rasberry Pi into useable
      values in the form: "X,X,X".
    */

    eye_selection = Serial.parseInt();
    head_selection = Serial.parseInt();
    wheel_selection = Serial.parseInt();
  }

  /*
    This switch statement is being used to intake the input values parsed from the Rasberry Pi
    and then running the various combinations of numbers to convery specific eyes, head movements, and wheel movements
  */

  switch (eye_selection) {
    case 0:

      break;

    case 1:

      blinkAnim();
      blink1.display(lc);

      break;

    case 2:

      blinkAnim();
      error.display(lc);

      break;

    case 3:

      blinkAnim();
      happy.display(lc);

      break;

    case 4:

      loadAnim();
      break;
  }

  switch (head_selection) {
    case 0:

      break;

    case 1:

      head.turnRight(horiz);
      break;

    case 2:

      head.turnLeft(horiz);
      break;

    case 3:

      head.nod(vertic);
      break;

    case 4:

      head.shake(horiz);
      break;
  }

  switch (1) {
    //Straight movement and turns right after a specific breakpoint
    case 0:
      long duration, distance;
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(1000);
      digitalWrite(trigPin, LOW);
      duration = pulseIn(echoPin, HIGH);
      distance = (duration / 2) / 29.1;
      Serial.print(distance);
      Serial.println("CM");
      delay(10);

      if ((distance <= 45)) {

        digitalWrite(E1, LOW);
        digitalWrite(E2, LOW);
        digitalWrite(E1, HIGH);
        digitalWrite(E2, HIGH);
        digitalWrite(I1, LOW);
        digitalWrite(I2, HIGH);
        digitalWrite(I3, LOW);
        digitalWrite(I4, HIGH);
      }

      else if (distance > 10) {

        digitalWrite(E1, HIGH);
        digitalWrite(E2, HIGH);
        digitalWrite(I1, LOW);
        digitalWrite(I2, HIGH);
        digitalWrite(I3, HIGH);
        digitalWrite(I4, LOW);

      }



      delay(500);
      break;
     //Stops the tracks
    case 1:
      digitalWrite(E1, HIGH);
      digitalWrite(E2, HIGH);
      digitalWrite(I1, HIGH);
      digitalWrite(I2, HIGH);
      digitalWrite(I3, HIGH);
      digitalWrite(I4, HIGH);
      break;

    //Call case 2 to move in a circle
    case 2:
      
     digitalWrite(E1, HIGH);
     digitalWrite(E2, HIGH);
     digitalWrite(I1, HIGH);
     digitalWrite(I2, LOW);
     digitalWrite(I3, HIGH);
     digitalWrite(I4, LOW);

     delay (10000); // change direction after 10 seconds

     digitalWrite(E1, LOW);
     digitalWrite(E2, LOW);
     delay(200);
   
     digitalWrite(E1, HIGH);
     digitalWrite(E2, HIGH);
     digitalWrite(I1, LOW);
     digitalWrite(I2, HIGH);
     digitalWrite(I3, HIGH);
     digitalWrite(I4, LOW);
     delay(10000);
      
     break;

    case 3:
      
      digitalWrite(E1, HIGH);
      digitalWrite(E2, HIGH);
      digitalWrite(I1, HIGH);
      digitalWrite(I2, LOW);
      digitalWrite(I3, LOW);
      digitalWrite(I4, HIGH);
      delay(10000);

      // change direction

      digitalWrite(E1, LOW);
      digitalWrite(E2, LOW);
      delay(200);

      digitalWrite(E1, HIGH);
      digitalWrite(E2, HIGH);
      digitalWrite(I1, LOW);
      digitalWrite(I2, HIGH);
      digitalWrite(I3, HIGH);
      digitalWrite(I4, LOW);
      delay(10000);

      break;

    case 4:

      break;
  }



  eye_selection = 0;
  head_selection = 0;


}

/*
  This is the code that is used for the blink animation being used in between eye transitions
*/

void blinkAnim() {

  for (int i = 7; i >= 0; i--) {

    lc.setColumn(0, i, pupilBlink[i]);
    lc.setColumn(1, i, pupilBlink[i]);
    delay(25);
  }

  delay(500);

  for (int i = 0; i <= 7; i++) {

    lc.setColumn(0, i, 0);
    lc.setColumn(1, i, 0);
    delay(2);
  }
}

void errorAnim() {
  
  for (int i = 100; i >= 0; i--) {
    randA = random(0,7);
    randB = random(0,7);
    randC = random(0,7);
    randD = random(0,7);
    randE = random(0,7);
    randF = random(0,7);
    randG = random(0,7);
    randH = random(0,7);  
    lc.setLed(0,randA,randB,true);
    lc.setLed(1,randC,randD,true);
    lc.setLed(0,randE,randF,false);
    lc.setLed(1,randG,randH,false);
    delay(15);
  }
}


void loadAnim() {
  
  for (int i = 2; i >=0; i--) {
    int m = 7;
    for (int j = 0; j <=7; j++) {

      lc.setLed(0,0,j,true);
      lc.setLed(1,0,j,true);
      lc.setLed(0,m,0,false); /* remove the m column */
      lc.setLed(1,m,0,false);
      m--;
      delay(30);
    }
    int j = 0;
    for (int k = 0; k <=7; k++){

       lc.setLed(0,k,7,true);
       lc.setLed(1,k,7,true);
       lc.setLed(0,0,j,false); /* remove the j row */
       lc.setLed(1,0,j,false);
       j++;
       delay(30);
    }
    int k = 0;
    for (int l = 7; l >=0; l--) {

       lc.setLed(0,7,l,true);
       lc.setLed(1,7,l,true);
       lc.setLed(0,k,7,false);
       lc.setLed(1,k,7,false); /*remove the k column */
       k++;
       delay(30);
    }
    int l = 7;
    for (int m = 7; m >=0; m--) {

      lc.setLed(0,m,0,true);
      lc.setLed(1,m,0,true);
      lc.setLed(0,7,l,false); 
      lc.setLed(1,7,l,false); /*remove the l row */
      l--;
      delay(30);
    }

  }

}

  






















