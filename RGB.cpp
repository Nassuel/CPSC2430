/**
 * @file RGB.cpp - implementation for RBG class
 * @author Kevin Lundeen
 * @see "Seattle Univeristy, CPSC 2430, Spring 2018"
 */

#include "RGB.h"

/**
 * These are the definitions for the pre-built objects for common colors.
 */
const RGB RGB::BLACK(0, 0, 0);
const RGB RGB::WHITE(255, 255, 255);
const RGB RGB::RED(255, 0, 0);
const RGB RGB::GREEN(0, 255, 0);
const RGB RGB::BLUE(0, 0, 255);
const RGB RGB::YELLOW(255, 255, 0);
const RGB RGB::CYAN(0, 255, 255);
const RGB RGB::MAGENTA(255, 0, 255);
const RGB RGB::TRANSPARENT;

RGB::RGB() : transparent(true), red(255), green(255), blue(255) {
}

RGB::RGB(unsigned char red, unsigned char green, unsigned char blue)
        : transparent(false), red(red), green(green), blue(blue) {
}

int RGB::bestMatch(const ListA<RGB> &setcolors) const {
    if (setcolors.size() <= 0)
        return -1;
    int best = 0;
    int rd = red - setcolors.get(best).red;
    int gd = green - setcolors.get(best).green;
    int bd = blue - setcolors.get(best).blue;
    int bestd = rd*rd + gd*gd + bd*bd;
    for (int i = 1; i < setcolors.size(); i++) {
        rd = red - setcolors.get(i).red;
        gd = green - setcolors.get(i).green;
        bd = blue - setcolors.get(i).blue;
        int dsq = rd*rd + gd*gd + bd*bd;
        if (dsq < bestd) {
            best = i;
            bestd = dsq;
        }
    }
    return best;
}

std::ostream& operator<<(std::ostream &out, RGB rgb) {
    out << "(r" << static_cast<int>(rgb.red);
    out << ",g" << static_cast<int>(rgb.green);
    out << ",b" << static_cast<int>(rgb.blue) << ")";
    return out;
}