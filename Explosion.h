/**
 * @file Explosion.h - Animation of an explosion (Firework type)
 * @author Nassuel Valera
 * @see "Seattle University, CPSC 2430, Spring 2018"
 */

#pragma once
#include "adt/Critter.h"
/**
 * @class Explosion - A shot object (that acts like a critter)
 *
 * Model/view/controller object for a Menagerie-style critter.
 *
 * The Explosion is a pixel expansion, like a firework.
 * It only expands and the rotate() and reverse() methods do nothing.
 * The rendering is an expansion of pixels, changing with the help of the 
 * constant t.
 */
class Explosion : public Critter {
public:
    Explosion(int row, int col);

    void move();
    void reverse();
    void rotate();

    void render(PixelMatrix &pxm) const;
    Critter::Direction getHeading() const;
    int getColumn() const;

    std::ostream& print(std::ostream&) const;
private:
    int r, c, t;  // Explosion location is at this (r,c) and t starts at 0
};

