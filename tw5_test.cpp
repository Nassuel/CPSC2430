/**
 * @file tw5.cpp - 
 * @author Kevin Lundeen
 * @see "Seattle University, CPSC2430, Spring 2018"
 */

#include <iostream>
#include "BabyHuffman.h"
using namespace std;

int main() {
    /*
     * Fake up some data.
     */
    static const int N = 8;
    char characters[] = {'a',  'b',  'c', 'd', 'e',    'f', 'g', 'h'};
    int frequencies[] = {289, 2821, 9393,  98, 111, 202034,  44, 100};

    /*
     * Build the code tree, baby.root,.
     * Then print the code tree.
     */
    BabyHuffman baby;
    baby.buildCodeTree(characters, frequencies, N);
    cout << baby.root << endl;

    /*
     * Read the codes from the final Huffman code tree and place each code (recursively) into baby.codes.
     * Then print them all out.
     */
    baby.populateCodes(baby.root, Bits());
    for (int i = 0; i < N; i++)
        cout << "'" << characters[i] << "'(" << frequencies[i] << "): " << baby.codes[(unsigned)characters[i]] << endl;

    return 0;
}

