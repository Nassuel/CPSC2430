/**
 * @file p1.cpp - driver for the menagerie game
 * @author Prof. Kevin Lundeen
 * @see "Seattle University, CPSC 2430, Spring 2018"
 */

#include "Menagerie.h"
#include "Terminal.h"

int main() {
    Terminal t(false);  // false -> don't block on keystrokes
    Menagerie game(t);
    for (int i = 0; i < 3; i++)
        game.play();
    return 0;
}