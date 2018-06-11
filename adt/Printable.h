/**
 * @file Printable.h - Allows printing of abstract base classes via the print method.
 * @author Kevin Lundeen
 * @see "Seattle University, CPSC 2430, Spring 2018"
 */

#pragma once
#include <iostream>

/**
 * @class Printable<T> - allow abstract base class with virtual method print to work
 *
 * NOTE to students: feel free to treat this as magic and ignore it!
 * We need it so we can print out a Critter without knowing at compile time
 * what kind of Critter it is. (And similar other classes.)
 * @see https://en.wikipedia.org/wiki/Curiously_recurring_template_pattern
 *
 * @tparam T the Abstract Base Class itself.
 *           Must have a print method.
 */
template <typename T>
struct Printable {
    friend std::ostream& operator<<(std::ostream &out, T const & a) { return a.print(out); }
};
