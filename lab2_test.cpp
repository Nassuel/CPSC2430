/**
 * @file lab2_test.cpp - tests for lab2 assignment
 * @author Kevin Lundeen
 * @see "Seattle University, CPSC 2430, Spring 2018"
 */
#include <iostream>
#include <sstream>
#include <gtest/gtest.h>
#include "InchWorm.h"

TEST(Lab2Test, TestInchWorm) {
	InchWorm iw(10,10);
	PixelMatrix pxm(20,20);
	// expect initial state bunched, so with first move we go forward 2 pixels and get straight
	iw.move();
	iw.render(pxm);
	EXPECT_EQ(RGB::WHITE, pxm.get(10,12));
	EXPECT_EQ(RGB::GREEN, pxm.get(10,11));
	EXPECT_EQ(RGB::WHITE, pxm.get(10,10));
	EXPECT_EQ(RGB::GREEN, pxm.get(10,9));
	EXPECT_EQ(RGB::WHITE, pxm.get(10,8));
	EXPECT_EQ(RGB::GREEN, pxm.get(10,7));
	EXPECT_EQ(RGB::WHITE, pxm.get(10,6));
}

TEST(Tw1Test, TestBig5) {
	InchWorm *r0 = new InchWorm(3, -2);
	r0->move(); r0->move(); r0->move();
	InchWorm r1 = *r0;
	PixelMatrix pxm(20,20);
	PixelMatrix pxm0 = pxm, pxm1 = pxm;
	r0->render(pxm0);
	r1.render(pxm1);
	EXPECT_EQ(pxm0, pxm1);
	r1.move();
	pxm1 = pxm;
	r1.render(pxm1);
	EXPECT_NE(pxm0, pxm1);
	delete r0; // destroy r0 and make sure r1 still works
	pxm0 = pxm;
	r1.render(pxm0);
	EXPECT_EQ(pxm1, pxm0);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
