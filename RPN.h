

#pragma once
#include <string>
#include "Tokens.h"
#include "DictBST.h"

class RPN {
public:
	double evaluate(std::string expression);
private:
	DictBST<std::string, double> symboltable;
	
	double evalToken(const Token& token) const;
};