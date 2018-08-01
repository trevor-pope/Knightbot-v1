/*
Replace all instances of "boilerplate" with what you want to call the class
*/

#include "boilerplate.h"

/*
lc is the object that controls and displays the light on each matrix
direction is a boolean that is false when down and true when up
*/


/*
Constructor method 

---DO NOT TOUCH----
*/
boilerplate::boilerplate(){

}

/*
You need at least one method that is called within the main loop of the Arduino file. For this example "display()" is called in the main loop
and manipulates the Ledcontrol object
			---DO NOT EDIT CONTENTS----
*/

void boilerplate::display(LedControl lc){

	lc.setRow(0, 3, 255);
}

/*
Replace all instances of "boilerplate" with your desired class name
*/
#ifndef boilerplate_h
#define	boilderplate_h


#include <expression.h>

class boilderplate : public expression {
	
	/*
	Inside of public, define methods that will be used in the main Arduino file. For instance, display() is the method calledi in the main loop.
	It takes arguments of LedControl, iterator, and direction. You can edit how the method will work inside of the cpp file.
	*/
	public:
	
		boilderplate();
		
		void display(LedControl lc);
		
	/*
	Inside of private, define methods that will only be used inside of the cpp file. 
	*/	
	private:
	
};

#endif
