


#include "Head.h"
#include "Servo.h"
#include "Arduino.h"
#include <Adafruit_PWMServoDriver.h>
/*
lc is the object that controls and displays the light on each matrix
direction is a boolean that is false when down and true when up
*/


/*
Constructor method 

---DO NOT TOUCH----
*/
Head::Head(){

}

/*
You need at least one method that is called within the main loop of the Arduino file. For this example "display()" is called in the main loop
and manipulates the Ledcontrol object
			---DO NOT EDIT CONTENTS----
*/


void Head::turnRight(Servo horiz){
	horiz.write(90);
	delay(500);
	horiz.write(180);
	delay(500);
	horiz.write(90);
	delay(500);
}

void Head::turnLeft(Servo horiz){
	
	horiz.write(90);
	delay(500);
	horiz.write(0);
	delay(500);
	horiz.write(90);
	delay(500);
}


void Head::nod(Servo vertic){

	vertic.write(50);
  	delay(500);
  	vertic.write(120);
  	delay(500);
  	vertic.write(20);
  	delay(500);
  	vertic.write(120);
  	delay(500);
  	vertic.write(55);
}

void Head::shake(Servo horiz){
	
	horiz.write(40);
 	delay(500);
 	horiz.write(120);
 	delay(500); 
 	horiz.write(40);
 	delay(500);
 	horiz.write(120);
 	delay(500);
 	horiz.write(90);
}

