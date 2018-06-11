// Names: Nassuel Valera, Ben Gruher, Qiyu Yan

#include <iostream>
#include "CsvFile.h"
#include "DictM.h"
#include <unordered_map>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

struct PopDens {
	int pop;
	double landA, dens;
	string place;
	
	PopDens() = default;
	
	
	
	void density() {
		dens = pop / landA;
	}
	
	bool operator<(const PopDens& other) const {
		return this->dens < other.dens;
	}
};

int main() {
    CsvFile csv("data/LND01.csv");  // Land area data for each US county from US Census
	CsvFile csv1("data/DEC_10_SF2_PCT1_with_ann.csv");
	
	std::unordered_map<int, PopDens> data;
	
	std::vector<PopDens> sorted;
	
    while (!csv.eof()) {
        DictM<string, string> row = csv.next();
		PopDens popD;
		popD.landA = stod(row.get("LND110210D"));
		popD.place = row.get("Areaname");
		popD.pop = 0;
			
		data[stoi(row.get("STCOU"))] = popD;
			
        //cout << key << ": " << row.get(key) << endl;
    }
	
	while(!csv1.eof()) {
		DictM<string, string> row = csv1.next();
		if (row.get("POPGROUP.id") == "001") {
			int population = stoi(row.get("D001"));
			int name = stoi(row.get("GEO.id2"));
			
			PopDens &value = data[name];
			
			value.pop = population;
			
			value.density();
		}
	}
	
	for (auto it = data.begin(); it != data.end(); ++it) {
		PopDens pd = it->second;
		if (pd.pop > 0 && pd.landA > 0.0)
			sorted.push_back(pd);
	}
	
	sort(sorted.begin(), sorted.end());
	
	for (auto pd : sorted) 
		cout << pd.place << ": " << pd.dens << endl;
	
    return 0;
}