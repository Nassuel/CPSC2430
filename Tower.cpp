/**
 * @file Tower.cpp - implementation of the tower class for the Towers of Hanoi game
 * @author Kevin Lundeen
 * @see "Seattle University, CPSC 2430, Spring 2018"
 */

#include "Tower.h"
using namespace std;

Tower::Tower(int height) : v() {
    for (int i = height; i >= 1; i--)
        push(i);
}

void Tower::render(PixelMatrix &pxm, int r, int c) {
    pxm.paint(r-8, c, r, c, RGB::BLUE); // pole
    int h = r;
    for (int disk: v) {
        pxm.paint(h, c - disk, h, c + disk, RGB::GREEN);
        h--;
    }
}

int Tower::size() const {
    return static_cast<int>(v.size());
}

void Tower::pop() {
    v.pop_back();
}

void Tower::push(const int& n) {
    if (n < 1 || (!empty() && peek() < n))
        throw logic_error("illegal push onto Tower");
    v.push_back(n);
}

bool Tower::empty() const {
    return v.empty();
}

const int& Tower::peek() const {
    return v.back();
}

std::ostream& Tower::print(std::ostream &out) const {
    for (auto x: v)
        out << x << " ";
    return out;
}

void Tower::clear() {
	v.clear();
}

std::ostream& operator<<(std::ostream& out, const Move& move) {
    out << "(";
    // just show the last few hex digits of the from-Tower's address
    out << (void *)(reinterpret_cast<unsigned long>(move.from) % 0x100);
    out << ",";
    // just show the last few hex digits of the to-Tower's address
    out << (void *)(reinterpret_cast<unsigned long>(move.to) % 0x100);
    out << "," << move.count << ")";
    return out;
}
