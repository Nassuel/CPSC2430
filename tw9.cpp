/**
 *
 */
 
#include <iostream>
#include <algorithm>
#include "SetHash.h"
#include <cmath>
using namespace std;

class AnimalHash {
public:
	size_t operator()(const string& animal) {
		int n = animal.length();
		if (n == 0)
			return 0;
		size_t hash;
		size_t hash = static_cast<size_t>(animal[0] * 100 + animal[n/2] * 10 + animal[n - 1]);
			// Test
			//std::cout << "AnimalHash(" << bookName << ") == " << hash << std::endl;
		// size_t hash = static_cast<size_t>(animal[0] * 100 + animal[n/2] * 10 + animal[n - 1]);
		cout << "AnimalHash(" << animal << ") == " << hash << endl;
		return hash;
	}
};

int main() {
	SetHash<string,AnimalHash > set;
	//set.add("kiwi");
	//set.add("kwi");
	set.add("food");
	// cout << set.has("kiwi") << " (expect true)" << endl;
	// cout << set.has("kwi") << " (expect true)" << endl;
	// cout << set.has("koala") << " (expect false)" << endl;
	return 0;
}