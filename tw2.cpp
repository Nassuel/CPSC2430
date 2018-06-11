/**
 * @file tw2_hints.cpp - If you're stuck on tw2.cpp, use this as a starting point
 * @author Kevin Lundeen
 * @see "Seattle University, CPSC 2430, Spring 2018"
 */

#include <iostream>
#include "Terminal.h"
#include "QueueL.h"
#include "Tower.h"
using namespace std;

/**
 * Find the spare tower.
 * @param from     not a spare
 * @param to       not a spare
 * @param towers   all towers to pick from
 * @return         tower that is not from or to
 */
Tower* spare(Tower *from, Tower *to, Tower* towers[]) {
    if (from != towers[0] && to != towers[0])
        return towers[0];
    if (from != towers[1] && to != towers[1])
        return towers[1];
    return towers[2];
}

/**
 * This is a Tower of Hanoi solution using queues. (Typical solution is to use recursion.)
 * The idea here is that we put our desired moves in a queue. If any of those moves is
 * a compound move, i.e., more than one disk, we have to decompose it into several steps.
 * For a move of N disks from tower X to tower Y, think of it as:
 *       1. Move N-1 disks from X to the spare tower, Z.
 *       2. Move 1 disk (the biggest one) from X to the goal tower, Y.
 *       3. Move the N-1 disks back from the spare tower, Z, to the goal tower, Y.
 * Of course, for move of 1 disk, we can just do it directly.
 * We start for the game with Move(start, goal, start->size()).
 *
 * So we need to keep refining each of the compound steps until they are completely decomposed
 * into single-disk steps. So here's the algorithm:
 *       1. Place initial compound move into output queue.
 *       2. Make output queue the input queue and clear the output queue.
 *       3. Go through each move on the input queue and:
 *           a. if it is a one-disk move, just move it to the output queue, else
 *           b. if it is a compound move, decompose it into three moves and place them on the output queue
 *       4. If the output queue is all one-disk moves, we're done so return it
 *       5. Otherwise there is more decomposition of moves to do so repeat starting at step 2 above
 *
 * @param a       pointer to the left tower
 * @param b       pointer to the middle tower
 * @param c       pointer to the right tower
 * @param start   pointer to the tower (a, b, or c) where the disks are now
 * @param goal    pointer to the tower (a, b, or c) where we want to move all the disks
 * @return        a queue of all the moves needed to solve the puzzle
 */
QueueL<Move> findQSolution(Tower *a, Tower *b, Tower *c, Tower *start, Tower *goal) {
    QueueL<Move> inq, outq;       // these are the input and output queue we will keep swapping
    Tower* towers[] = {a, b, c};  // the three towers--we just need this for calling spare()
    bool done = false;            // use this to keep track of when we only have 1-disk moves left

	// start with one move on the queue -- what we are trying to accomplish
    outq.enqueue(Move(start, goal, start->size()));

    while (!done) {
        // make the old output queue be the new input queue and clear the output queue
        inq = outq;
        outq.clear();
        done = true;

        // process the input queue into the output queue
        while (!inq.empty()) {
            // get the next move off the queue
            // FIXME: do some queue operations on inq here, including getting the next move, m
          Move m = inq.peek();
          inq.dequeue();
                               
            // if the move is simple, transfer to output queue, otherwise decompose it
            if (m.count == 1) {
              // FIXME: just transfer as is to output queue
              
              outq.enqueue(m);
            } else {
              Tower *other = spare(m.from, m.to, towers);
              outq.enqueue(Move(m.from, other, m.count-1));
              outq.enqueue(Move(m.from, m.to, 1));
              outq.enqueue(Move(other, m.to, m.count-1));
                // FIXME: decompose it into three steps onto output queue
                done = false;
            }
        }
    }
    return outq;
}

/**
 * Display the steps of the solution on the terminal.
 *
 * Pull the moves from the solution queue and perform the moves on the
 * actual tower data structures. Then at each step use the render method on
 * the tower objects to render the towers onto a pixel matrix which is then
 * used to paint the terminal at each step. We stop at each step and wait
 * for a user key stroke from the terminal.
 */
void animateSolution(QueueL<Move> solution, Tower *a, Tower *b, Tower *c) {
    Terminal t;
    int rows = t.getRowCount();
    int cols = t.getColCount();
    PixelMatrix pxm(rows, cols, RGB::BLACK);
    PixelMatrix pxb = pxm;
    int aplace = cols/6;
    int bplace = aplace + cols/3;
    int cplace = bplace + cols/3;
    int base = rows - 1;

    // view the game by having each tower paint their renderings
    pxm = pxb; // fresh pxm
    a->render(pxm, base, aplace);
    b->render(pxm, base, bplace);
    c->render(pxm, base, cplace);
    t.paint(pxm);
    t.getKey();  // pause (wait for any keystroke)

    while (!solution.empty()) {
        // FIXME: get the next move, m
      Move m = solution.peek();
      solution.dequeue();
        // FIXME: carry out the move on the actual towers, a, b, and c
      int disk = m.from->peek();
      m.from->pop();
      m.to->push(disk);
      // FIXME: show the result (as above before the loop)
      pxm = pxb;
      a->render(pxm, base, aplace);
      b->render(pxm, base, bplace);
      c->render(pxm, base, cplace);
      t.paint(pxm);
      t.getKey();
    }
}

/**
 * The game!
 * @return 0
 */
int main() {
    int start;
    cout << endl << "Welcome to Towers of Hanoi" << endl;
    cout << "A computer science student classic!" << endl;
    cout << "After entering the height of the game you want to play, " << endl;
    cout << "type <Enter> and then any key repeatedly until the game is done. " << endl;
    cout << "How tall? ";
    cin >> start;
    Tower a(start), b, c;

    // First solve it with a queue-based solution
    QueueL<Move> solution = findQSolution(&a, &b, &c, &a, &c);
    //cout << solution << endl;

    // Show an animation of the solution by pulling off each 1-disk move from the output queue
    animateSolution(solution, &a, &b, &c);

    return 0;
}
