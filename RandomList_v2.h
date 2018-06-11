/**
 * @file RandomList_v2.h - a class for making lists of random doubles.
 * @author Kevin Lundeen
 * @see "Seattle University, CPSC2430, Spring 2018"
 */
#pragma once
#include <iostream>
#include "ListA.h"

/**
 * @class RandomList - a class for making lists of random doubles.
 *
 * Random numbers are selected during construction and cannot be subsequently
 * modified. The numbers are drawn from a uniform distribution.
 *
 * v2: added get(i) method
 *
 * Only the 3-argument- and copy-constructors are provided.
 */
class RandomList {
public:
	/**
	 * There is no default constructor, only this 3-arg version.
	 * 
	 * The random numbers are chosen from a uniform distribution from low to high.
	 * @param count  length of the list
	 * @param low    low range boundary of the uniform distribution
	 * @param high   high range boundary of the uniform distribution
	 * @throws       invalid_argument if count < 1 or low < high
	 */
	RandomList(int count, double low, double high);
	
	// "Big five"
	RandomList() = delete;  // no default constructor
	~RandomList() = default;  // compiler-generated for the rest is fine (why?)
	RandomList(const RandomList& other) = default;
	RandomList(RandomList&& temp) = default;
	RandomList& operator=(const RandomList& other) = default;
	RandomList& operator=(RandomList&& temp) = default;

	/**
	 * Get the ith element of this list.
	 *
	 * @param i  element to fetch
	 * @return   ith element
	 * @pre      i <= size()
	 */
	double get(int i) const;

	/**
	 * Calculate the average of all the values in the list.
	 * @return mean (average)
	 */
	double mean() const;

	/**
	 * Calculate the sum of all the values in the list.
	 * @return sum 
	 */
	double sum() const;

	/**
     * Number of values in the list.
     * This will be whatever the count parameter was in the construction.
     * @return number of elements
     */
	int size() const;

	/**
	 * Print all the values in the list to out.
	 *
	 * @param out  output stream to print to
	 * @return     modified output stream
	 */
	std::ostream& print(std::ostream &out) const;

private:
	ListA<double> list;  // just uses a List internally
};

/**
 * Overload for << printing.
 */
std::ostream& operator<<(std::ostream& out, const RandomList& randlist);

