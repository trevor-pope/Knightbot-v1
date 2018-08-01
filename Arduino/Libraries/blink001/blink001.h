#ifndef blink001_h
#define	blink001_h


#include <expression.h>

class blink001 : public expression {
	public:
	
		blink001();
		
		void display(LedControl lc);
		
		
	private:
		
		void sweepAnim(LedControl lc);
		
		int pupil[8] = {0, 0, 24, 60, 60, 24, 0, 0};
};

#endif