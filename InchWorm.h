/**
 * @file InchWorm.h - Cody the Inch Worm!
 * @author Kevin Lundeen
 * @see "Seattle University, CPSC 2430, Spring 2018"
 */

#pragma once
#include "adt/Critter.h"
/**
 * @class InchWorm - Critter that moves like an inch worm across the screen.
 *
 * Model/view/controller object for a Menagerie-style critter.
 *
 * Rendered as a 7-pixel green and white body whose midsection oscillates
 * on each movement, propelling the hind quarters forward by two units
 * then the head forward by two units on the next move.
 */
class InchWorm : public Critter {
public:
    /**
     * InchWorm is created EASTbound and in BUNCHED state.
     *
     * @param row  initial placement of head
     * @param col  initial placement of head
     */
    InchWorm(int row, int col);

    void move();
    void reverse();
    void rotate();

    void render(PixelMatrix &pxm) const;
    Critter::Direction getHeading() const;
    int getColumn() const;

    std::ostream& print(std::ostream&) const;
private:
    /**
     * Movement state of an InchWorm.
     * STRAIGHT is all body parts in a straight line behind the head at (r,c)
     * BUNCHED  has the middle part of the body above the line of the rest and
     *          the tail pulled forward two units
     */
    enum State { STRAIGHT, BUNCHED };

    State state;
    Critter::Direction heading;
    int r, c;  // head is at this (r,c) location

    bool eastwest() const;
    int sign() const;

    /**
     * print out State
     * @param out    where to print out
     * @param state  the state, either "STRAIGHT" or "BUNCHED"
     * @return       out, at the end
     */
    friend std::ostream& operator<<(std::ostream& out, InchWorm::State state);
};

