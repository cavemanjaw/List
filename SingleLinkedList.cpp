#include "SingleLinkedList.h"
#include <iostream>

SingleLinkedList::List::List():
	head(nullptr)
{
}

void SingleLinkedList::List::Insert(int data)
{
	//TODO: Actually review it!

	/*
	 * There could be pointer-to-pointer use
	 * to not to use the condition checking for
	 * head node
	 */
	Node** nodePtr = &head;
	bool allocated = false;

	//Can do break instead of checking condition "!allocated"
	while (!allocated)
	{
		//If head == nullptr for the first iteration
		if (*nodePtr == nullptr)
		{
			//Allocate memory to head for first iteration
			*nodePtr = new Node(data);

			//It is, for the first iteration, "head->data = data;"
			(*nodePtr)->data = data;
			//Could be break and in while(true) loop
			allocated = true;
		}

		//Assign the address of nextNode to nodePtr
		nodePtr = &((*nodePtr)->nextNode);

	}
	//Traverse to the nearest nullptr od Node* nextNode
	//Insert the value to the new node and assign pointers
}

SingleLinkedList::Node::Node(int data)
	:data(data), nextNode(nullptr)
{
}

void SingleLinkedList::List::PrintList()
{
	Node** nodePtr = &head;

	while (*nodePtr != nullptr)
	{
		std::cout << (*nodePtr)->data << " ";
		nodePtr = &((*nodePtr)->nextNode);
	}

	std::cout << std::endl;
}

// It would be nice to be able to remove without iteration, when the place of element is known
// That is passing the element by known address (reference or pointer)
void SingleLinkedList::List::Remove(int elementToRemove)
{
	Node** nodePtr = &head;
	bool isRemoved = false;
	while (isRemoved != true)
	{
 		if ((*nodePtr)->data == elementToRemove)
		{
			//Remove the element from list
			//Rearrange pointers
			
			//If found, delete the prevoius pointer
			//Assign the next pointer to te prevous pointer
			
			//There is a need to store the address of Node* for deleted pointer, to assign its value to
			//the prevoius pointer
			isRemoved = true;
		}
	nodePtr = &((*nodePtr)->nextNode);
	}
	//Iterate over elements of list
	//If found delete and rearrange the pointers
}
