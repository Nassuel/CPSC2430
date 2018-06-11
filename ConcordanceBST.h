/**
  *@file ConcordanceApp.cpp - the concordance ADT using BST dictionaries
  *@author Nassuel Valera Cuevas
  *@see "Seattle University CPSC2430 Spring 2018"
  */

#pragma once
#include "adt/Concordance.h"
#include "ListA.h"
#include "DictBST.h"

class ConcordanceBST : public Concordance {
public:
	/**
	 * Index a book into the concordance
	 *
	 * @param bookname name to call this book within this concordance. Must be unique.
	 * @param filename where to find the text file for this book.
	 * @return info on the loaded book
	 * @except invalid_argument if filename cannot be opened or the bookname is already in use
	 * @pre bookname is not the name of a currently indexed book in this concordance
	 * @post bookname is the name of a currently indexed book in this concordance
	 */
	const BookInfo& loadBook(std::string bookname, std::string filename);
	
	/**
	 * Remove an indexed book and all of its referenced words in this concordance.
	 *
	 * @param bookname name of the book to remove.
	 * @pre bookname is the name of a currently indexed book in this concordance
	 * @post bookname is not the name of a currently indexed book in this concordance
	 */
    void unloadBook(std::string bookname);
	
	/**
	 * Get a list of all the occurences of the given word in all the books currently indexed
	 * in this concordance.
	 *
	 * @param word to look up
	 * @return list of occurences (an empty list is returned if there are no occurences)
	 */
    const List<WordRef>& lookupWord(std::string word) const;
	
	/**
	 * Get a short list of all the words, starting with given one, with occurences in this concordance.
	 *
	 * The WordInfo structure gives the number of occurences accross all the currently indexed books.
	 * The number of words returned is at the discretion of the implementation, typically about 20.
	 *
	 * @param start first word (or so) in the returned alphabetical list
	 * @return contigous alphabetical list of a few words (typically 20), starting around start
	 */
    ListA<WordInfo> *wordList(std::string start) const;
	
	/**
	 * Get line of text from the given book.
	 *
	 * @param bookname name of a currently indexed book
	 * @param lineNumber line number of the test to return from that bookname
	 * @return line of text from the book
	 */
    std::string getLine(std::string bookname, int lineNumber) const;
	
	/**
	 * Depunctuates a string.
	 *
	 * @param word word to depunctuate.
	 * @return depunctuated word
	 */
    static std::string depunctuate(std::string word);
	
	/**
	 * Get the most common word of a given length accross all indexed books.
	 *
	 * @param length word of length to look for
	 * @return most common word of a given length (empty if now words of that length are currently
	 * indexed)
	 */
    WordInfo maxWord(int length) const;

private:
    typedef std::string BookName;
    typedef std::string Word;
    typedef std::string Line;
    typedef ListA<Line> Book;
    typedef ListA<WordRef> WordRefList;
    typedef DictBST<Word, WordRefList> WordIndex;
    WordIndex words;
    DictBST<BookName, BookInfo> catalog;
    DictBST<BookName, Book> books;
};