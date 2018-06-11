/**
 * @file DictM.h - stl::map implementation of Dictionary ADT
 * @author Kevin Lundeen
 * @see "Seattle University, CPSC2430, Spring 2018"
 */

#pragma once
#include "adt/Dictionary.h"
#include <map>

/**
 * @class DictM - stl::map implementation of Dictionary ADT
 *
 * A dictionary is a set whose elements has an associated payload.
 * An element is either in the dictionary or not, solely as determined
 * by the equality operator (operator==). There is no
 * concept in this class of multiple equivalent elements.
 *
 * This implementation of the Dictionary ADT also supports
 * a const_iterator and methods begin() and end(). Order of
 * iteration is in KeyType order (per its < operator). Additionally,
 * there is a begin(key) that starts the iteration at the given
 * key.
 *
 * Time-efficiency of methods is directly resulting from using the STL
 * map template class which uses a balanced BST:
 * has(key)         O(log n)
 * get(key)         O(log n)
 * get(key) const   O(log n)
 * add(key,value)   O(log n)
 * remove(key)      O(log n)
 * begin()          O(1)
 * begin(key)       O(log n)
 * end()            O(1)
 *
 * @tparam KeyType     type of elements (keys) of the dictionary
 *                     must support equality operator and < operator
 * @tparam ValueType   type of associated data for each key in the dictionary
 *                     must support zero-argument construction
 */
template <typename KeyType, typename ValueType>
class DictM : public Dictionary<KeyType, ValueType> {
public:
    typedef DictM<KeyType,ValueType> DictType;  // DictType is alias for DictM<KeyType,ValueType>
    DictM() = default;
    ~DictM() = default;
    DictM(const DictType& other) = default;
    DictM(DictType&& temp) = default;
    DictType& operator=(const DictType& other) = default;
    DictType& operator=(DictType&& temp) = default;

    bool has(const KeyType& key) const {
        return map.find(key) != map.end();
    }

    ValueType& get(const KeyType& key) {
        return map[key];
    }

    const ValueType& get(const KeyType& key) const {
        return map.at(key);
    }

    void add(const KeyType& key, const ValueType& value) {
        map[key] = value;
    }

    void remove(const KeyType& key) {
        map.erase(key);
    }

    /**
     * @class const_iterator - used for begin() and end()
     * C++11 expectations for const iterators. Can be used
     * in range-based for loops, for example.
     * Operations supported are *, !=, and ++(prefix).
     */
    class const_iterator {
    public:
        const_iterator(typename DictType::StlMap::const_iterator it) : it(it) {}
        const KeyType& operator*() const {
            return it->first;
        }
        const const_iterator& operator++() {
            ++it;
            return *this;
        }
        bool operator!=(const const_iterator& rhs) const {
            return it != rhs.it;
        }
    private:
        typename DictType::StlMap::const_iterator it;
        friend class DictM<KeyType,ValueType>;
    };

    /**
     * Beginning iterator starts iteration in KeyType order through the elements.
     * @return beginning iterator
     */
    const_iterator begin() const {
        return const_iterator(map.begin());
    }

    /**
     * Beginning iterator starts iteration in alphabetical order
     * @param start
     * @return
     */
    const_iterator begin(const KeyType& start) const {
        return const_iterator(map.lower_bound(start));
    }

    /**
     * Ending iterator used in standard fashion to see when an iterator has finished
     * traversing this set.
     *
     * @return ending iterator
     */
    const_iterator end() const {
        return const_iterator(map.end());
    }

private:
    typedef std::map<KeyType, ValueType> StlMap;  // Make an alias for the complicated typename
    StlMap map;
};
