#include <iostream>
#include "BinaryNode.h"
using namespace std;

int main() {
	BinaryNode<char> *tree;
	
	tree = new BinaryNode<char>(new BinaryNode<char>('b'), new BinaryNode<char>('c'), 'a');
	cout << tree << endl;
	cout << endl << endl << "no internal testing released yet" << endl << endl;
	BinaryNode<char>::freeNodes(tree);
	return 0;
}

