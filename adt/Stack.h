/**
 * @file adt/Stack.h - the Stack ADT
 * @author Kevin Lundeen
 * @see "Seattle University, CPSC 2430, Spring 2018"
 */

#pragma once
#include <iostream>

/**
 * @class Stack<T> -- abstract base class for the Stack ADT
 *
 * The Stack Abstract Data Type is a list of same-datatype elements where insertions
 * and deletions can only happen at one end.
 * The stack can be enlarged by pushing an element of type T to it. (Note that
 * T must have an accessible default constructor.) It can be shrunk by the pop
 * method. Only the top element can be accessed. It is accessed with the peek method.
 *
 * @param T  Data type of the elements. Each T element is copied into the stack with
 *           the push method.  A const reference to the copy is
 *           returned by the peek method. T therefore must have an accessible
 *           copy-constructor and assignment operator. Most implementations also
 *           require a default constructor. The ADT does not require that T support
 *           any comparison operators.
 */

template <typename T>
class Stack {
public:
    /**
     * Get a reference to the element stored at the top of the stack (newest of it's current elements).
     *
     * Efficiency: O(1)
     * @return   a const reference to the top element in this stack
     * @throws   out_of_range if this stack is empty
     * @pre      !empty()
     */
    virtual const T& peek() const = 0;

    /**
     * Add a new element to the stack.
     *
     * Efficiency: depends on the implementation
     * @param datum  value to be copied onto the top of the stack
     * @post         peek() == datum and pop() would return the stack to the exact same state as before
     */
    virtual void push(const T& datum) = 0;

    /**
     * Remove the top (newest) element from the stack and destroy it.
     *
     * Efficiency: O(1)
     * @throws  out_of_range if empty()
     * @pre     !empty()
     * @post    one fewer item on the stack
     */
    virtual void pop() = 0;

    /**
     * Check if this stack has no elements.
     *
     * @return  true if there are no elements
     */
    virtual bool empty() const = 0;

    /**
     * Pop all the elements from the stack.
     *
     * @post  size() == 0
     */
    virtual void clear() = 0;

    /**
     * Print the contents to the given stream.
     *
     * Requires that T has << operator into std::ostream.
     * @param out  stream to print to
     * @return     modified output stream
     * @pre        out is writable
     * @post       out has a textual representation of list inserted (with <<)
     */
    virtual std::ostream& print(std::ostream& out) const = 0;

    virtual ~Stack() {} // make the destructors virtual
};

/**
 * Template operator<< overload for printing.
 *
 * This just redirects to the print method.
 */
template <typename T>
std::ostream& operator<<(std::ostream& out, const Stack<T>& stack) {
    return stack.print(out);
}

