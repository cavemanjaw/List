#include "SingleLinkedList.h"

int main()
{
	//Testing List class and Node class from SingleLinkedList namespace
	SingleLinkedList::List list;

	list.Insert(5);
	list.Insert(4);
	list.Insert(10);

	list.PrintList();

	return 0;
}
