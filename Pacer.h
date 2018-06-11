/**
 * @file Pacer.h - Time keeper class for Menagerie
 * @author Kevin Lundeen
 * @see "Seattle University, CPSC 2430, Spring 2018"
 */

#pragma once
#include <chrono>
#include "adt/Critter.h"
/**
 * @class Pacer - Time keeper class for Menagerie
 *
 * Model/view/controller object for a Menagerie-style critter.
 * The Pacer critter just sits as one blue pixel in the lower-left corner and
 * doesn't move. It does however block in the move() method the guaranteed
 * delay time before it returns. Used as a slow-down piece.
 * The rotate() and reverse() methods do nothing. The reported
 * heading is always EAST.
 */
class Pacer : public Critter {
public:
    /**
     * Construct a Pacer with the given delay.
     *
     * A delay of something like 0.005 is recommended.
     * @param delay  time of delay since last move()
     */
    Pacer(double delay);

    void move();
    void reverse();
    void rotate();

    void render(PixelMatrix &pxm) const;
    Critter::Direction getHeading() const;
    int getColumn() const;

    std::ostream& print(std::ostream&) const;
private:
    double delay;  // amount of elapsed time between the returns from move() method calls
    std::chrono::time_point<std::chrono::system_clock> lasttime; // time of last move() method return
};

