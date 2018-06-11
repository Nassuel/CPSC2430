/**
 * @file p4_test.cpp - Project 3, The Concordance using hash tables
 * @author Jordan Boulanger
 * @see "Seattle University, CPSC2430, Spring 2018"
 */

#include "ConcordanceApp4.h"
#include <gtest/gtest.h>

using namespace std;
TEST(p4_test, Load_twice) {
    ConcordanceH cc;
	Concordance::BookInfo myInfo = cc.loadBook("Ulysses", "data/Ulysses.txt");
	EXPECT_EQ(32710, myInfo.lineCount);
	EXPECT_EQ(267810, myInfo.wordCount);
	EXPECT_THROW(cc.loadBook("Ulysses", "data/Ulysses.txt"), invalid_argument);
}

TEST(p4_test, lookup_plump) {
    ConcordanceH cc;
	Concordance::BookInfo myInfo = cc.loadBook("Ulysses", "data/Ulysses.txt");
	Concordance::WordRef myWord = cc.lookupWord("plump").get(0);
	const auto &myList = cc.lookupWord("plump");
	EXPECT_EQ(20, myList.size());
	EXPECT_EQ(98, myWord.wordNumber);
	EXPECT_EQ(46, myWord.lineNumber);
	EXPECT_EQ(8, myWord.columnNumber);
	EXPECT_EQ("plump", myWord.word);
}

TEST(p4_test, get_line) {
    ConcordanceH cc;
	Concordance::BookInfo myInfo = cc.loadBook("Ulysses", "data/Ulysses.txt");
	Concordance::BookInfo macbeth = cc.loadBook("Macbeth", "data/Macbeth.txt");
	auto line = cc.getLine("Ulysses", 100);
	auto line1 = cc.getLine("Macbeth", 1000);
	EXPECT_EQ("\xE2\x80\x94My name is absurd too: Malachi Mulligan, two dactyls. But it has a\r", line);
	EXPECT_EQ("First, as I am his Kinsman, and his Subiect,", line1);
}

TEST(p4_test, 2books_lookup) {
    ConcordanceH cc;
	Concordance::BookInfo ulysses = cc.loadBook("Ulysses", "data/Ulysses.txt");
	Concordance::BookInfo macbeth = cc.loadBook("Macbeth", "data/Macbeth.txt");

	const auto &wordlist = cc.lookupWord("measure");
	Concordance::WordRef myWord = wordlist.get(0);
	Concordance::WordRef myWord1 = wordlist.get(14);

	EXPECT_EQ(15, wordlist.size());
	
	EXPECT_EQ(621, myWord.lineNumber);
	EXPECT_EQ(3957, myWord.wordNumber);
	EXPECT_EQ(28, myWord.columnNumber);
	
	EXPECT_EQ(3655, myWord1.lineNumber);
	EXPECT_EQ(20262, myWord1.wordNumber);
	EXPECT_EQ(19, myWord1.columnNumber);
}


TEST(p4_test, macbeth_lookup) {
    ConcordanceH cc;
	Concordance::BookInfo ulysses = cc.loadBook("Ulysses", "data/Ulysses.txt");
	Concordance::BookInfo macbeth = cc.loadBook("Macbeth", "data/Macbeth.txt");

	const auto &wordlist = cc.lookupWord("loveless");
	Concordance::WordRef myWord = wordlist.get(0);
	
	EXPECT_EQ(1, wordlist.size());
	
	EXPECT_EQ(2137, myWord.lineNumber);
	EXPECT_EQ(14381, myWord.wordNumber);
	EXPECT_EQ(27, myWord.columnNumber);
}

TEST(p4_test, depunctuate) {
    ConcordanceH cc;
	auto nopunct = cc.depunctuate("!./macbeth.,");
	EXPECT_EQ("macbeth", nopunct);
}

TEST(p4_test, maxWord) {
    ConcordanceH cc;
	Concordance::BookInfo myInfo = cc.loadBook("Ulysses", "data/Ulysses.txt");
	Concordance::BookInfo macbeth = cc.loadBook("Macbeth", "data/Macbeth.txt");
	auto myword = cc.maxWord(5);
	auto myword1 = cc.maxWord(10);

	EXPECT_EQ("their", myword.word);
	EXPECT_EQ(782, myword.wordCount);
	EXPECT_EQ("cunningham", myword1.word);
	EXPECT_EQ(71, myword1.wordCount);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
