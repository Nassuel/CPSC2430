/**
 * @file SetS.h - stl::set implementation of Set ADT
 * @author Kevin Lundeen
 * @see "Seattle University, CPSC2430, Spring 2018"
 */

#pragma once
#include "adt/Set.h"
#include <set>

/**
 * @class SetS - stl::set implementation of the Set ADT
 *
 * An element is either in the set or not, solely as determined
 * by the equality operator (operator==). There is no
 * concept in this class of multiple equivalent elements.
 *
 * This implementation of the Set ADT also supports
 * a const_iterator and methods begin() and end(). Order of
 * iteration is in KeyType order (per its < operator). Additionally,
 * there is a begin(key) that starts the iteration at the given
 * key.
 *
 * Time-efficiency of methods is directly resulting from using the STL
 * set template class which uses a balanced BST:
 * has(key)         O(log n)
 * add(key,value)   O(log n)
 * remove(key)      O(log n)
 * begin()          O(1)
 * begin(key)       O(log n)
 * end()            O(1)
 *
 * @tparam KeyType     type of elements (keys) of the set
 *                     must support equality operator and < operator
 */
template <typename KeyType>
class SetS : public Set<KeyType> {
public:
    SetS() = default;
    ~SetS() = default;
    SetS(const SetS<KeyType>& other) = default;
    SetS(SetS<KeyType>&& temp) = default;
    SetS<KeyType>& operator=(const SetS<KeyType>& other) = default;
    SetS<KeyType>& operator=(SetS<KeyType>&& temp) = default;

    bool has(const KeyType& key) const {
        return set.find(key) != set.end();
    }

    void add(const KeyType& key) {
        set.insert(key);
    }

    void remove(const KeyType& key) {
        set.erase(key);
    }

    /**
     * @class const_iterator - used for begin() and end()
     * C++11 expectations for const iterators. Can be used
     * in range-based for loops, for example.
     * Operations supported are *, !=, and ++(prefix).
     */
    class const_iterator {
    public:
        const_iterator(typename std::set<KeyType>::const_iterator it) : underlyingIterator(it) {
        }
        const KeyType& operator*() const {
            return *underlyingIterator;
        }
        const const_iterator& operator++() {
            ++underlyingIterator;
            return *this;
        }
        bool operator!=(const const_iterator& rhs) const {
            return underlyingIterator != rhs.underlyingIterator;
        }
    private:
        typename std::set<KeyType>::const_iterator underlyingIterator;
        friend class SetS<KeyType>;
    };

    /**
     * Beginning iterator starts iteration in KeyType order through the elements.
     * @return beginning iterator
     */
    const_iterator begin() const {
        return const_iterator(set.begin());
    }

    /**
     * Beginning iterator starts iteration in alphabetical order
     * @param start
     * @return
     */
    const_iterator begin(const KeyType& start) const {
        return const_iterator(set.lower_bound(start));
    }

    /**
     * Ending iterator used in standard fashion to see when an iterator has finished
     * traversing this set.
     *
     * @return ending iterator
     */
    const_iterator end() const {
        return const_iterator(set.end());
    }

private:
    std::set<KeyType> set;
};
