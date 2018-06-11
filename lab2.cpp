/**
 * @file lab2.cpp - Class in which the terminal control and
 *		 			user interaction is implemented.
 * @author Nassuel Valera
 * @see "Seattle University, CPSC2430, Spring 2018"
 */
 
#include <iostream>
#include <string>
#include <sstream>
#include "InchWorm.h"	// Header class
#include "PixelMatrix.h"
#include "Terminal.h"

using namespace std;

int main() {
	Terminal t;
	InchWorm cody(10, 10);	// Constructor for InchWorm
	PixelMatrix pxm(100, 100, RGB::BLACK);
	PixelMatrix pxb = pxm;
	
	// Text to be set on the terminal
	t.setText(0,0,"CODY, THE INCH WORM");
	t.setText(3,4,"n - next move");
	t.setText(4,4,"b - reverse move");
	t.setText(5,4,"r - rotate");
	t.setText(6,4,"q - quit");
	
	while (true) {
		char letter = t.getKey();
		
		if (letter == 'n') {
			pxm = pxb;		// Refresh pxm
			cody.move();
		}
		
		if (letter == 'b') {
			pxm = pxb;		// Refresh pxm
			cody.reverse();
		}
		
		if (letter == 'r') {
			pxm = pxb;		// Refresh pxm
			cody.rotate();
		}
		
		if (letter == 'q')
			break;
		
		cody.render(pxm);
		t.paint(pxm);
	}
	
	return 0;
}