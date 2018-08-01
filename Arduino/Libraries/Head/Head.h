
/*
Replace all instances of "Head" with your desired class name
*/
#ifndef Head_h
#define	Head_h

#include <Servo.h>
#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>
class Head {
	/*
	Inside of public, define methods that will be used in the main Arduino file. For instance, display() is the method calledi in the main loop.
	It takes arguments of LedControl, iterator, and direction. You can edit how the method will work inside of the cpp file.
	*/
	public:
	
		Head();
		
		void turnRight(Servo horiz);
		
		void turnLeft(Servo horiz);
		
		void nod(Servo vertic);
		
		void shake(Servo horiz);
	/*
	Inside of private, define methods that will only be used inside of the cpp file. 
	*/	
	private:
	
};

#endif
