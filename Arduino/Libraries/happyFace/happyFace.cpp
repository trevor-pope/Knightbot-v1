
#include "happyFace.h"

	int pupil[8] = {254, 129, 129, 129, 157, 157, 157, 254};

/*
lc is the object that controls and displays the light on each matrix
direction is a boolean that is false when down and true when up
*/

/*
Constructor method ---DO NOT TOUCH----
*/

happyFace::happyFace(){

}

/*
This method is called by the Arduino in the main file. 
Make sure the text before the "::" matches the name of the file
			---DO NOT EDIT CONTENTS----
*/

void happyFace::display(LedControl lc){

	displayPupil(lc);
	
}

/*
displayPupil() is the function that houses the static display for each eye
Make sure the text before the "::" matches the name of the file
*/

void happyFace::displayPupil(LedControl lc){
  
  //First Eye
   
  lc.setRow(0, 0, pupil[0]);
  lc.setRow(0, 1, pupil[1]);
  lc.setRow(0, 2, pupil[2]);
  lc.setRow(0, 3, pupil[3]);
  lc.setRow(0, 4, pupil[4]);
  lc.setRow(0, 5, pupil[5]);
  lc.setRow(0, 6, pupil[6]);
  lc.setRow(0, 7, pupil[7]);
  
  
  //Second Eye
  lc.setRow(1, 0, pupil[0]);
  lc.setRow(1, 1, pupil[1]);
  lc.setRow(1, 2, pupil[2]);
  lc.setRow(1, 3, pupil[3]);
  lc.setRow(1, 4, pupil[4]);
  lc.setRow(1, 5, pupil[5]);
  lc.setRow(1, 6, pupil[6]);
  lc.setRow(1, 7, pupil[7]);
  
}