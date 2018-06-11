/**
 * @file lab1_test.cpp - tests for lab1 assignment
 * @author Kevin Lundeen
 * @see "Seattle University, CPSC 2430, Spring 2018"
 */
#include <iostream>
#include <sstream>
#include <gtest/gtest.h>
#include "PQueueLL.h"
#include "RandomList_v2.h"
using namespace std;

TEST(Tw3Test, TestPQLL) {
    PQueueLL<int> pq;
    EXPECT_EQ(true, pq.empty());
    pq.enqueue(2);
    EXPECT_EQ(false, pq.empty());
    pq.enqueue(0);
    pq.enqueue(4);
    pq.enqueue(3);
	PQueueLL<int> *ppq = new PQueueLL<int>(pq);
	ostringstream oss;
    oss << pq;
	EXPECT_EQ(string("0, 2, 3, 4"), oss.str());
	oss.str(""); oss.clear();
	oss << *ppq;
	EXPECT_EQ(string("0, 2, 3, 4"), oss.str());
	
	ppq->clear();
	oss.str(""); oss.clear();
    oss << pq;
	EXPECT_EQ(string("0, 2, 3, 4"), oss.str());
	oss.str(""); oss.clear();
	cout << *ppq;
	EXPECT_EQ(string(""), oss.str());
	
	delete ppq;
	EXPECT_EQ(0, pq.peek());
    pq.dequeue();
	EXPECT_EQ(2, pq.peek());
    pq.dequeue();
	EXPECT_EQ(3, pq.peek());
    pq.dequeue();
	EXPECT_EQ(4, pq.peek());
    pq.dequeue();
    EXPECT_EQ(true, pq.empty());
}

TEST(Tw3Test, TestRandom) {
	PQueueLL<double> pq;
	RandomList rlist(1000, -1000.0, 1000.0);
	for (int i = 0; i < rlist.size(); i++)
		pq.enqueue(rlist.get(i));
	double last = -1001.0;
	for (int i = 0; i < rlist.size(); i++) {
		EXPECT_LE(last, pq.peek());
		pq.dequeue();
	}
	EXPECT_EQ(true, pq.empty());
}
TEST(Tw3Test, EmptyTest) {
	PQueueLL<string> priorityq;
	priorityq.enqueue("Cool"); //test a different type
	priorityq.enqueue("Pets");
	priorityq.enqueue("Are");
	priorityq.enqueue("Awesome");
	EXPECT_EQ("Are", priorityq.peek());
	priorityq.dequeue();
	EXPECT_EQ("Awesome", priorityq.peek());
	priorityq.dequeue();
	EXPECT_EQ("Cool", priorityq.peek());
	priorityq.dequeue();
	EXPECT_EQ("Pets", priorityq.peek());
	priorityq.dequeue();
	EXPECT_EQ(true, priorityq.empty());
	try{  
		// This should throw an error
		priorityq.peek();
		FAIL();
	} catch (...) {
		SUCCEED();
	}
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
