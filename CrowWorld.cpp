/**
 * @file CrowWorld.cpp - implementation for CrowWorld class.
 * @author Nassuel Valera
 * @see "Seattle University, CPSC2430, Spring 2018"
 */
 
#include <iostream>
#include "CrowWorld.h"	// Header Class
#include <cmath>		// Trig Functions
#include <stdlib.h>     // abs
#include <fstream>		// Open/Read files
using namespace std;

#define PI 3.14159265	// Pi value used to calculate from Degrees to Radians

CrowWorld::CrowWorld(double radius, double speed, std::string directory) {
	// Assigning values
	this->radius = radius;
	this->speed = speed;
	
	// File Reading and List Loading for the Data used (Files located in data folder)
	ifstream fcities(directory + "/Cities.txt");
	if(!fcities.is_open())
		throw logic_error(string("cannot open ") + directory + "/Cities.txt");
	string city;
	while(!fcities.eof()) {
		fcities >> city;
		cities.append(city);
	}
	fcities.close();
	
	ifstream fcousins(directory + "/Cousins.txt");
	if(!fcousins.is_open())
		throw logic_error(string("cannot open ") + directory + "/Cousins.txt");
	string cousin;
	while(!fcousins.eof()) {
		fcousins >> cousin;
		cousins.append(cousin);
	}
	fcousins.close();
	
	ifstream flatitudes(directory + "/Latitude.txt");
	if(!flatitudes.is_open())
		throw logic_error(string("cannot open ") + directory + "/Cousins.txt");
	double lat;
	while(!flatitudes.eof()) {
		flatitudes >> lat;
		latitude.append(lat);
	}
	flatitudes.close();
	
	ifstream flongitudes(directory + "/Longitude.txt");
	if(!flongitudes.is_open())
		throw logic_error(string("cannot open ") + directory + "/Longitude.txt");
	double lon;
	while(!flongitudes.eof()) {
		flongitudes >> lon;
		longitude.append(lon);
	}
	flongitudes.close();
	
	// Special case involving the constructor constants
	if(speed < 0 || radius < 0)
		throw invalid_argument("bad ctor args to CrowWorld");
}

bool CrowWorld::hasCity(std::string city) const {
	for(int i = 0; i < cities.size(); i++) {
		if (cities.get(i) == city)
			return true;
	}
	return false;
}

std::string CrowWorld::getCousin(std::string city) const {
	for(int i = 0; i < cities.size(); i++) {
		if (cities.get(i) == city)
			return cousins.get(i);
	}
	return "";
}

/**
* page referenced to find the distance equation: https://en.wikipedia.org/wiki/Great-circle_distance
*/
double CrowWorld::getDistance(std::string from, std::string to) const {
	if (hasCity(from) && hasCity(to)) {
		double latFrom = 0;
		double lonFrom = 0;
		double latTo = 0;
		double lonTo = 0;
		double delSigma = 0;
		for(int i = 0; i < cities.size(); i++) {
			if (cities.get(i) == from) {
				latFrom = latitude.get(i);
				lonFrom = longitude.get(i);
			}
			if (cities.get(i) == to) {
				latTo = latitude.get(i);
				lonTo = longitude.get(i);
			}
		}
		delSigma = acos(sin(toRadians(latFrom)) * sin(toRadians(latTo)) + cos(toRadians(latFrom)) * cos(toRadians(latTo)) * cos(toRadians(abs(lonTo - lonFrom))));
		return radius * delSigma;
	} else {
		if (!hasCity(from))
			throw logic_error(from + " does not exist in the data");
		else
			throw logic_error(to + " does not exist in the data");
	}
}

double CrowWorld::getFlytime(std::string from, std::string to) const {
	if (hasCity(from) || hasCity(to)) {
		return 1/speed * getDistance(from,to);
	} else {
		throw logic_error("City does not exist in the data");
	}
}

double CrowWorld::toRadians(double degrees) {
	return degrees * PI/180;
}