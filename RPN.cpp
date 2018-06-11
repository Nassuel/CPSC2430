
#include "RPN.h"
#include "Tokens.h"
#include "StackV.h"
using namespace std;

double RPN::evaluate(string expression) {
    Tokens q(expression);
	StackV<Token> stack;
	
	while (!q.empty()) {
		Token token = q.peek();
		q.dequeue();
        
		if (token.type == Token::NUMBER || token.type == Token::IDENTIFIER)
			stack.push(token);
		else if (token.type == Token::OPERATOR) {
			Token right = stack.peek();
			stack.pop();
			Token left = stack.peek();
			stack.pop();
			if (token.op == '+') 
				stack.push(Token(evalToken(left) + evalToken(right)));
			else if (token.op == '-') 
				stack.push(Token(evalToken(left) - evalToken(right)));
			else if (token.op == '*') 
				stack.push(Token(evalToken(left) * evalToken(right)));
			else if (token.op == '/') 
				stack.push(Token(evalToken(left) / evalToken(right)));
			else if (token.op == '=') {
				symboltable.add(left.id, evalToken(right));
				stack.push(Token(right.number));
			}
		}
	}
	return evalToken(stack.peek());
}

double RPN::evalToken(const Token& token) const {
	if (token.type == Token::OPERATOR)
		throw invalid_argument("cannot eval an op token");
	if (token.type == Token::NUMBER)
		return token.number;
	if (!symboltable.has(token.id))
		throw invalid_argument("unknown variable " + token.id);
	return symboltable.get(token.id);
}