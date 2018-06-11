/**
  * @file ConcordanceApp4.cpp - implementation of ConcordanceApp4 class
  * @author Nassuel Valera Cuevas
  * @see "Seattle University CPSC2430 Spring 2018"
  */

#include <iostream>
#include "ConcordanceApp4.h"
#include <string>

void ConcordanceApp4::run() {
	std::cout << "Welcome to the Concordance App!" << std::endl;
	std::cout << "Please insert one command at a time" << std::endl;
		
	while (1) {
		std::cout << "Concordance: ";
		std::string input;
		getline(std::cin, input);
		
		Command com = getCommand(input);
			
		if (com == Command::QUIT) {
			break;
		} else if (com == Command::LOAD) {
			std::string load = getFilename(input);
			std::cout << "Filename for " << load << ": ";
				
			std::string filename;
			getline(std::cin, filename);
				
			concordance.loadBook(load, filename);
				
			std::cout << std::endl;
				
			// Testing
			//std::cout << "Book: " << load << " was loaded from its address " << filename << std::endl;
		} else if (com == Command::LOOKUP) {
			std::cout << std::endl;
				
			std::string wordToLook = input.substr(input.find(" ") + 1, input.size());
				
			const List<ConcordanceH::WordRef> &words = concordance.lookupWord(wordToLook);
				
			displayWords(words);
				
			// What reference does the user want
			std::cout << "Which reference for " << wordToLook << "? (0 for none): ";
			
			std::string selnum;
				
			getline(std::cin, selnum);
			int seln = stoi(selnum) - 1;
				
			std::cout << std::endl;
				
			if (seln == -1) {
				// do nothing
			} else {
				displayPassage(words.get(seln));
					
				while (1) {
					std::string dummie = " " + wordToLook;
					std::cout << "Another reference for " 
					<< concordance.highlightWord(dummie, dummie.find(wordToLook), dummie.size()) << "? (0 for none): ";
					
					std::string selnum2;
				
					getline(std::cin, selnum2);
					int seln2 = stoi(selnum2) - 1;
						
					std::cout << std::endl;
					if (seln2 == -1) {
						break;
					} else {
						displayPassage(words.get(seln2));
					}
						
				}
			}
					
		} else if (com == Command::SHOW) {
			// word to show
			lookup(input.substr(input.find(" ") + 1 , input.size() - 1));
		} else if (com == Command::MAX) {				
			std::cout << "Most common word of length " << stoi(input.substr(input.find(" "), input.size()))
					<< ": " << concordance.maxWord(stoi(input.substr(input.find(" "), input.size()))).word << ": "
					<< concordance.maxWord(stoi(input.substr(input.find(" "), input.size()))).wordCount << " occurrences"
					<< std::endl;
					std::cout << std::endl;
		} else if (com == Command::UNLOAD) {
			std::string unl = getFilename(input);
			concordance.unloadBook(unl);
			std::cout << std::endl;
			//std::cout << "Book " + unl + " was unloaded succesfully" << std::endl;
		}
	}
}

ConcordanceApp4::Command ConcordanceApp4::getCommand(std::string &name) {
	// formats the string name to lower case
	for (unsigned int i = 0; i < name.size(); i++)
		name[i] = tolower(name[i]);
		
	if (name.find("load") == 0)
		return Command::LOAD;
	else if (name.find("quit") == 0)
		return Command::QUIT;
	else if (name.find("lookup") == 0)
		return Command::LOOKUP;
	else if (name.find("show") == 0)
		return Command::SHOW;
	else if (name.find("max") == 0)
		return Command::MAX;
	else if (name.find("unload") == 0)
		return Command::UNLOAD;
	else
		throw std::invalid_argument("Unvalid Command");
}

std::string ConcordanceApp4::getFilename(std::string prompt) {	
	prompt = prompt.substr(prompt.find(" ") +1, prompt.size());	
	prompt[0] = toupper(prompt[0]);
	return prompt;
}

void ConcordanceApp4::displayWords(const List<Concordance::WordRef> &words) {
	for(int i = 1; i <= words.size(); i++) {
		std::string line;
		Concordance::WordRef ref = words.get(i-1);
		line = concordance.getLine(ref.bookname, ref.lineNumber);       

        std::string w = ref.word;
        std::string l = line;
        for(unsigned int j = 0; j < w.size(); j++)
            w[j] = toupper(w[j]);
        for(unsigned int k = 0; k < line.size(); k++)
            l[k] = toupper(l[k]);
        line = concordance.highlightWord(line, l.find(w), ref.word.size());
        std::cout<< i << ".  (" << ref.bookname << ":" << ref.lineNumber << ") " << line << std::endl;       
    }
}

void ConcordanceApp4::displayPassage(const Concordance::WordRef &ref) {
	std::string selname = ref.bookname;
	int snuml = ref.lineNumber;

	for(int i = snuml - 5; i < snuml + 6;i++) {
		std::string line;
		line = concordance.getLine(selname, i);
			
		std::string hw = ref.word;
		std::string hl = line;
		for(unsigned int j = 0; j < hw.size(); j++)
				hw[j]=toupper(hw[j]);
		for(unsigned int k = 0; k < line.size(); k++)
				hl[k]=toupper(hl[k]);
		int fw = hl.find(hw);
		if(fw != -1)
			line = concordance.highlightWord(line, fw, ref.word.size());
           
		std::cout << "(" << selname << ":"<< i <<") "<< line << std::endl;
	}
}

int ConcordanceApp4::getSelection(std::string prompt, int maxSelection) {
	// Absolutely no idea what this method is supposed to do
	return 0;
}

void ConcordanceApp4::lookup(std::string word) {
	auto list = concordance.wordList(word);
	for (int i = 0; i < list->size(); i++) {
		std::cout << list->get(i).word << ": " << list->get(i).wordCount << " occurrences" << std::endl;
	}
		
	std::cout << std::endl;
}