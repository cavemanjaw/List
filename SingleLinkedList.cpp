#include "SingleLinkedList.h"

SingleLinkedList::List::List():
	head(nullptr)
{
}

void SingleLinkedList::List::Insert(int data)
{
	//TODO: Actually review it!

	/* There could be pointer-to-pointer use
	 * to not to use the condition checking for
	 * head node
	 */
	Node** nodePtr = &head;
	bool allocated = false;
	while (!allocated)
	{
		if (*nodePtr == nullptr)
		{
			*nodePtr = new Node;
			(*nodePtr)->data = data;
			//Could be break and in while(true) loop
			allocated = true;
		}
		nodePtr = &((*nodePtr)->nextNode);

	}
	//Traverse to the nearest nullptr od Node* nextNode
	//Insert the value to the new node and assign pointers
}
