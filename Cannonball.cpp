/**
 * @file Cannonball.cpp - Implementation of Cannonball class
 * @author Kevin Lundeen
 * @see "Seattle University, CPSC 2430, Spring 2018"
 */

#include "Cannonball.h"
using namespace std;

Cannonball::Cannonball(int row, int col) : r(row), c(col) {
}

void Cannonball::move() {
    r -= 1;
}

void Cannonball::reverse() {
}

void Cannonball::rotate() {
}

void Cannonball::render(PixelMatrix &pxm) const {
    pxm.paint(r-1, c, RGB::MAGENTA);
}

Critter::Direction Cannonball::getHeading() const {
    return NORTH;
}

int Cannonball::getColumn() const {
    return c;
}

ostream& Cannonball::print(ostream &out) const {
    return out << "Cannonball(" << r << "," << c << ")";
}
