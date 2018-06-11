/**
 * @file ConcordanceBST.cpp - implementation for ConcordanceBST class
 * @author Nassuel Valera (Template by Professor Kevin Lundeen)
 * @see "Seattle University, CPSC2430, Spring 2018"
 */

#include <fstream>
#include <sstream>
#include <stdexcept>
#include "ConcordanceBST.h"
using namespace std;

const Concordance::BookInfo& ConcordanceBST::loadBook(string bookname, string filename) {
    if (books.has(bookname))
        throw invalid_argument("already have a book named " + bookname);
    ifstream f(filename);
    if (!f.is_open())
        throw invalid_argument("cannot open " + filename);

    BookInfo info(bookname, filename);
    Book book;
    Line line;
    Word word;
    while (!f.eof() && getline(f, line)) {
        info.lineCount++;
        book.append(line);

        istringstream ss(line);
        int colnum = 0;
        while (!ss.eof() && ss >> word) {
            word = depunctuate(word);
            if (word.length() > 0) {
                info.wordCount++;
                words.get(word).append(WordRef(bookname, word, info.wordCount, info.lineCount, colnum));
            }
            colnum = ss.tellg();
        }
    }
    catalog.add(bookname, info);
    books.add(bookname, book);
    return catalog.get(bookname);
}

void ConcordanceBST::unloadBook(string bookname) {
    catalog.remove(bookname);
    books.remove(bookname);
    ListA<Word> toDelete;
    for (Word word: words) {
        WordRefList &wrl = words.get(word);
        for (int i = wrl.size()-1; i >= 0; i--)
            if (wrl.get(i).bookname == bookname)
                wrl.remove(i);
        if (wrl.size() == 0)
            toDelete.append(word);
    }
    for (int j = toDelete.size()-1; j >= 0; j--)
        words.remove(toDelete.get(j));
}

const List<Concordance::WordRef>& ConcordanceBST::lookupWord(string word) const {
    static ListA<WordRef> empty;
    if (!words.has(word))
        return empty;
    return words.get(word);
}

ListA<Concordance::WordInfo> *ConcordanceBST::wordList(string start) const {
    auto infolist = new ListA<WordInfo>;
    for (auto it = words.begin(start); infolist->size() < 20 && it != words.end(); ++it) {
        const Word& word = *it;
        const WordRefList& reflist = words.get(word);
        infolist->append(WordInfo(word, reflist.size()));
    }
    return infolist;
}

string ConcordanceBST::getLine(string bookname, int lineNumber) const {
    if (0 < lineNumber && lineNumber <= books.get(bookname).size())
        return books.get(bookname).get(lineNumber-1);
    else
        return "";
}

string ConcordanceBST::depunctuate(string word) {
    string s = word;
    int epos = word.length() - 1;
    while (epos >= 0 && !isalnum(word[epos]))
        epos--;
    int spos = 0;
    while (spos <= epos && !isalnum(word[spos]))
        spos++;
    if (epos < spos)
        return "";
    word = word.substr(spos, epos-spos+1);
    if (word.length() > 1 && isupper(word[0]) && !isupper(word[1]))
        word[0] = tolower(word[0]);
    return word;
}

Concordance::WordInfo ConcordanceBST::maxWord(int length) const {
    WordInfo info;
    for (auto it = words.begin(); it != words.end(); ++it) {
        auto word = *it;
        auto wl = words.get(word);
        if (static_cast<int>(word.length())== length && wl.size() > info.wordCount) {
            info.wordCount = wl.size();
            info.word = word;
        }
    }
    return info;
}

