/**
 * @file InchWorm2.cpp - Implementation of InchWorm class (continued)
 * @author Kevin Lundeen
 * @see "Seattle University, CPSC 2430, Spring 2018"
 * @see InchWorm.cpp - for some methods
 */

#include "InchWorm.h"
using namespace std;

Critter::Direction InchWorm::getHeading() const {
    return heading;
}

int InchWorm::getColumn() const {
    return c;
}

ostream& operator<<(ostream& out, InchWorm::State state)  {
    return out << (state == InchWorm::BUNCHED ? "BUNCHED" : "STRAIGHT");
}

ostream& InchWorm::print(ostream &out) const {
    return out << "InchWorm(" << r << "," << c << "," << state << "," << heading << ")";
}
