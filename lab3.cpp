/**
 * @file lab3.cpp - Lab 3 Implementation using Binary Tree ADT.
 * @author Nassuel Valera
 * @see "Seattle University, CPSC 2430, Spring 2018"
 */

#include <iostream>
#include "QueueL.h"
#include "BinaryNode.h"
using namespace std;

int main() {
	BinaryNode<char>* tree;
	QueueL<BinaryNode<char>*> queue;
	
	for(char i = 'a'; i <= 'h'; i++) {
		tree = new BinaryNode<char>(i);
		queue.enqueue(tree);
	}
	
	while (1) {
		BinaryNode<char> *left = queue.peek();
		queue.dequeue();
		
		BinaryNode<char> *right = queue.peek();
		
		// Logic for when to stop the while loop
		if (!queue.empty()) {
			queue.dequeue();
		} else {
			break;
		}
		
		tree = new BinaryNode<char>(left,right,'*');
				
		queue.enqueue(tree);
	}
	
	cout << tree << endl;
	BinaryNode<char>::freeNodes(tree);
	return 0;
}