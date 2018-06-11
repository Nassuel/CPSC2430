/**
 * @file p2_test.cpp - tests for assignment p2
 * @author Jordan Boulanger
 * @see "Seattle University, CPSC2430, Spring 2018"
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include "Huffman.h"
#include "BitStreamF.h"
#include <gtest/gtest.h>
#include <stdio.h>
#include <fcntl.h>
using namespace std;

TEST(P2Tests, checkCodes) {
    int ans = open("expected.txt", O_RDWR | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
    string correct[Huffman::MAX_CHAR];
    if (!fork()) {
        dup2(ans, 1); //hijack stdout
        close(ans); //close child handle
        execl("p2key", "p2key", NULL);
    } else { //parent
        while (wait(NULL) > 0);
        close(ans);

        ifstream newAnswers;
        newAnswers.open("expected.txt");

        string line;
        int index = 0;
        while (getline(newAnswers, line)) {
            unsigned int pos = 0;
            if ((pos = line.find(": ")) != std::string::npos) {
                correct[index] = line.substr(pos + 2, string::npos);
                index++;
            }
        }
        newAnswers.close();

        string fnbook = "data/Ulysses.txt";
        string fnencoded = "data/Ulysses_encoded.dat";
        string fnbookcopy = "data/Ulysses_copy.txt";
        string fnzerosandones = "data/zerosandones.txt";

        ifstream sample(fnbook);
        Huffman huffy(sample);
        sample.close();

        index = 0;
        for (int c = 0; c <= Huffman::MAX_CHAR; c++) {
            ostringstream code_stored;
            if (!huffy.getCode(c).empty()) {
                code_stored << huffy.getCode(c);
                EXPECT_EQ(correct[index], code_stored.str());
                index++;
            }
        }
    }
}

TEST(P2Tests, checkEncoded) {
    int ans = open("expected1.txt", O_RDWR | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR); // just to supress output
    if (!fork()) {
        fflush(stdout);
        dup2(ans, 1); //hijack stdout
        close(ans);
        execl("p2key", "p2key", NULL);
    } else { //parent
        while (wait(NULL) > 0);
        close(ans);
        fflush(stdout);
        system("mv data/Ulysses_encoded.dat data/Ulysses_encodedkey.dat");

        string fnbook = "data/Ulysses.txt";
        string fnencoded = "data/Ulysses_encoded.dat";
        string fnbookcopy = "data/Ulysses_copy.txt";
        string fnzerosandones = "data/zerosandones.txt";

        ifstream sample(fnbook);
        Huffman huffy(sample);
        sample.close();

        ifstream in(fnbook);
        BitStreamF codeout;
        huffy.encode(in, codeout);

        codeout.writeToFile(fnencoded);
    }
    ans = open("expected1.txt", O_RDWR | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR); // actually using this time.
    if (!fork()) {
        fflush(stdout);
        dup2(ans, 1); //hijack stdout
        dup2(ans, 2); //hijack stderr
        close(ans); //close child handle
        execl("/bin/diff", "diff", "data/Ulysses_encodedkey.dat", "data/Ulysses_encoded.dat", NULL);
    } else { //parent
        while (wait(NULL) > 0);
        fflush(stdout);
        close(ans);

        ifstream newAnswers;
        newAnswers.open("expected1.txt");

        string line = "";
        while (getline(newAnswers, line)) {
            EXPECT_EQ(0, line.length());
        }
    }
}

TEST(P2Tests, checkCopy) {
    string fnbook = "data/Ulysses.txt";
    string fnencoded = "data/Ulysses_encoded.dat";
    string fnbookcopy = "data/Ulysses_copy.txt";
    string fnzerosandones = "data/zerosandones.txt";

    ifstream sample(fnbook);
    Huffman huffy(sample);
    sample.close();

    ifstream in(fnbook);
    BitStreamF codeout;
    huffy.encode(in, codeout);

    codeout.writeToFile(fnencoded);

    BitStreamF codein(fnencoded);
    ofstream out(fnbookcopy);
    huffy.decode(codein, out);
    out.close(); //important
    
    int ans = open("expected2.txt", O_RDWR | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
    if (!fork()) {
        fflush(stdout);
        dup2(ans, 1); //hijack stdout
        dup2(ans, 2); //hijack stderr
        close(ans); //close child handle
        execl("/bin/diff", "diff", "data/Ulysses.txt", "data/Ulysses_copy.txt", NULL);
    } else { //parent
        while (wait(NULL) > 0);
        fflush(stdout);
        close(ans);

        ifstream newAnswers;
        newAnswers.open("expected2.txt");

        string line = "";
        while (getline(newAnswers, line)) {
            EXPECT_EQ(0, line.length());
        }
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    int status = RUN_ALL_TESTS();
    if (status) {} //bypass unused variable
    remove("expected.txt");
    remove("expected1.txt");
    remove("expected2.txt");
    remove("data/Ulysses_encodedkey.dat");
}

