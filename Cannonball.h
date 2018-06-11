/**
 * @file Cannonball.h - Shot from the Cannon
 * @author Kevin Lundeen
 * @see "Seattle University, CPSC 2430, Spring 2018"
 */

#pragma once
#include "adt/Critter.h"
/**
 * @class Cannonball - A shot object (that acts like a critter)
 *
 * Model/view/controller object for a Menagerie-style critter.
 *
 * The Cannonball is a 1-pixel object shot northbound from a Cannon.
 * It only moves NORTH and the rotate() and reverse() methods do nothing.
 * The rendering is a single magenta pixel.
 */
class Cannonball : public Critter {
public:
    Cannonball(int row, int col);

    void move();
    void reverse();
    void rotate();

    void render(PixelMatrix &pxm) const;
    Critter::Direction getHeading() const;
    int getColumn() const;

    std::ostream& print(std::ostream&) const;
private:
    int r, c;  // base is at this (r,c) location
};

