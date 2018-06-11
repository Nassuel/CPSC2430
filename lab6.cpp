/**
 * @file lab6.cpp - Tests for PQHeap
 * @author Nassuel Valera Cuevas
 * @see "Seattle University, CPSC 2430, Spring 2018"
 */
 
#include <iostream>
#include "PQHeap.h"
using namespace std;

int main() {
	PQHeap<char> heapS;
	PQHeap<int> heapI;
	
	cout << "Enqueueing values to heaps..." << endl;
	for (char i = 'a'; i != 'h'; i++) {
		heapS.enqueue(i);
		heapI.enqueue(static_cast<int>(i));
	}
	cout << "Done!" << endl;
	
	cout << "Are the heaps empty...?" << endl;
	cout << heapS.empty() << " <- is it empty test | (expect false (0))" << endl;
	cout << heapI.empty() << " <- is it empty test | (expect false (0))" << endl;
	cout << "Done!" << endl;
	
	cout << "Check values inserted" << endl;
	while(!heapS.empty()) {
		auto dat = heapS.peek();
		heapS.dequeue();
		cout << dat << " ";
	}
	cout << endl;
	
	while(!heapI.empty()) {
		auto dot = heapI.peek();
		heapI.dequeue();
		cout << dot << " ";
	}
	cout << endl;
	cout << "Done!" << endl;
	
	cout << "Are the heaps empty...?" << endl;
	cout << heapS.empty() << " <- is it empty test | (expect true (1))" << endl;
	cout << heapI.empty() << " <- is it empty test | (expect true (1))" << endl;
	cout << "Done!" << endl;
	
	cout << "Enqueueing values to heaps...yes, again" << endl;
	for (char i = 'a'; i != 'h'; i++) {
		heapS.enqueue(i);
		heapI.enqueue(static_cast<int>(i));
	}
	cout << "Done!" << endl;
	
	cout << "Are the heaps empty...?" << endl;
	cout << heapS.empty() << " <- is it empty test | (expect false (0))" << endl;
	cout << heapI.empty() << " <- is it empty test | (expect false (0))" << endl;
	
	return 0;
}
