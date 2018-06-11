/**
  *@file ConcordanceApp.h - header file of ConcordanceApp
  *@author Nassuel Valera Cuevas
  *@see "Seattle University CPSC2430 Spring 2018"
  */

#pragma once
#include "ConcordanceBST.h"
#include <stdio.h>
#include <string>


class ConcordanceApp {
public:
	/**
	 *@method run() - Runs the console application, Concordance, using the Concordance class
	 */
	void run();
		
		
private:
	/**
	 * Concordance where the books are stored
	 */
	ConcordanceBST concordance;
	
	/**
	 * enum Class which facilitates the handling of Commands
	 */
	enum Command {
		QUIT, LOAD, LOOKUP, SHOW, MAX, UNLOAD
	};
	
	/**
	 * Read the string and determine if it is a command, then returns the enum associated to
	 * that command.
	 *
	 * @param name string to read
	 * @return enum Command 
	 *
	 * @except invalid_argument if the command seen on the string does not exist
	 */
	Command getCommand(std::string &name);
	
	/**
	 * Read the string and give it back as a string to be stored as a key.
	 *
	 * @param name string to read
	 * @return enum Command 
	 *
	 * @except invalid_argument if the command seen on the string does not exist
	 */
	std::string getFilename(std::string prompt);
	
	/**
	 * Takes a List of WordRefs and prints the lines where the word lookedup is located.
	 *
	 * @param name string to read
	 * @return enum Command 
	 *
	 * @except invalid_argument if the command seen on the string does not exist
	 */
	void displayWords(const List<Concordance::WordRef> &words);
	
	/**
	 * Takes a WordRef and prints passages.
	 *
	 * @param ref WordRef which to display lines for
	 */
	void displayPassage(const Concordance::WordRef &ref);
	
	/**
	 * Do not know what this method is supposed to do.
	 */
	int getSelection(std::string prompt, int maxSelection);
	
	/**
	 * Given word, parse through the wordList and prints the words.
	 *
	 * @param word word to start from
	 */
	void lookup(std::string word);
	
};
