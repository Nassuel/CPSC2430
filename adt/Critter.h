/**
 * @file Critter.h - Critters for the menagerie!
 * @author Kevin Lundeen
 * @see "Seattle University, CPSC 2430, Spring 2018"
 */

#pragma once
#include "Printable.h"
#include "../PixelMatrix.h"

/**
 * @class Critter ADT - for menagerie game
 *
 */
class Critter : public Printable<Critter> {
public:
    /**
     * @enum Direction the critter is going
     */
    enum Direction {
        NORTH, SOUTH, EAST, WEST
    };

    /**
     * Controller to move this critter in the way they like to move.
     * (This should just adjust the data model, not the view.
     * The view is adjusted during the render method.)
     */
    virtual void move() = 0;

    /**
     * Controller to reverse the direction of this critter's future movement.
     */
    virtual void reverse() = 0;

    /**
     * Controller to rotate this critter, e.g., horizontal to vertical.
     */
    virtual void rotate() = 0;

    /**
     * View of the critter. Render the data model onto a screen. This
     * method should assume they have a transparent pixel map and they
     * paint it with the pixels that would fairly represent the critter
     * on the screen.
     *
     * @param pxm  pixel map to paint with the rendering of this critter
     */
    virtual void render(PixelMatrix &pxm) const = 0;

    /**
     * Get the current heading (which way the next move() will take this).
     *
     * @return the current heading (or EAST if this critter is immovable)
     */
    virtual Direction getHeading() const = 0;

    /**
     * Current column (x-coordinate on the display).
     *
     * @return  current column
     */
    virtual int getColumn() const = 0;

    /**
     * Print the contents to the given stream.
     *
     * Requires that T has << operator into std::ostream.
     * @param out  stream to print to
     * @return     modified output stream
     * @pre        out is writable
     * @post       out has a textual representation of Critter inserted (with <<)
     */
    virtual std::ostream& print(std::ostream& out) const = 0;

    /**
     * print out Direction
     * @param out    where to print out
     * @param state  the state, either "STRAIGHT" or "BUNCHED"
     * @return       out, at the end
     */
    friend std::ostream& operator<<(std::ostream& out, Critter::Direction d)  {
        return out << (d == Critter::WEST ? 'W' : (d == Critter::NORTH ? 'N' : (d == Critter::EAST ? 'E' : 'S')));
    }

    virtual ~Critter() {} // make the destructors virtual
};



