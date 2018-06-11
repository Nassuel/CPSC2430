/**
 * @file Cannon.cpp - Implementation of Cannon class
 * @author Kevin Lundeen
 * @see "Seattle University, CPSC 2430, Spring 2018"
 */

#include "Cannon.h"

using namespace std;

Cannon::Cannon(int row, int col) : heading(EAST), r(row), c(col) {
}

void Cannon::move() {
    c += sign();
}

void Cannon::reverse() {
    if (heading == EAST)
        heading = WEST;
    else
        heading = EAST;
}

void Cannon::rotate() {
}

int Cannon::sign() const {
    return heading == EAST ? +1 : -1;
}

void Cannon::render(PixelMatrix &pxm) const {
    pxm.paint(r, c - 1, r, c + 1, RGB::RED);
    pxm.paint(r - 1, c, RGB::RED);
}

Critter::Direction Cannon::getHeading() const {
    return heading;
}

int Cannon::getColumn() const {
    return c;
}

ostream &Cannon::print(ostream &out) const {
    return out << "Cannon(" << r << "," << c << "," << heading << ")";
}
