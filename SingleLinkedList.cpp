#include "SingleLinkedList.h"
#include <iostream>

SingleLinkedList::List::List():
	head(nullptr)
{
}

SingleLinkedList::List::~List()
{
	Node** nodePtr = &head;

	while ((*nodePtr) != nullptr)
	{
		Node* nodeToRemove = *nodePtr;
		*nodePtr = (*nodePtr)->nextNode;
		delete nodeToRemove;
	}
}

SingleLinkedList::List::List(const List& list)
{
	Node* const* orgNodePtr = &(list.head);
	Node** copiedNodePtr = &head;
	while(*orgNodePtr != nullptr)
	{
		//Allocate new Node objects to pointers
		*copiedNodePtr = new Node;
		(*copiedNodePtr)->data = (*orgNodePtr)->data;

		//Get the nextNode for original and copied pointer
		orgNodePtr = &((*orgNodePtr)->nextNode);
		copiedNodePtr = &((*copiedNodePtr)->nextNode);
	}
}

SingleLinkedList::Node& SingleLinkedList::List::Front()
{
	return (*head);
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

//Values of member variables are not initailized body of this void-argumented
//constructor, this constructor shouldn't be called in default List constructor,
//because Insert method won't work since it is seeking for non-nullptr Node*
//also, access to uninitialized member nextNode pointer will cause crash

//This ctor can be declared as private, to prevent from calling it outside the class
// but in such design solution it would be necessary to declare friendship between
//this function and SingleLinkedList::List class
//How to design such friendship? Class friedship? Function friendship?
//I think it is impossible to declare ctor of one class outside the class and declare friendship
//with this function in another class
SingleLinkedList::Node::Node()
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

int SingleLinkedList::List::Size()
{
	Node** nodePtr = &head;
	int size = 0;

	while (*nodePtr != nullptr)
	{
		++size;
		nodePtr = &((*nodePtr)->nextNode);
	}
	return size;
}

// It would be nice to be able to remove without iteration, when the place of element is known
// That is passing the element by known address (reference or pointer)

//Returnes true if deletion was successful
void SingleLinkedList::List::Remove(int elementToRemove)
{
	//NO NEED FOR TWO POINTERS-TO-PONITERS
	Node** nodePtr = &head;
	//While not null!
	
	while ((*nodePtr) != nullptr)
	{
 		if ((*nodePtr)->data == elementToRemove)
		{
			//Seems ok, investigate to confirm
			Node* nodeToRemove = *nodePtr;
			*nodePtr = (*nodePtr)->nextNode;
			delete nodeToRemove;
		}
 		else
 		{
 			//For function to remove all elements this won't be valid, since it's omitting one node
 			//Will keyword else here do the job? So we only go to the next node if there was no deletion?
 			nodePtr = &((*nodePtr)->nextNode);
 		}
	}
	//Iterate over elements of list
	//If found delete and rearrange the pointers
}
