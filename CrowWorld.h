/**
 * @file RandomList.h - a class for making lists of random doubles.
 * @author Kevin Lundeen
 * @see "Seattle University, CPSC2430, Spring 2018"
 */

#pragma once
#include <string>
#include "ListA.h"

/**
 * @class CrowWorld - a class for reporting on flying between crow cousins around the world.
 *
 * Has (city, crow cousin name, latitude, longitude) for various cities based on a set of
 * data files. Can answer questions like which cousin is in a city, how far it is between 
 * any two of the known cities, and how long it takes a crow to fly between them.
 *
 * Only the 3-argument- and copy-constructors are provided.
 */
class CrowWorld {
public:
	/**
	 * Constructs a CrowWorld where the world is a given size and crows fly a certain speed.
	 *
	 * Expects four directories with the same number of entries: Cities.txt (single-word
	 * city names), Cousins.txt (single-word crow names), Longitude.txt (longitudes of 
	 * the corresponding cities), Latitude.txt (latitudes of the corresponding cities)
	 *
	 * @param radius     radius (in miles or whatever units) of the world
	 * @param speed      speed (in miles/hour or whatever units) of a crow in this world
	 * @param directory  filepath to where we can find the four data files
	 * @throws           logic_error if the files cannot be found or open or if they are
	 *                   different sizes (different number of entries)
	 * @pre              none of the throw conditions exist
	 */
	CrowWorld(double radius, double speed, std::string directory);

	// "Big five"
	CrowWorld() = delete;  // no default constructor
	~CrowWorld() = default;  // compiler-generated for the rest is fine (why?)
	CrowWorld(const CrowWorld& other) = default;
	CrowWorld(CrowWorld&& temp) = default;
	CrowWorld& operator=(const CrowWorld& other) = default;
	CrowWorld& operator=(CrowWorld&& temp) = default;

	/**
	 * Checks if the given city is in the list of cities.
	 * 
	 * @param city  city to check
	 * @return      true if the city is in the list of cities, false otherwise
	 */
	bool hasCity(std::string city) const;

	/**
	 * Gets the crow name for the crow that lives in the given city.
	 *
	 * @param city   city for which we want the cousin name
	 * @return       the name of the cousin in that city or empty string if not found
	 */
	std::string getCousin(std::string city) const;

	/**
	 * Gets the distance between the two given cities
	 * (in miles or whatever unit was implied in the construction).
	 *
	 * @param from    start city name
	 * @param to      end city name
	 * @return        distance "as the crow flies" along the great circle
	 * @throws        logic_error if either city does not exist in the data
	 * @pre           from and to are names in the Cities.txt file
	 */
	double getDistance(std::string from, std::string to) const;

	/**
	 * Gets the purported flying time for a crow between the two cities.
	 *
	 * Uses the speed of crows in this world and the distance to calculate the time.
	 * @param from    start city name
	 * @param to      end city name
	 * @return        time for a crow to fly between the two cities
	 * @throws        logic_error if either city does not exist in the data
	 * @pre           from and to are names in the Cities.txt file
	 */
	double getFlytime(std::string from, std::string to) const;

private:
	double radius;               // radius of the world
	double speed;                // speed of a crow in this world
	ListA<std::string> cities;   // list of city names
	ListA<std::string> cousins;  // list of corresponding cousins' names
	ListA<double> latitude;      // list of corresponding latitudes
	ListA<double> longitude;     // list of corresponding longitudes

	/**
	 * degrees to radians
	 * @param degrees angle in degrees
	 * @return angle in radians
	 */
	static double toRadians(double degrees);
};
