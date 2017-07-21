#include "SingleLinkedList.h"

int main()
{
	//Testing List class and Node class from SingleLinkedList namespace
	SingleLinkedList::List list;

	list.Insert(5);
	list.Insert(4);
	list.Insert(10);
	list.Insert(10);
	list.Insert(10);

	list.PrintList();

	list.Remove(10);

	list.PrintList();

	SingleLinkedList::List list2;

	list2.Insert(10);

	list2.PrintList();
	list2.Remove(10);
	list2.PrintList();

	return 0;
}
