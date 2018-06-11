/**
 * @file lab1.cpp - class in which the dialog with the user is implemented.
 * @author Nassuel Valera
 * @see "Seattle University, CPSC2430, Spring 2018"
 */
 
#include <iostream>
#include <string>
#include <sstream>
#include "CrowWorld.h"	// Header class
using namespace std;

int main() {
	CrowWorld w(3963.1676, 25.0, "data");	// Constructor for CrowWorld
	
	string inputFrom = "";	// variable for departure city
	string inputTo = "";	// variable for departure city
	
	// Handles the request of a departure city from the user
	while (true) {
	cout << "Where are you flying from? ";
	getline(cin, inputFrom);
	if(!w.hasCity(inputFrom))
		cout << inputFrom << " is not a place I know!" << endl;
	else 
		break;
	}
	
	// Handles the request of a destination city from the user
	while (true) {
	cout << "Where are you flying to? ";
	getline(cin, inputTo);
	if(!w.hasCity(inputTo))
		cout << inputFrom << " is not a place I know!" << endl;
	else 
		break;
	}
	
	// User dialog
	cout << "\n";
	cout << "Off to see " << w.getCousin(inputTo) << " in " + inputTo << "." << endl;
	
	cout << "From here in " << inputFrom + " that's " << w.getDistance(inputFrom,inputTo) << " miles as the crow flies." << endl;
	cout << "Being a crow that flies 25 mph, that should take you about " << w.getFlytime(inputFrom,inputTo) << " hours." << endl;
}