/**
 * @file lab4_test.cpp -
 * @author Kevin Lundeen
 * @see "Seattle University, CPSC2430, Spring 2018"
 */

#include <iostream>
#include "SetBST.h"
using namespace std;

SetBST<string> weeBST() {
    SetBST<string> wee;
    wee.add("gnome");
    wee.add("tom thumb");
    return wee;
}

int main() {
    SetBST<string> set;
    set.add("ant");
    set.add("bat");
    set.add("cat");
    set.add("dog");
    cout << set.has("ant") << " (expect true)" << endl;
    cout << set.has("elk") << " (expect false)" << endl;
    set.remove("ant");
    cout << set.has("ant") << " (expect false)" << endl;

    for (string animal: {"newt", "tarn", "ewe", "fox", "gnat", "mink", "rat", "sow", "vole", "hawk", "cow", "bee",
                         "lark", "ibex", "owl", "jay", "koi", "pug", "wasp", "zebra", "quail",
                         "unicorn", "yak", "xerus"})
        set.add(animal);

    // use an iterator to walk through the set
    cout << endl;
    for (SetBST<string>::const_iterator it = set.begin(); it != set.end(); ++it) {
        string animal = *it;
        cout << animal << " ";
    }
    cout << endl << "Expected above:" << endl;
    cout << "bat bee cat cow dog ewe fox gnat hawk ibex jay koi lark mink newt owl pug quail rat sow tarn unicorn vole wasp xerus yak zebra " << endl << endl;

    for (SetBST<string>::const_iterator it = set.begin("hawk"); it != set.begin("owl"); ++it) {
        string animal = *it;
        cout << animal << " ";
    }
    cout << endl << "Expected above:" << endl;
    cout << "hawk ibex jay koi lark mink newt " << endl << endl;

    SetBST<string> *pset = new SetBST<string>(set);
    pset->add("horse");
    pset->remove("lark");
    set = *pset;

    // use the range-based for loop to walk through the set
    // (this works for any class that has a begin() and end() method
    for (auto animal: *pset)
        cout << animal << " ";
    cout << endl << "Expected above:" << endl;
    cout << "bat bee cat cow dog ewe fox gnat hawk horse ibex jay koi mink newt owl pug quail rat sow tarn unicorn vole wasp xerus yak zebra " << endl << endl;
    delete pset;

    for (string animal: {"newt", "tarn", "ewe", "fox", "gnat", "mink", "rat", "sow", "vole", "hawk", "cow", "bee",
                         "unicorn", "yak", "xerus"})
        set.remove(animal);
    for (auto animal: set)
        cout << animal << " ";
    cout << endl << "Expected above:" << endl;
    cout << "bat cat dog horse ibex jay koi owl pug quail wasp zebra " << endl << endl;

    SetBST<string> testMovers(weeBST());  // test move ctor
    for (string s: testMovers)
        cout << s << endl;
    testMovers.add("sprite");
    testMovers = weeBST();  // test move op=
    for (string s: testMovers)
        cout << s << endl;

	// test moving past end
	auto itr = set.end();
	++itr;  // could throw, but nicer if it just does nothing
	// this we'd expect to throw at end(): cout << *itr << endl;

    return 0;
}
