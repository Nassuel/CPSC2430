/**
 * @file Tower.h - tower class for the Towers of Hanoi game
 * @author Kevin Lundeen
 * @see "Seattle University, CPSC 2430, Spring 2018"
 */

#pragma once
#include <vector>
#include "adt/Stack.h"
#include "PixelMatrix.h"

/**
 * @class Tower - tower class for the Towers of Hanoi game
 *
 * Stack of int where each element is an integer representing a
 * disk of that size.
 *
 * We also need two additional methods: size and render.
 *
 * Also checks that a push is valid for the game--cannot be larger than the current top
 * or smaller than 1.
 *
 * The constructor supports setting up an intial tower with increasing size disks.
 *
 * Implemented with std::vector.
 */
class Tower : public Stack<int> {
public:
    /**
     * Constructor optionally sets up a tower of [n, n-1, n-2, ..., 1]
     * @param height the size of the largest disk in an initial stack of disks
     */
    explicit Tower(int height=0);

	// default big 5
	~Tower() = default;
	Tower(const Tower& other) = default;
	Tower& operator=(const Tower& other) = default;
	Tower(Tower&& temp) = default;
	Tower& operator=(Tower&& temp) = default;

    // usual Stack methods, except for push
    void pop();
    const int& peek() const;
    bool empty() const;
    void clear();
    std::ostream& print(std::ostream& out) const;

    /**
     * Push a disk onto the tower.
     * Verifies that the rules are being followed, i.e., that
     * the pushed disk is no larger than the top disk currently
     * on the tower.
     * @param disk size of the disk to stack on top of the tower
     * @throws     logic_error if rules would be broken
     * @pre        empty() or peek() >= disk
     * @post       peek() == disk, size() is one greater, pop() will restore previous state
     */
    void push(const int& disk);

    /**
     * Get the current number of disks on this tower.
     * @return number of disks
     */
    int size() const;

    /**
     * Paints a rendering of this tower onto the given pixel matrix.
     * @param pxm           pixel matrix to paint
     * @param baseRow       row where the bottom-most disk is placed
     * @param poleColumn    column where the pole is placed
     */
    void render(PixelMatrix &pxm, int baseRow, int poleColumn);

private:
    std::vector<int> v;
};

/**
 * @struct Move - for holding a move of one or more disks from one tower to another
 */
struct Move {
    Tower *from;
    Tower *to;
    int count;
    Move(Tower *from, Tower *to, int count) : from(from), to(to), count(count){}
};

/**
 * Print out for a move.
 * @param out    stream to print to
 * @param move   move to print
 * @return       out
 */
std::ostream& operator<<(std::ostream& out, const Move& move);
