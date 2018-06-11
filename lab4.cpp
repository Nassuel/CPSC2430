/**
 * @file lab4.cpp - Test class for SetBST
 * @author Nassuel Valera Cuevas
 * @see "Seattle University, CPSC2430, Spring 2018"
 */
 
 #include <iostream>
 #include "SetBST.h"
 using namespace std;
 
 int main() {
    SetBST<int> nums;
	SetBST<double> dubs;
	SetBST<string> strs;
	
	nums.add(9);
	nums.add(5);
	nums.add(25);
	nums.add(1);
	nums.add(7);
	nums.add(4);
	
	dubs.add(9.2);
	dubs.add(5.7);
	dubs.add(25.9);
	dubs.add(1.1);
	dubs.add(7.5);
	dubs.add(4.2654);
	
	strs.add("Piotr");
	strs.add("James");
	strs.add("Jhonnattan");
	strs.add("Ryan");
	strs.add("Frederic");
	strs.add("Forrest");
	
	for (auto num : nums)
		cout << num << endl;
	
	for (auto dub : dubs)
		cout << dub << endl;
	
	for (auto str : strs)
		cout << str << endl;
 }