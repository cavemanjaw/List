#include <gtest/gtest.h>
#include "../src/SingleLinkedList.h"

class Size : public testing::Test
{
	virtual void SetUp() {}
	virtual void TearDown() {}
};

TEST_F(Size, InitiallyCreatedListSize)
{
	SingleLinkedList::List<int> list;

	EXPECT_EQ(0U, list.Size());
}

TEST_F(Size, NonEmptyInsertedElementsListSize)
{
	SingleLinkedList::List<int> list;

	list.Insert(2);
	list.Insert(3);
	list.Insert(2);

	EXPECT_EQ(3U, list.Size());
}

TEST_F(Size, CopyConstructedEmptyListSize)
{
	SingleLinkedList::List<int> list;
	SingleLinkedList::List<int> secondList(list);

	EXPECT_EQ(0U, list.Size());
	EXPECT_EQ(0U, secondList.Size());
}
