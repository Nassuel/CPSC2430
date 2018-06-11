/**
 * @file tw3.cpp - test class for Priority Queue
 * @author Nassuel Valera
 * @see "Seattle University, CPSC 2430, Spring 2018"
 */

#include <iostream>
#include "PQueueLL.h"
using namespace std;

int main() {
	PQueueLL<int> test;
	cout << test.empty() << " expected true" << endl;
	test.enqueue(8);
	test.enqueue(20);
	test.enqueue(3);
	cout << test << endl;
	cout << test.peek() << " expect 0" << endl;
	test.dequeue();
	
	return 0;
}