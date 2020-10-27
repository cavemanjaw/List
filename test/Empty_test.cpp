#include <gtest/gtest.h>
#include "../src/SingleLinkedList.h"

class Empty : public testing::Test
{
	virtual void SetUp() {}
	virtual void TearDown() {}
};

TEST_F(Empty, InitiallyEmptyList)
{
	SingleLinkedList::List<int> list;

	EXPECT_EQ(true, list.Empty());
}

TEST_F(Empty, CopyConstructedEmptyList)
{
	SingleLinkedList::List<int> list;
	SingleLinkedList::List<int> secondList(list);

	EXPECT_EQ(true, list.Empty());
	EXPECT_EQ(true, secondList.Empty());
}

TEST_F(Empty, ClearedEmptyList)
{
	SingleLinkedList::List<int> list;

	EXPECT_EQ(true, list.Empty());

	list.Insert(2);
	list.Insert(4);
	list.Insert(5);
	list.Insert(123);

	EXPECT_EQ(false, list.Empty());

	list.Clear();

	EXPECT_EQ(true, list.Empty());
}

TEST_F(Empty, EmptyListAfterElementRemoval)
{
	SingleLinkedList::List<int> list;

	EXPECT_EQ(true, list.Empty());

	list.Insert(2);

	EXPECT_EQ(false, list.Empty());

	list.Remove(2);

	EXPECT_EQ(true, list.Empty());
}
