

#pragma once
#include "adt/Set.h"
#include <stdexcept>


template<typename KeyType, typename Hasher>
class SetHash : public Set<KeyType> {
public:
	SetHash() : table(nullptr), tablesize(0), cardinality(0) {
		tablesize = 107;
		table = new Entry[tablesize];
	}
	
	~SetHash() {
		delete[] table;
	}
	
	// FIXME - big 5
	
	void add(const KeyType& key) {
		Entry &entry = getBucket(key);
		if (entry.status != Status::ACTIVE) {
			entry.status = ACTIVE;
			entry.key = key;
			cardinality++;
		}
	}
	
	bool has(const KeyType& key) const {
		const Entry &entry = getBucket(key);
		return entry.status == Status::ACTIVE;
	}
	
	void remove(const KeyType& key) {
		throw std::invalid_argument("not implemented yet FIXME");
	}
private:
	enum Status {
		EMPTY, ACTIVE, DELETED
	};
	
	struct Entry {
		Status status;
		KeyType key;
		
		Entry() : status(Status::EMPTY), key() {}
	};
	
	Entry *table;		// want to make it dynamic
	size_t tablesize;	// how big the table is
	int cardinality; 	// keep track of how many items are inside of the table set
	
	/**
	 * Find the bucket where the key should live.
	 * If key is in the set, then the bucket where key currently is, is returned.
	 * If key is not in the set, then the bucket where key should be inserted is returned.
	 * @param key key to look for
	 * @return bucket where the key should live
	 */
	Entry &getBucket(const KeyType& key) const {
		Hasher h;
		size_t hash = h(key);
		size_t bucket = hash % tablesize;
		// FIXME - worry about collisions!
		while ((table[bucket].status == Status::ACTIVE && table[bucket].key != key) || table[bucket].status == Status::DELETED)
			bucket = (bucket + 1) % tablesize;
		return table[bucket];
	}
};