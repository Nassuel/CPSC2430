/**
 *
 *
 */
  
#pragma once

#include <vector>
#include "adt/Stack.h"

template <typename T>
class StackV : public Stack<T> {
public:
	// Big 5 can use defaults
	
	void push(const T& datum) {
		v.push_back(datum);
	}
	
	void pop() {
		if (empty())
			throw std::invalid_argument("popping from an empty stack");
		v.pop_back();
	}
	const T& peek() const {
		if (empty())
			throw std::invalid_argument("peeking in an empty stack");
		return v.back();
	}
	bool empty() const {
		return v.empty();
	}
	void clear() {
		v.clear();
	}
	std::ostream& print(std::ostream& out) const {
		for(auto datum: v)
			out << datum << " ";
		return out;
	}
private:
	std::vector<T> v;
};