#include "errorFace.h"

	int pupilError[8] = {195, 231, 126, 60, 60, 126, 231, 195};
	
/*
lc is the object that controls and displays the light on each matrix
direction is a boolean that is false when down and true when up
*/


/*
Constructor method ---DO NOT TOUCH----
*/

errorFace::errorFace(){

}

/*
This method is called by the Arduino in the main file. 
Make sure the text before the "::" matches the name of the file
			---DO NOT EDIT CONTENTS----
*/

void errorFace::display(LedControl lc){

	sweepAnim(lc);
	
}

/*sweepAnim() is the function that houses the instructions for the eye animation 
Make sure the text before the "::" matches the name of the file
*/

void errorFace::sweepAnim(LedControl lc){

	lc.setRow(0, 0, pupilError[0]);
	lc.setRow(0, 1, pupilError[1]);
	lc.setRow(0, 2, pupilError[2]);
	lc.setRow(0, 3, pupilError[3]);
	lc.setRow(0, 4, pupilError[4]);
	lc.setRow(0, 5, pupilError[5]);
	lc.setRow(0, 6, pupilError[6]);
	lc.setRow(0, 7, pupilError[7]);
	
	lc.setRow(1, 0, pupilError[0]);
	lc.setRow(1, 1, pupilError[1]);
	lc.setRow(1, 2, pupilError[2]);
	lc.setRow(1, 3, pupilError[3]);
	lc.setRow(1, 4, pupilError[4]);
	lc.setRow(1, 5, pupilError[5]);
	lc.setRow(1, 6, pupilError[6]);
	lc.setRow(1, 7, pupilError[7]);
}
/*


/*
displayPupil() is the function that houses the static display for each eye
Make sure the text before the "::" matches the name of the file
*/
