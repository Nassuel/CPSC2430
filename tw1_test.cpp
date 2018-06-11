/**
 * @file tw1_test.cpp - tests for tw1 assignment
 * @author Kevin Lundeen
 * @see "Seattle University, CPSC 2430, Spring 2018"
 */
#include <iostream>
#include <sstream>
#include <gtest/gtest.h>
#include "RandomList.h"


TEST(Tw1Test, TestSize) {
	RandomList o(1234, -1, 1);
	EXPECT_EQ(1234, o.size());
}

TEST(Tw1Test, TestMean) {
	RandomList o2(10, 11.2, 11.2);
	EXPECT_NEAR(11.2, o2.mean(), 1e-10);
	EXPECT_NEAR(112.0, o2.sum(), 1e-10);
	RandomList o3(10000, 0.0, 100.0);
	EXPECT_NEAR(50.0, o3.mean(), 1.0);
}

TEST(Tw1Test, TestThrow) {
	try {
		RandomList o4(0, 1, 1);
		FAIL() << "Expected std::invalid_argument";
	} catch(std::invalid_argument const & err) {
		; // PASS
	} catch(...) {
		FAIL() << "Wrong type of error, expected std::invalid_argument";
	}
	try {
		RandomList o5(100, 1, -1);
		FAIL() << "Expected std::invalid_argument";
	} catch(std::invalid_argument const & err) {
		; // PASS
	} catch(...) {
		FAIL() << "Wrong type of error, expected std::invalid_argument";
	}
}

TEST(Tw1Test, TestBig5) {
	RandomList *r0 = new RandomList(100, -1, 1);
	RandomList r1 = *r0;
	double d1 = r1.mean();
	EXPECT_EQ(r0->mean(), d1);
	delete r0;
	EXPECT_EQ(r1.mean(), d1);
	RandomList r2(1000, 6, 7);
	r2 = r1;
	EXPECT_EQ(r2.mean(), d1);
	EXPECT_EQ(r2.size(), r1.size());
}

TEST(Tw1Test, TestPrint) {
	RandomList o(10, -1.2, -1.2);
	std::ostringstream ss;
	ss << o;
	EXPECT_EQ("-1.2, -1.2, -1.2, -1.2, -1.2, -1.2, -1.2, -1.2, -1.2, -1.2", ss.str());
}	

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
