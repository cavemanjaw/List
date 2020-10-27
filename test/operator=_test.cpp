#include <gtest/gtest.h>
#include "../src/SingleLinkedList.h"

#define NUMBER_OF_ELEMENTS 15

class CopyAssignmentOperator : public testing::Test
{
	virtual void SetUp() {}
	virtual void TearDown() {}
};

TEST_F(CopyAssignmentOperator, CopyEmptyList)
{
	SingleLinkedList::List<int> list;
	SingleLinkedList::List<int> secondList;

	EXPECT_EQ(true, list.Empty());
	EXPECT_EQ(true, secondList.Empty());

	list = secondList;

	EXPECT_EQ(true, list.Empty());
	EXPECT_EQ(true, secondList.Empty());
}

TEST_F(CopyAssignmentOperator, CopyEmptyListChainedOperator)
{
	SingleLinkedList::List<int> list;
	SingleLinkedList::List<int> secondList;
	SingleLinkedList::List<int> thirdList;
	SingleLinkedList::List<int> fourthList;
	SingleLinkedList::List<int> fifthList;

	EXPECT_EQ(true, list.Empty());
	EXPECT_EQ(true, secondList.Empty());
	EXPECT_EQ(true, thirdList.Empty());
	EXPECT_EQ(true, fourthList.Empty());
	EXPECT_EQ(true, fifthList.Empty());

	list = secondList = thirdList = fourthList = fifthList;

	EXPECT_EQ(true, list.Empty());
	EXPECT_EQ(true, secondList.Empty());
	EXPECT_EQ(true, thirdList.Empty());
	EXPECT_EQ(true, fourthList.Empty());
	EXPECT_EQ(true, fifthList.Empty());
}

TEST_F(CopyAssignmentOperator, CopyClearedListChainedOperator)
{
	SingleLinkedList::List<int> lists[5];

	for (auto& element: lists)
	{
		EXPECT_EQ(true, element.Empty());
	}

	//Fill the lists with some elements
	for (auto& element: lists)
	{
		for (int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
		{
			element.Insert(i);
		}
	}

	for (auto& element: lists)
	{
		EXPECT_EQ(false, element.Empty());
	}

	//Clear the lists
	for (auto& element: lists)
	{
		element.Clear();
	}

	lists[0] = lists[1] = lists[2] = lists[3] = lists[4];

	for (auto& element: lists)
	{
		EXPECT_EQ(true, element.Empty());
	}
}
