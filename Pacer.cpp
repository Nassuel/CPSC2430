/**
 * @file Pacer.cpp - Implementation of Pacer class
 * @author Kevin Lundeen
 * @see "Seattle University, CPSC 2430, Spring 2018"
 */

#include <thread>
#include "Pacer.h"
using namespace std;

Pacer::Pacer(double delay) : delay(delay), lasttime(std::chrono::system_clock::now()) {
}

void Pacer::move() {
    auto curtime = std::chrono::system_clock::now();
    std::chrono::duration<double> diff = curtime - lasttime;
    int wait = static_cast<int>((delay - diff.count()) * 1000);
    if (wait > 0)
        std::this_thread::sleep_for(std::chrono::milliseconds(wait));
    lasttime = std::chrono::system_clock::now();
}

void Pacer::reverse() {
}

void Pacer::rotate() {
}

void Pacer::render(PixelMatrix &pxm) const {
    int r, c;
    pxm.getSize(r, c);
    pxm.paint(r-1, 0, RGB::BLUE);
}

Critter::Direction Pacer::getHeading() const {
    return EAST;
}

int Pacer::getColumn() const {
    return 0;
}

ostream& Pacer::print(ostream &out) const {
    return out << "Pacer(" << delay << ")";
}
