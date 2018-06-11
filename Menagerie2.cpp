/**
 * @file Menagerie2.cpp - implementation of the Menagerie class (continued)
 * @author Prof. Lundeen
 * @see "Seattle University, CPSC 2430, Spring 2018"
 * @see Menagerie.cpp
 */

#include <iostream>
#include <fstream>
#include "Menagerie.h"
using namespace std;

Menagerie::Menagerie(Display &display) : eventCount(0), lastMovement(0), display(display), scene(), critters(), events(), logfile(nullptr) {
    if (LOGGING)
        logfile = new ofstream("dbug.log");
}

Menagerie::~Menagerie() {
	if (LOGGING)
		delete logfile;
    clear();
}

void Menagerie::clear() {
    for (int i = 0; i < critters.size(); i++)
        killCritter(i);
    critters.clear();
    events.clear();
}

void Menagerie::refreshDisplay() {
    display.paint(scene);
}

void Menagerie::play() {
    bool alive = true;
    resetGame();
    getRenderings();
    compositeScene();

    log("play");
    while (alive) {
        // process some events
        for (int i = 0; alive && i < EVENT_CYCLE && !events.empty(); i++)
            alive = processEvent();

        // redraw the scene
        getRenderings();
        processCollisions();
        doTurns();
        alive = compositeScene() && alive; // cannot change alive from false to true

        // get any key presses and stick them on the queue as COMMAND(keystroke)
        while (display.hasKey()) {
            int c = display.getKey();
            log(static_cast<char>(c), "keystroke");
            events.enqueue(Event(COMMAND, c));
        }
    }
    log("game over");
}

void Menagerie::getRenderings() {
    log("render");
    int n = critters.size();
    int rows = display.getRowCount();
    int cols = display.getColCount();

    // get renderings from each artifact
    pxms.clear();
    for (int i = 0; i < n; i++) {
        PixelMatrix pxm(rows, cols, RGB::TRANSPARENT);
        Critter *c = critters.get(i);
        if (c != nullptr)
            c->render(pxm);
        pxms.append(pxm);
    }
}

void Menagerie::doTurns() {
    log("turns");
    int n = critters.size();
    int rows = display.getRowCount();
    int cols = display.getColCount();
    PixelMatrix invisible(rows, cols, RGB::TRANSPARENT);

    // look for turnings
    for (int i = 0; i < n; i++) {
        Critter *c = critters.get(i);
        if (c != nullptr && pxms.get(i) == invisible) {
            bool eastbound = c->getHeading() == Critter::EAST;
            c->rotate();
            if (!eastbound)
                c->reverse();
            c->move();
            c->move();
            c->rotate();
            if (!eastbound)
                c->reverse();
            int j;
            for (j = 0; j < TURN_REVIVAL; j++) {
                c->move();
                PixelMatrix pxm = invisible;
                c->render(pxm);
                if (pxm != invisible) {
                    pxms.set(i, pxm);
                    break;
                }
            }
            if (j == TURN_REVIVAL) {
                log(*c, "lost after turn");
                killCritter(i);
            }
        }
    }
}

void Menagerie::killCritter(int i) {
    Critter *c = critters.get(i);
    delete c;
    critters.set(i, nullptr);
}

ostream& operator<<(std::ostream& out, const Menagerie::Event& event) {
    switch(event.type) {
        case Menagerie::MOVE:
            out << "MOVE-" << event.data;
            break;
        case Menagerie::COMMAND:
            out << "COMMAND-" << static_cast<char>(event.data);
            break;
        default:
            out << "???";
            break;
    }
    return out;
}

