/**
  * @file DictHash.h - the concordance ADT using hash table dictionaries
  * @author Nassuel Valera Cuevas (Template by Professor Kevin Lundeen)
  * @see "Seattle University CPSC2430 Spring 2018"
  */

#pragma once
#include "adt/Dictionary.h"
#include <stdexcept>
#include <cmath>
#include <algorithm>
#include <iostream>

/**
 * Table implementation of Dictionary ADT
 *
 * @param KeyType the index for the dictionary
 * @param ValueType the value type for the dictionary
 * @param the key hasher. Must support ctor and op(const KeyType&)
 *	
 * Time efficiency of methods:
 * add(key, value) O(1)
 * has(key) O(1)
 * get(key) O(1)
 * remove(key) O(1)
 */
template<typename KeyType, typename ValueType, typename Hasher>
class DictHash : public Dictionary<KeyType, ValueType> {
public:
	DictHash() : table(nullptr), tablesize(0), cardinality(0) {
		tablesize = 7;
		table = new Entry[tablesize];
	}
	
	~DictHash() {
		delete[] table;
	}
	
	// FIXME - big 5
	DictHash(const DictHash<KeyType, ValueType, Hasher>& other) : table(nullptr), tablesize(0), cardinality(0) {
		*this = other;
	}
	
	DictHash(const DictHash<KeyType, ValueType, Hasher>&& temp) : table(nullptr), tablesize(0), cardinality(0) {
		*this = temp;
	}
	
	DictHash<KeyType, ValueType, Hasher>& operator=(const DictHash<KeyType, ValueType, Hasher>& other) {
		if (this != &other) {
			if (tablesize < other.tablesize) {
				tablesize = other.tablesize;
				delete[] table;
				table = new Entry[tablesize];
			}
			cardinality = other.cardinality;
			for(auto it = other.begin(); it != other.end(); ++it) {
				add(it.dict->table[it.current].key, it.dict->table[it.current].value);
			}
		}
		return *this;
	}
	
	DictHash<KeyType, ValueType, Hasher>& operator=(DictHash<KeyType, ValueType, Hasher>&& temp) {
		std::swap(table, temp.table);
		std::swap(cardinality, temp.cardinality);
		std::swap(tablesize, temp.tablesize);
		return *this;
	}
	
	/**
	 * Add the given key, value pair into this dictionary.
	 * 
	 * May or may not be an element of the dictionary. If already in the
	 * dictionary, the prior value for key is discarded.
	 *
	 * @param key an element of this dictionary
	 * @param the data to associate with key
	 * @post has(key) is true, get(key) == value
	 */
	void add(const KeyType& key, const ValueType& value) {
		checksize();
		Hasher h;
		size_t hashed = h(key);
		const_iterator itr(this, hashed);
		const const_iterator begin = this->begin();
		
		itr.current = begin.current;
		while ((itr.dict->table[itr.current].status == Status::ACTIVE || itr.dict->table[itr.current].status == Status::DELETED) && itr.dict->table[itr.current].key != key) {
			++itr;
		}
		table[itr.current].status = Status::ACTIVE;
		table[itr.current].value = value;
		table[itr.current].key = key;
		cardinality++;
	}
	
	/**
	 * Determine if the given key is currently is in this dictionary.
	 *
	 * @param key possible element of this dictionary
	 * @return true if key is an element, false otherwise
	 */
	bool has(const KeyType& key) const {
		const Entry &entry = getBucket(key);
		return entry.status == Status::ACTIVE;
	}
	
	/**
	 * Remove the given key from the dictionary.
	 * 
	 * It is irrelevant how many times this key has been added to the dictionary or
	 * even if it is currently an element of not.
	 *
	 * @param key an element (possibly) of this dictionary
	 * @post has(key) is false
	 */
	void remove(const KeyType& key) {
		Entry &toRemove = getBucket(key);
		if (toRemove.status != Status::EMPTY) {
			toRemove.status = Status::DELETED;
			cardinality--;
		}
	}
	
	/**
	 * Fetch the current value associated with this key.
	 * 
	 * The returned reference is const.
	 *
	 * If the key was not already in the dictinary, this call throws an exception.
	 *
	 * @param key an element of this dictionary
	 * @except invalid_argument if key not a member
	 * @return the value corresponding to this key
	 * @pre has(key) is true
	 */
	const ValueType& get(const KeyType& key) const {
		Entry &toGet = getBucket(key);
		if (has(key))
			throw std::invalid_argument("Key is not a member.");
		return toGet.value;
	}
	
	/**
	 * Fetch the current value associated with this key.
	 * 
	 * The returned reference is const.
	 *
	 * If the key was not already in the dictinary, this call adds the key to the table
	 * with a default value object.
	 *
	 * @param key an element of this dictionary
	 * @except invalid_argument if key not a member
	 * @pre has(key) is true
	 */
	ValueType& get(const KeyType& key) {
		Entry &toGet = getBucket(key);
			if(!has(key)) {
				checksize();
				add(key, valueD);
			}
		return toGet.value;
	}
	
	/**
     * @class const_iterator - used for begin() and end()
     * C++11 expectations for const iterators. Can be used
     * in range-based for loops, for example.
     * Operations supported are *, !=, and ++(prefix).
     */
    class const_iterator {
    public:
        const_iterator(const DictHash<KeyType, ValueType, Hasher> *dict, int pos) : dict(dict), current(pos) {}
        const KeyType& operator*() const {
            return dict->table[current].key;
        }
        const const_iterator& operator++() {
            while(dict->table[current].status != Status::ACTIVE)
				current++;
            return *this;
        }
        bool operator!=(const const_iterator& rhs) const {
            return dict != rhs.dict || current != rhs.current;
        }
    private:
        const DictHash<KeyType, ValueType, Hasher> *dict;
        size_t current; // current index into list
        friend class DictHash<KeyType, ValueType, Hasher>;
    };

    /**
     * Beginning iterator starts iteration in arbitrary order through the elements.
     * @return beginning iterator
     */
    const_iterator begin() const {
        size_t i = 0;
		while (table[i].status != Status::ACTIVE)
			i++;
		return const_iterator(this, i);
    }
	
	/**
     * Beginning iterator starts iteration in alphabetical order
     * @param start
     * @return location of the node with the "start" KeyType
     */
    const_iterator begin(const KeyType& start) const {
		Hasher h;
		return const_iterator(this, static_cast<size_t>(h(start)));
    }

    /**
     * Ending iterator used in standard fashion to see when an iterator has finished
     * traversing this dict.
     *
     * @return ending iterator
     */
    const_iterator end() const {
        return const_iterator(this, tablesize - 1);
    }
	
private:
	
	enum Status {
		EMPTY, ACTIVE, DELETED
	};
	
	struct Entry {
		Status status;
		KeyType key;
		ValueType value;
		
		Entry() : status(Status::EMPTY), key(), value() {}
	};
	
	Entry *table;		// want to make it dynamic
	size_t tablesize;	// how big the table is
	int cardinality; 	// keep track of how many items are inside of the table dict
	ValueType valueD;
	
	/**
	 * Find the bucket where the key should live.
	 * If key is in the dict, then the bucket where key currently is, is returned.
	 * If key is not in the dict, then the bucket where key should be inserted is returned.
	 * @param key key to look for
	 * @return bucket where the key should live
	 */
	Entry &getBucket(const KeyType& key) const {
		Hasher h;
		size_t hash = h(key);
		size_t bucket = hash % tablesize;
		// FIXME - worry about collisions! Fixed with linear probing
		while ((table[bucket].status == Status::ACTIVE && table[bucket].key != key) || table[bucket].status == Status::DELETED)
			bucket = (bucket + 1) % tablesize;
		return table[bucket];
	}
	
	/**
	 * See if we need to rehash.
	 *
	 * If so, go ahead and do it. Rehashes on loadfactor > 50%	 
	 */
	void checksize() {
		if (loadfactor() > 0.5) {
			size_t newTableSize = tablesize * 2;
			// if a prime number was doubled, it is an even number. No need to check, nextprime is
			// called on tablesize
			tablesize = nextprime(newTableSize);
			
			Entry *newTable = new Entry[tablesize];
		
			for (auto it = this->begin(); it != this->end(); ++it) {
				add(it.dict->table[it.current].key, it.dict->table[it.current].value);
			}
			
			delete[] table;
			table = newTable;
			delete[] newTable;
		}
	}
	
	/**
	 * Report on current load factor (n/tablesize)
	 *
	 * @return load factor as a ratio
	 */
	double loadfactor() const {
		return cardinality / tablesize;
	}
	
	/**
	 * Check if n is prime.
	 * 
	 * @param n number to check
	 * @return true if n is prime
	 */
	static bool isprime(size_t n) {
		int sqrRoot(std::pow(n, 0.5)), count(0); // sqrRoot assigned to a variable so it is called once.
		for (int i = 2; i <= sqrRoot; i++)
			if (n % i == 0)
			    count++;
		return (count == 0); // for loop started at 2; check for == 0
	}
	
	/**
	 * Next prime number after n.
	 *
	 * @param lower bound (n+1) for prime
	 * @return next prime after n (but minimum is 7)
	 */
	static size_t nextprime(size_t n) {
		n += 1; // do not care about even numbers and the incoming number is one.
		while (!isprime(n))
			n += 2;
		return n;
	}
};