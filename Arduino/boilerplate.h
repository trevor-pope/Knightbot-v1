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
