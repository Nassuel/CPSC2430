/**
 *@file lab5.cpp - Test implementation for DictBST
 *@author Nassuel Valera Cuevas
 *@see "Seattle University CPSC2430 Spring 2018"
 */

#include <iostream>
#include "DictBST.h"
using namespace std;

struct testStruct{
    string tstr;
    int tint;  
};

int main() {
	DictBST<string, string> strSqu;
	strSqu.add("arain", "Arain");
	strSqu.add("bun","Bun");
	strSqu.add("cow","Cow");
	strSqu.add("dob","Dob");
	strSqu.add("extravagant","Extravagant");
	
	for (auto itr = strSqu.begin(); itr != strSqu.end(); ++itr) {
		string thing = *itr;
		cout << thing << " ";
	}
	cout << endl;
	
	return 0;
}