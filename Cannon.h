/**
 * @file Cannon.h - Shooter of Cannonballs
 * @author Kevin Lundeen
 * @see "Seattle University, CPSC 2430, Spring 2018"
 */

#pragma once
#include "adt/Critter.h"
/**
 * @class Cannon - A shooting object (that acts like a critter)
 *
 * Model/view/controller object for a Menagerie-style critter.
 *
 * The Cannon is the user-controlled shooter that can move along the bottom of the display.
 * It only moves EAST or WEST and the rotate() method does nothing.
 * The rendering is a red little pyramid with the idea that the top is cannon's barrel
 * always pointing NORTH.
 */
class Cannon : public Critter {
public:
    Cannon(int row, int col);

    void move();
    void reverse();
    void rotate();

    void render(PixelMatrix &pxm) const;
    Critter::Direction getHeading() const;
    int getColumn() const;

    std::ostream& print(std::ostream&) const;
private:
    Direction heading;  // EAST or WEST
    int r, c;  // base is at this (r,c) location

    int sign() const;
};

