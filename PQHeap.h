/**
 * @file PQHeap.h - Heap implementation of PriorityQueue ADT
 * @author Nassuel Valera Cuevas
 * @see "Seattle University, CPSC 2430, Spring 2018"
 */

#pragma once
#include <stdexcept>
#include "adt/PriorityQueue.h"
#include "adt/List.h"

/**
 * @see adt/PriorityQueue.h
 */
template <typename T>
class PQHeap : public PriorityQueue<T> {
public:
	PQHeap() : heap(nullptr), n(0), capacity(0) {}
	~PQHeap() {
		delete[] heap;
	}
	PQHeap(const PQHeap<T>& other) : PQHeap() {
		*this = other;
	}
	PQHeap(PQHeap<T>&& temp) : PQHeap() {
		*this = temp;
	}
	PQHeap<T>& operator=(const PQHeap<T>& other) {
		if (this != &other) {
			delete[] heap;
			n = other.n;
			capacity = other.capacity;
			heap = new T[capacity];
			for (size_t i = root(); i <= n; i++)
				heap[i] = other.heap[i];
		}
		return *this;
	}
	
	// Make own swap
	PQHeap<T>& operator=(PQHeap<T>&& temp) {
		swap(heap, temp.heap);
		swap(n, temp.n);
		swap(capacity, temp.capacity);
	}
	
	/**
	 * Build a heap in O(n) time. Utilizing a list. 
	 * 
	 * @param list of elements to enqueue en masse
	 * @post every element in list has been enqueued into this heap
	 */
	PQHeap(const List<T>& list) : PQHeap() {
		capacity = list.size();
		n = list.size();
		heap = new T[capacity];
		for (int i = list.size()-1; i >= 0; i--)
			heap[i] = list.get(i);
		for (size_t i = n/2; i >= root(); i--)
			percolate(i);
	}
	
	/**
	 * @see adt/PriorityQueue.h
	 */
	void enqueue(const T& datum) {
		if (n == capacity)
			resize();
		heap[++n] = datum;
		bubble(n);
	}

	/**
	 * @see adt/PriorityQueue.h
	 */
	const T& peek() const {
		if (empty())
			throw std::invalid_argument("peek in empty heap");
		return heap[root()];
	}

	/**
	 * @see adt/PriorityQueue.h
	 */
	void dequeue() {
		if (empty())
		throw std::invalid_argument("dequeue from empty heap");
		swap(root(), n--);
		percolate(root());
	}
	
	/**
	 * @see adt/PriorityQueue.h
	 */
	bool empty() const {
		return n == 0;
	}
	
	/**
	 * @see adt/PriorityQueue.h
	 */
	void clear() {
		n = 0;
	}
	
	/**
	 * @see adt/PriorityQueue.h
	 */
	std::ostream& print(std::ostream &out) const {
		for (size_t i = root(); i <= n; i++)
			out << value(i) << " ";
		return out;
	}

private:
	T *heap;
	size_t n;
	size_t capacity;
	
	/**
	 * Bubble the value at heap[child] up to its appropriate place in the heap.
	 * Bubble as in bubbles go up when they're in water.
	 *
	 * @param child index of heap where the node may be out-of-heapness
	 */
	void bubble(size_t child) {
		while (!is_root(child) && value(child) < value(parent(child))) {
			size_t p = parent(child);
			swap(child, p);
			child = p;
		}
	}
	
	/**
	 * Percolate the value at heap[p] down to its appropriate place in the heap.
	 *
	 * @param p index of heap where the node may be out-of-heapness
	 */
	void percolate(size_t p) {
		while (!is_leaf(p)) {
			size_t child = left(p);
			if (has_right(p) && value(right(p)) < value(child))
				child = right(p);
			if (value(p) <= value(child))
				return;
			swap(child, p);
			p = child;
		}
	}
	
	/**
	 * Get the value of heap node i.
	 *
	 * @param i index into heap
	 * @return reference to the value at node i
	 */
	const T& value(size_t i) const {
		return heap[i];
	}
	
	/**
	 * The root index in this heap. Denoting that it starts at 1.
	 * Index 0 being empty.
	 *
	 * @return 1 which is the root
	 */
	static size_t root() {
		return 1;
	}

	/**
	 * Get the parent index of child.
	 *
	 * @param child index of node whose parent is desired.
	 * @return index of the parent of child
	 */
	static size_t parent(size_t child) {
		return child/2;
	}

	/**
	 * Get the left child index of p.
	 *
	 * @param p index of node whose left child is desired.
	 * @return index of left child of p
	 */
	static size_t left(size_t p) {
		return p*2;
	}

	/**
	 * Get the right child index of p.
	 *
	 * @param p index of node whose right child is desired.
	 * @return index of right child of p
	 */
	static size_t right(size_t p) {
		return left(p)+1;
	}

	/**
	 * Check if given index is in this heap.
	 *
	 * @param i node index to check
	 */
	bool valid(size_t i) const {
		return i <= n && i >= root();
	}
	
	/**
	 * Check if given index is in this heap.
	 *
	 * @param i node index to check
	 * @return true if i is root()
	 */
	bool is_root(size_t i) const {
		return i == root();
	}
	
	/**
	 * Check if the given index is a leaf in this heap.
	 *
	 * @param i index of the node to check
	 * @return true if i is leaf
	 */
	bool is_leaf(size_t i) const {
		return !valid(left(i));
	}
	
	/**
	 * Check if given index has a right child in this heap. No need to check for
	 * left node since if a parent node has a right child, it sure has a left child.
	 *
	 * @param p node index to check
	 * @return true if p has both a left and right child.
	 */
	bool has_right(size_t p) const {
		return valid(right(p));
	}
	
	/**
	 * Swap the value at i and j in the heap.
	 *
	 * @param ref1 index into heap
	 * @param ref2 index into heap
	 */
	void swap(size_t ref1, size_t ref2) {
		T tmp(heap[ref1]);
		heap[ref1] = heap[ref2];
		heap[ref2] = tmp;
	}

	/**
	 * Resize the heap to be twice as big.
	 */
	void resize() {
		T *oldheap = heap;
		capacity = 2*capacity + 19;
		heap = new T[capacity + 1];
		for (size_t i = 1; i <= n; i++)
			heap[i] = oldheap[i];
		
		delete[] oldheap;
	}
};