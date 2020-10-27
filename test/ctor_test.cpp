#include <gtest/gtest.h>
#include "../src/SingleLinkedList.h"

class Constructor : public testing::Test
{
	virtual void SetUp() {}
	virtual void TearDown() {}
};

TEST_F(Constructor, ConstructEmptyList)
{
	// Add more instantiation based on Herb Sutter article
	SingleLinkedList::List<int> list;
	SingleLinkedList::List<int> secondList = SingleLinkedList::List<int>();
	auto thirdList = SingleLinkedList::List<int>();
}
