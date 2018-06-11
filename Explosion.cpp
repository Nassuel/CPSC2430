/**
 * @file Explosion.cpp - Implementation of Explosion class
 * @author Nassuel Valera
 * @see "Seattle University, CPSC 2430, Spring 2018"
 */

#include "Explosion.h"
using namespace std;

Explosion::Explosion(int row, int col) : r(row), c(col), t(0){
}

void Explosion::move() {
    t++;
}

void Explosion::reverse() {
}

void Explosion::rotate() {
}

void Explosion::render(PixelMatrix &pxm) const {
    if (t == 0)
		pxm.paint(r,c,RGB::RED);
	else if (t == 1) {
		pxm.paint(r + 1, c - 1,RGB::RED);
		pxm.paint(r + 1, c + 1,RGB::RED);
		pxm.paint(r - 1, c - 1,RGB::RED);
		pxm.paint(r - 1, c - 1,RGB::RED);
	} else if (t == 2) {
		pxm.paint(r + 2, c    ,RGB::RED);
		pxm.paint(r + 2, c + 2,RGB::RED);
		pxm.paint(r + 2, c - 2,RGB::RED);
		pxm.paint(r - 2, c    ,RGB::RED);
		pxm.paint(r - 2, c + 2,RGB::RED);
		pxm.paint(r - 2, c - 2,RGB::RED);
		pxm.paint(r    , c - 2,RGB::RED);
		pxm.paint(r    , c + 2,RGB::RED);
	} else if (t == 3) {
		pxm.paint(r - 3, c - 1,RGB::RED);
		pxm.paint(r - 1, c - 3,RGB::RED);
		pxm.paint(r + 3, c - 1,RGB::RED);
		pxm.paint(r + 1, c + 3,RGB::RED);
	}
}

Critter::Direction Explosion::getHeading() const {
    return NORTH;
}

int Explosion::getColumn() const {
    return c;
}

ostream& Explosion::print(ostream &out) const {
    return out << "Explosion(" << r << "," << c << ")";
}
