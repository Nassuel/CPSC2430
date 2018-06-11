/**
 * @file lab6_test.cpp - tests for PQHeap
 * @author Jordan Boulanger
 * @see "Seattle University, CPSC2430, Spring 2018"
 */
#include <iostream>
#include <gtest/gtest.h>
#include <sstream>
#include "PQHeap.h"
using namespace std;

PQHeap<string> makeMeAQueueYay(){
	PQHeap<string> heap;
	for (string i: {"jade", "is", "my", "kitty", "cat"})
        heap.enqueue(i);
	return heap;
}

TEST(lab6_test, is_it_in_order) {
    PQHeap<int> heap;
    for (int i: {-3, 14, 2829, 100, -2, -3, 2, 1, 0, 14, 99, 38, 272})
        heap.enqueue(i);
    ostringstream oss;
    while (!heap.empty()) {
        oss << heap.peek() << " ";
        heap.dequeue();
    }
	EXPECT_EQ("-3 -3 -2 0 1 2 14 14 38 99 100 272 2829 ", oss.str());
}

TEST(lab6_test, rvalue_move) {
    PQHeap<string> heap(makeMeAQueueYay());
    ostringstream oss;
    while (!heap.empty()) {
        oss << heap.peek() << " ";
        heap.dequeue();
    }
	EXPECT_EQ("cat is jade kitty my ", oss.str());
}

TEST(lab6_test, lvalue_move) {
	PQHeap<int> heap;
    for (int i: {-3, 14, 2829, 100, -2, -3, 2, 1, 0, 14, 99, 38, 272})
        heap.enqueue(i);
	
	PQHeap<int> supercoolheap = heap;
	ostringstream oss;
    while (!heap.empty()) {
        oss << heap.peek() << " ";
        heap.dequeue();
    }
	EXPECT_EQ("-3 -3 -2 0 1 2 14 14 38 99 100 272 2829 ", oss.str());
}

TEST(lab6_test, make_it_resize) {
	PQHeap<size_t> heap;
	size_t i;
	for (i = 10000; i > 0; i -= 2)
		heap.enqueue(i);
	for (i = 0; i < 4; i++)
		heap.dequeue();
	for (i = 11; i < 10000; i += 2)
		heap.enqueue(i);
	for (i = 10; i < 10000; i++) {
		EXPECT_EQ(i, heap.peek());
		heap.dequeue();
	}
	EXPECT_EQ(false, heap.empty());
	heap.enqueue(666);
	heap.enqueue(999);
	heap.enqueue(333);
	heap.enqueue(888);
	EXPECT_EQ(333, heap.peek());
	// test destruction of a non-empty heap, too
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

