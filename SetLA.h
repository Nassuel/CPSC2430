/**
 * @file SetLA.h - The implementation of Set ADT using a ListA
 * @author Kevin Lundeen
 * @see "Seattle University, CPSC2430, Spring 2018"
 */

#pragma once
#include "adt/Set.h"
#include "ListA.h"

/**
 * @class SetLA - - The implementation of Set ADT using a ListA
 * @tparam KeyType  set element datatype (must support ==)
 *
 * Time efficiency:
 * has(key)     O(n)
 * add(key)     O(n)
 * remove(key)  O(n)
 */
template <typename KeyType>
class SetLA : public Set<KeyType> {
public:
    bool has(const KeyType& key) const;

    void add(const KeyType& key);

    void remove(const KeyType& key);

    /**
     * @class const_iterator - used for begin() and end()
     * C++11 expectations for const iterators. Can be used
     * in range-based for loops, for example.
     * Operations supported are *, !=, and ++(prefix).
     */
    class const_iterator {
    public:
        const_iterator(const SetLA<KeyType> *set, int pos) : set(set), current(pos) {}
        const KeyType& operator*() const {
            return set->list.get(current);
        }
        const const_iterator& operator++() {
            current++;
            return *this;
        }
        bool operator!=(const const_iterator& rhs) const {
            return set != rhs.set || current != rhs.current;
        }
    private:
        const SetLA<KeyType> *set;
        int current; // current index into list
        friend class SetLA<KeyType>;
    };

    /**
     * Beginning iterator starts iteration in arbitrary order through the elements.
     * @return beginning iterator
     */
    const_iterator begin() const {
        return const_iterator(this, 0);
    }

    /**
     * Ending iterator used in standard fashion to see when an iterator has finished
     * traversing this set.
     *
     * @return ending iterator
     */
    const_iterator end() const {
        return const_iterator(this, list.size());
    }

private:
    /**
     * Implementation uses a list of elements in arbitrary order. Each element is
     * stored exactly once in list. The has method uses linear search.
     */
    ListA<KeyType> list;
};

template <typename KeyType>
bool SetLA<KeyType>::has(const KeyType &key) const {
    for (int i = list.size()-1; i >= 0; i--)
        if (key == list.get(i))
            return true;
    return false;
}

template <typename KeyType>
void SetLA<KeyType>::add(const KeyType &key) {
    if (!has(key))
        list.append(key);
}

template <typename KeyType>
void SetLA<KeyType>::remove(const KeyType &key) {
    for (int i = list.size()-1; i >= 0; i--)
        if (key == list.get(i))
            list.remove(i);
}

