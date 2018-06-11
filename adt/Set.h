/**
 * @file Set.h - The Set ADT
 * @author Kevin Lundeen
 * @see "Seattle University, CPSC2430, Spring 2018"
 */

#pragma once

/**
 * @class Set ADT - collection of KeyType objects
 *
 * An element is either in the set or not, solely as determined
 * by the equality operator (operator==). There is no
 * concept in this class of multiple equivalent elements.
 *
 * Implementations of this ADT are also expected to support
 * a const_iterator and methods begin() and end(). Order of
 * iteration can be arbitrary.
 *
 * @tparam KeyType  elements of the set
 *                  must support equality operator
 */
template <typename KeyType>
class Set {
public:
    /**
     * Determine if the given key is currently in this set
     *
     * @param key  possible element of this set
     * @return     true if key is an element, false otherwise
     */
    virtual bool has(const KeyType& key) const = 0;

    /**
     * Add the given key into this set
     *
     * May or may not already be an element of this set.
     * @param key  an element of this set
     * @post       has(key) is true
     */
    virtual void add(const KeyType& key) = 0;

    /**
     * Remove the given key from this set
     *
     * It is irrelevant how many times this key has been added to the set
     * or even if it is currently an element or not.
     * @param key  an element (possibly) of this set
     * @post       has(key) is false
     */
    virtual void remove(const KeyType& key) = 0;

    virtual ~Set() = default;  // make the destructors virtual
};
