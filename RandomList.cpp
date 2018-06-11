/**
 * @file RandomList.cpp - implementation for RamdonList class
 * @author Nassuel Valera
 * @see "Seattle University, CPSC2430, Spring 2018"
 */
 
#include <iostream>
#include <random>
#include <ctime>
#include "RandomList.h"
using namespace std;

RandomList::RandomList(int count, double low, double high) : list() {
	if (count < 1 || low > high)
		throw invalid_argument("bad ctor args to RandomList");
	uniform_real_distribution<double> distribution(low,high);
	random_device rd;
	mt19937 generator(rd());
	for (int i = 0; i < count; i++)
		list.append(distribution(generator));
}

int RandomList::size() const {
	return list.size();
}

double RandomList::sum() const {
	double total = 0.0;
	for (int i = 0; i < size(); i++) {
		total += list.get(i);
	}
	return total;
}

double RandomList::mean() const {
	return sum() / size();
}

ostream& RandomList::print(ostream& out) const {
	return list.print(out);
}

ostream& operator<<(ostream& out, const RandomList& randlist) {
	return randlist.print(out);
}

