/**
 * @file lab1_test.cpp - tests for lab1 assignment
 * @author Kevin Lundeen
 * @see "Seattle University, CPSC 2430, Spring 2018"
 */
#include <iostream>
#include <sstream>
#include <gtest/gtest.h>
#include "CrowWorld.h"


TEST(Tw1Test, TestFlytime) {
	CrowWorld w(3963.1676, 25.0, "data");
	EXPECT_NEAR(5201.23, w.getDistance("Nashville", "Timbuktu"), 0.01);
	EXPECT_NEAR(208.049, w.getFlytime("Nashville", "Timbuktu"), 0.001);
	EXPECT_NEAR(204.186, w.getFlytime("Leningrad", "Denver"), 0.001);
}

TEST(Tw1Test, TestThrow) {
	try {
		CrowWorld w(3963.1676, 25.0, "datax");
		FAIL() << "Expected std::logic_error";
	} catch(std::logic_error const & err) {
		; // PASS
	} catch(...) {
		FAIL() << "Wrong type of error, expected std::logic_error";
	}
	try {
		CrowWorld w(3963.1676, 25.0, "data");
		w.getFlytime("somewhere", "nowhere");
		FAIL() << "Expected std::logic_error";
	} catch(std::logic_error const & err) {
		; // PASS
	} catch(...) {
		FAIL() << "Wrong type of error, expected std::logic_error";
	}
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
