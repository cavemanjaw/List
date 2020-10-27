#include <gtest/gtest.h>
#include "../src/SingleLinkedList.h"

#define NUMBER_OF_ELEMENTS 15

class ReverseRecursive : public testing::Test
{
	virtual void SetUp() {}
	virtual void TearDown() {}
};

TEST_F(ReverseRecursive, InitiallyCreatedListSize)
{
	SingleLinkedList::List<int> list;

	for (int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
	{
		list.Insert(i);
	}

	EXPECT_EQ(NUMBER_OF_ELEMENTS, list.Size());

	list.ReverseRecursive();

	//TODO: Change to iterators when the time comes
	for (int i = NUMBER_OF_ELEMENTS - 1; i <= 0; --i)
	{
		SingleLinkedList::Node<int>* listPtr = &(list.Front());
		EXPECT_EQ(i, listPtr->data);
		listPtr = listPtr->nextNode;
	}
}
