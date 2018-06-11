/**
 * @file InchWorm.cpp - implementation for the InchWorm class
 * @author Nassuel Valera
 * @see "Seattle University, CPSC2430, Spring 2018"
 */
 
#include <iostream>
#include "adt/Critter.h"
#include "InchWorm.h"
#include "PixelMatrix.h"
using namespace std;

InchWorm::InchWorm(int row, int col) : state(BUNCHED), heading(EAST), r(row), c(col) {
}

void InchWorm::move() {
	// East movement
	if(state == STRAIGHT) {
		state = BUNCHED;
	} else {
		state = STRAIGHT;
		if(eastwest())
			c += sign() * 2;
		else
			r += sign() * 2;
	}
}

void InchWorm::reverse() {
	if (eastwest())
		heading = (heading == EAST) ? WEST : EAST;
	else 
		heading = (heading == NORTH) ? SOUTH : NORTH;
}

void InchWorm::rotate() {
	switch(heading) {
        case NORTH:
            heading = EAST;
            break;
        case EAST:
            heading = SOUTH;
            break;
        case SOUTH:
            heading = WEST;
            break;
        case WEST:
        default:
            heading = NORTH;
            break;
	}
}

void InchWorm::render(PixelMatrix &pxm) const {
	// Bunched and Heading west display case
	if (heading == WEST && state == BUNCHED) {
		pxm.paint(r	   , c	  , RGB::WHITE); // Head
		pxm.paint(r    , c + 1, RGB::GREEN);
		pxm.paint(r - 1, c + 1, RGB::WHITE);
		pxm.paint(r - 1, c + 2, RGB::GREEN);
		pxm.paint(r - 1, c + 3, RGB::WHITE);
		pxm.paint(r    , c + 3, RGB::GREEN);
		pxm.paint(r    , c + 4, RGB::WHITE); // Tail
	}
	
	// Bunched and Heading west display case
	if (heading == WEST && state == STRAIGHT) {
		pxm.paint(r    , c    , RGB::WHITE); // Head
		pxm.paint(r    , c + 1, RGB::GREEN);
		pxm.paint(r    , c + 2, RGB::WHITE);
		pxm.paint(r    , c + 3, RGB::GREEN);
		pxm.paint(r    , c + 4, RGB::WHITE);
		pxm.paint(r    , c + 5, RGB::GREEN);
		pxm.paint(r    , c + 6, RGB::WHITE); // Tail
	}
	
	// Bunched and Heading east display case
	if (heading == EAST && state == BUNCHED) {
		pxm.paint(r	   , c	  , RGB::WHITE); // Head
		pxm.paint(r    , c - 1, RGB::GREEN);
		pxm.paint(r - 1, c - 1, RGB::WHITE);
		pxm.paint(r - 1, c - 2, RGB::GREEN);
		pxm.paint(r - 1, c - 3, RGB::WHITE);
		pxm.paint(r    , c - 3, RGB::GREEN);
		pxm.paint(r    , c - 4, RGB::WHITE); // Tail
	}
	
	// Bunched and Heading south display case
	if (heading == SOUTH && state == BUNCHED) {
		pxm.paint(r	   , c	  , RGB::WHITE); // Head
		pxm.paint(r	- 1, c    , RGB::GREEN);
		pxm.paint(r - 1, c - 1, RGB::WHITE);
		pxm.paint(r - 2, c - 1, RGB::GREEN);
		pxm.paint(r - 3, c - 1, RGB::WHITE);
		pxm.paint(r - 3, c    , RGB::GREEN);
		pxm.paint(r - 4, c    , RGB::WHITE); // Tail
	}
	
	// Bunched and Heading north display case
	if (heading == NORTH && state == BUNCHED) {
		pxm.paint(r	   , c	  , RGB::WHITE); // Head
		pxm.paint(r	+ 1, c    , RGB::GREEN);
		pxm.paint(r + 1, c - 1, RGB::WHITE);
		pxm.paint(r + 2, c - 1, RGB::GREEN);
		pxm.paint(r + 3, c - 1, RGB::WHITE);
		pxm.paint(r + 3, c    , RGB::GREEN);
		pxm.paint(r + 4, c    , RGB::WHITE); // Tail
	}
	
	// Straight and Heading north display case
	if (heading == NORTH && state == STRAIGHT) {
		pxm.paint(r	   , c	  , RGB::WHITE);  // Head
		pxm.paint(r	+ 1, c    , RGB::GREEN);
		pxm.paint(r + 2, c    , RGB::WHITE);
		pxm.paint(r + 3, c    , RGB::GREEN);
		pxm.paint(r + 4, c    , RGB::WHITE);
		pxm.paint(r + 5, c    , RGB::GREEN);
		pxm.paint(r + 6, c    , RGB::WHITE);
	}
	
	
	// Straight and Heading east display case
	if (heading == EAST && state == STRAIGHT) {
		pxm.paint(r    , c    , RGB::WHITE); // Head
		pxm.paint(r    , c - 1, RGB::GREEN);
		pxm.paint(r    , c - 2, RGB::WHITE);
		pxm.paint(r    , c - 3, RGB::GREEN);
		pxm.paint(r    , c - 4, RGB::WHITE);
		pxm.paint(r    , c - 5, RGB::GREEN);
		pxm.paint(r    , c - 6, RGB::WHITE); // Tail
	}
	
	// Straight and Heading south display case
	if (heading == SOUTH && state == STRAIGHT) {
		pxm.paint(r	   , c	  , RGB::WHITE);  // Head
		pxm.paint(r	- 1, c    , RGB::GREEN);
		pxm.paint(r - 2, c    , RGB::WHITE);
		pxm.paint(r - 3, c    , RGB::GREEN);
		pxm.paint(r - 4, c    , RGB::WHITE);
		pxm.paint(r - 5, c    , RGB::GREEN);
		pxm.paint(r - 6, c    , RGB::WHITE);
	}
}

/**
* Get the sign of the move offset.
*
* @return +1 if heading east or south, -1 if heading west or north
*/
int InchWorm::sign() const {
	return  (heading == EAST || heading == SOUTH) ? +1 : -1;
}

/**
*  Is the worm currently horizontal, i.e. going back or forth?
*
*  @return true if heading east or west
*/
bool InchWorm::eastwest() const {
    return (heading == EAST || heading == WEST);
}

