/**
 * @file Huffman.cpp - Implementation of Huffman.h
 * @author Nassuel Valera Cuevas
 * @see "Seattle University, CPSC2430, Spring 2018"
 */
 
#include "Huffman.h"
#include "PQueueLL.h"
#include "Bits.h"
using namespace std;

// Public methods
Huffman::Huffman(std::istream &sampleSource) {
	sample(sampleSource);
}

Huffman::~Huffman() {
	clear();
}

void Huffman::encode(std::istream& source, BitStream& codedOutput) const {
	int c = source.get();
	while (c != 00) {
		Bits bits = codes[to_unsigned(c)];
		codedOutput << bits;
		c = source.get();
	}
}

void Huffman::decode(BitStream& codedInput, std::ostream& out) const {
	while (!codedInput.empty()) {
		unsigned char c;
		if (translateCode(codedInput, c, false))
			throw invalid_argument(codedInput.empty() ? "unexpected end of bit stream" : "invalid code detected");
	}
}

Bits Huffman::getCode(unsigned char c) const {
	return codes[to_unsigned(c)];
}

int Huffman::getFrequency(unsigned char c) const {
	return samplecount[to_unsigned(c)];
}

// Struct Methods
Huffman::PQEntry::PQEntry(int freq, unsigned char c) : frequency(freq), codeTree(new CodeTree(c)) {}

Huffman::PQEntry::PQEntry(int combinedFrequency, CodeTree *lessFrequent, CodeTree *moreFrequent) : frequency(combinedFrequency), codeTree(new CodeTree(lessFrequent, moreFrequent, '*')) {}

// Private Methods
void Huffman::sample(std::istream &sampleSource) {
	clear();
	collectFrequencies(sampleSource);
	buildCodeTree();
	populateCodes(root, Bits());
}

bool Huffman::translateCode(BitStream &code, unsigned char &c, bool mustUseItAll) const {
	// Could not figure out the syntax for this (will look at solution)
	return false;
}

void Huffman::collectFrequencies(std::istream &sampleSource) {
	char c;
	while(c != EOF) {
        c =  sampleSource.get();
        unsigned char ch = to_unsigned(c);
        samplecount[ch] += 1;
    }

}

void Huffman::buildCodeTree() {
	PQueueLL<PQEntry*> queue;
	PQEntry *tree;
	
	for(int i = 0; i <= MAX_CHAR; i++) {
		unsigned char c = i;
		tree = new PQEntry(samplecount[i], c);
		queue.enqueue(tree);
	}
	
	while (1) {

		PQEntry *left = queue.peek();
        queue.dequeue();
		
		PQEntry *right;

        if (!queue.empty()) {
            right = queue.peek();
            queue.dequeue();
        } else {
            break;
        }
		
		tree = new PQEntry(left->frequency + right->frequency, left->codeTree, right->codeTree);
		
        queue.enqueue(tree);
    }
	
	this->root = tree->codeTree;
}

void Huffman::populateCodes(CodeTree *node, Bits code) {
	if (node->isLeaf()) {
		codes[(unsigned)node->data] = code;
	} else {
		Bits leftcode = code;
		leftcode.enqueue(0);
		populateCodes(node->left, leftcode);
		
		Bits rightcode = code;
		rightcode.enqueue(1);
		populateCodes(node->right, rightcode);
	}
}

void Huffman::clear() {
	CodeTree::freeNodes(this->root);
}

