/**
 * @file Concordance.h - the Concordance ADT
 * @author Kevin Lundeen
 * @see "Seattle University, CPSC2430, Spring 2018"
 */

#pragma once
#include <iostream>
#include "List.h"

/**
 * @class Concordance - ADT for the Concordance functionality required by ConcordanceApp
 */
class Concordance {
public:
    /**
     * Data structure used to hold information on each book that has been loaded into this concordance.
     */
    struct BookInfo {
        std::string bookname;
        std::string filename;
        int lineCount;
        int wordCount;

        BookInfo() : BookInfo("", "") {}
        BookInfo(std::string bn, std::string fn)
                : bookname(bn), filename(fn), lineCount(0), wordCount(0) {}

        friend std::ostream& operator<<(std::ostream& out, const BookInfo& info) {
            return out << info.bookname << ":" << info.filename << ":" << info.lineCount << ":" << info.wordCount;
        }
    };

    /**
     * Data structure used to hold information on a single occurrence of a word in one of the currenly indexed texts
     * in this concordance.
     */
    struct WordRef {
        std::string bookname;
        std::string word;
        int wordNumber;
        int lineNumber;
        int columnNumber;

        WordRef() : WordRef("", "", 0, 0, 0) {}
        WordRef(std::string bn, std::string w, int wn, int ln, int cn)
                : bookname(bn), word(w), wordNumber(wn), lineNumber(ln), columnNumber(cn) {}

        friend std::ostream& operator<<(std::ostream& out, const WordRef& ref) {
            return out << ref.bookname << ":" << ref.word << ":" << ref.lineNumber << ":" << ref.columnNumber;
        }
    };

    /**
     * Data structure used to hold information on a word and the number of occurrences of that word across all
     * currently indexed texts in this concordance.
     */
    struct WordInfo {
        std::string word;
        int wordCount;

        explicit WordInfo(std::string w="", int n=0) : word(w), wordCount(n) {}

        friend std::ostream& operator<<(std::ostream& out, const WordInfo& info) {
            return out << info.word << ": " << info.wordCount << " occurrences";
        }
    };

    /**
     * Index a book into this concordance.
     *
     * @param bookname  Name to call this book within this concordance. Must be unique.
     * @param filename  Where to find the text file for this book.
     * @return          Info on the loaded book.
     * @throws invalid_argument if filename cannot be opened or the bookname name is already in use
     * @pre             bookname is not the name of a currently indexed book in this concordance
     * @post            bookname is the name of a currently indexed book in this concordance
     */
    virtual const BookInfo& loadBook(std::string bookname, std::string filename) = 0;

    /**
     * Remove an indexed book and all of its referenced words in this concordance.
     *
     * @param bookname  Name of the book to remove.
     * @pre             bookname is the name of a currently indexed book in this concordance
     * @post            bookname is not the name of a currently indexed book
     */
    virtual void unloadBook(std::string bookname) = 0;

    /**
     * Get a list of all the occurrences of the given word in all the books currently indexed in this concordance.
     *
     * @param word   to look up
     * @return       list of occurrences (an empty list is returned if there are no occurrences)
     */
    virtual const List<WordRef>& lookupWord(std::string word) const = 0;

    /**
     * Get a short list of all the words, starting with given one, with occurrences in this concordance.
     *
     * The WordInfo structure gives the number of occurrences across all the currently indexed books.
     * The number of words returned is at the discretion of the implementation, typically about 20.
     * Return value should be deleted by caller when they are done with it.
     * @param start   first word (or so) in the returned alphabetical list
     * @return        contiguous alphabetical list of a few words (typically 20), starting around start
     */
    virtual List<WordInfo> *wordList(std::string start) const = 0;

    /**
     * Get a line of text from the given book.
     *
     * @param bookname    name of a currently indexed book
     * @param lineNumber  line number of the text to return from that book
     * @return            line of text from the book
     */
    virtual std::string getLine(std::string bookname, int lineNumber) const = 0;

    /**
     * Get the most common word of a given length across all indexed books.
     *
     * @param length   word length to look for
     * @return         most common word of given length (empty one if no words of that length are currently indexed)
     */
    virtual WordInfo maxWord(int length) const = 0;

    /**
     * Add red highlighting around the indicated letters in the given line.
     *
     * @param line    line of text
     * @param column  column number where to start highlighting (columns start at 1, not 0)
     * @param length  length of text to highlight
     * @return        line of text with VT100 escape sequence to turn highlighted region red
     */
    static std::string highlightWord(std::string line, int column, int length) {
        std::string ret = line.substr(0, column)
               + "\033[31m" + line.substr(column, length+1)
               + "\033[39m";
        if (static_cast<int>(line.length()) > column+length+1)
            ret += line.substr(column+length+1);
        return ret;
    }

    virtual ~Concordance() = default;  // make destructors work in implementations
};


