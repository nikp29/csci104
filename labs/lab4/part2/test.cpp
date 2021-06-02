#include "arraylist.h"
#include "gtest/gtest.h"
#include <iostream>

class ArrayListTest : public testing::Test
{
protected:
	// You can remove any or all of the following functions if its body is empty.

	ArrayListTest()
	{
		// You can do set-up work for each test here.
	}

	virtual ~ArrayListTest()
	{
		// You can do clean-up work that doesn't throw exceptions here.
	}

	// If the constructor and destructor are not enough for setting up
	// and cleaning up each test, you can define the following methods:
	virtual void SetUp()
	{
		// Code here will be called immediately after the constructor (right
		// before each test).
		list.add(1);
		list.add(2);
		list.add(3);
	}

	virtual void TearDown()
	{
		// Code here will be called immediately after each test (right
		// before the destructor).
	}

	// Objects declared here can be used by all tests in the test case.
	ArrayList list;
};

TEST_F(ArrayListTest, GetNominal)
{
	// Exepct 0th element to be 1, 1st elemnt to be 2, etc.
	for (int i = 0; i < 3; i++)
	{
		EXPECT_EQ(i + 1, list.get(i));
	}
}

TEST_F(ArrayListTest, AddNominal)
{
	// expected added element to be 4
	list.add(4);
	EXPECT_EQ(4, list.get(3));
	EXPECT_EQ(4, list.size());
}
/**
			Removes an int from the position, and shift everytihng in place
			Calling remove(2) on | 1 2 3 4 5 | results in | 1 2 4 5 |
			The size also decrements.
			If the position is invalid, does not do anything.
		**/
TEST_F(ArrayListTest, RemoveNominal)
{
	list.remove(1);
	EXPECT_EQ(3, list.get(1));
	EXPECT_EQ(1, list.get(0));
	list.remove(0);
	EXPECT_EQ(3, list.get(0));
	list.remove(0);
	EXPECT_EQ(0, list.size());
}
/**
			Replaces an int at the position with the new int.
			If the position is invalid, does not do anything.
		*/
TEST_F(ArrayListTest, SetOffNominal)
{
	list.set(-1, 2);
	list.set(3, 2);
	list.set(0, 1);
	list.set(1, 1);
	list.set(2, 1);
	list.set(-1, 2);
	EXPECT_EQ(3, list.size());
	EXPECT_EQ(1, list.get(0));
	for (int i = 0; i < 3; i++)
	{
		EXPECT_EQ(1, list.get(i));
	}
}
