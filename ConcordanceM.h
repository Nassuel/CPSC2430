/**
 * @file ConcordanceM.h - 
 * @author Kevin Lundeen
 * @see "Seattle University, CPSC2430, Spring 2018"
 */

#pragma once
#include "adt/Concordance.h"
#include "ListA.h"
#include "DictM.h"

class ConcordanceM : public Concordance {
public:
    const BookInfo& loadBook(std::string bookname, std::string filename);

    void unloadBook(std::string bookname);

    const List<WordRef>& lookupWord(std::string word) const;

    ListA<WordInfo> *wordList(std::string start) const;

    std::string getLine(std::string bookname, int lineNumber) const;

    static std::string depunctuate(std::string word);

    WordInfo maxWord(int length) const;

private:
    typedef std::string BookName;
    typedef std::string Word;
    typedef std::string Line;
    typedef ListA<Line> Book;
    typedef ListA<WordRef> WordRefList;
    typedef DictM<Word, WordRefList> WordIndex;
    WordIndex words;
    DictM<BookName, BookInfo> catalog;
    DictM<BookName, Book> books;
};
