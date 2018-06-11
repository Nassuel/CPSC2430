/**
 * @file tw1.cpp - Our first teamwork project in CPSC2430
 * @author Kevin Lundeen
 * @see "Seattle University, CPSC2430, Spring 2018"
 */
#include <iostream>
#include "RandomList.h"
using namespace std;

int main() {
	RandomList list(10, -1.8, +1.8);
	cout << "mean: " << list.mean() << endl;
	cout << "whole list: [" << list << "]" << endl;
	return 0;
}

