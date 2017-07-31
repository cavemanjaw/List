#ifndef SINGLE_LINKED_LIST_H
#define SINGLE_LINKED_LIST_H
#include <iostream>

namespace SingleLinkedList
{
	template<typename Data>
	class Node
	{
	public:
		Node();
		Node(Data data);

		Data data;
		Node* nextNode;
	};

//Must have a node
	template<typename Data>
	class List
	{
	public:
		List();
		~List();
		List(const List<Data>& list);
		void Insert(Data data);
		void PrintList();
		void Remove(Data elementToRemove);
		Node<Data>& Front();
		int Size();
	private:
		Node<Data>* head;

	};
}

template<typename Data>
SingleLinkedList::List<Data>::List():
	head(nullptr)
{
}

template<typename Data>
SingleLinkedList::List<Data>::~List()
{
	Node<Data>** nodePtr = &head;

	while ((*nodePtr) != nullptr)
	{
		Node<Data>* nodeToRemove = *nodePtr;
		*nodePtr = (*nodePtr)->nextNode;
		delete nodeToRemove;
	}
}

template<typename Data>
SingleLinkedList::List<Data>::List(const List& list)
{
	Node<Data>* const* orgNodePtr = &(list.head);
	Node<Data>** copiedNodePtr = &head;
	while(*orgNodePtr != nullptr)
	{
		//Allocate new Node objects to pointers
		*copiedNodePtr = new Node<Data>;
		(*copiedNodePtr)->data = (*orgNodePtr)->data;

		//Get the nextNode for original and copied pointer
		orgNodePtr = &((*orgNodePtr)->nextNode);
		copiedNodePtr = &((*copiedNodePtr)->nextNode);
	}
}

template<typename Data>
SingleLinkedList::Node<Data>& SingleLinkedList::List<Data>::Front()
{
	return (*head);
}

template<typename Data>
bool SingleLinkedList::List<Data>Empty()
{
	//We take advantage of implicit conversion here, make sure it works
	//return !head;
	retrun (head == nullptr) ? 1 : 0;
}

template<typename Data>
void SingleLinkedList::List<Data>::Insert(Data data)
{
	//TODO: Actually review it!

	/*
	 * There could be pointer-to-pointer use
	 * to not to use the condition checking for
	 * head node
	 */
	Node<Data>** nodePtr = &head;
	bool allocated = false;

	//Isn't this unsafe if we would not find the nullptr node?
	while (true)
	{
		//If head == nullptr for the first iteration
		if (*nodePtr == nullptr)
		{
			//Allocate memory to head for first iteration
			*nodePtr = new Node<Data>(data);
			(*nodePtr)->data = data;
			break;
		}

		//Assign the address of nextNode to nodePtr
		nodePtr = &((*nodePtr)->nextNode);

	}
	//Traverse to the nearest nullptr od Node* nextNode
	//Insert the value to the new node and assign pointers
}

template<typename Data>
SingleLinkedList::Node<Data>::Node(Data data)
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
template<typename Data>
SingleLinkedList::Node<Data>::Node()
{
}

template<typename Data>
void SingleLinkedList::List<Data>::PrintList()
{
	Node<Data>** nodePtr = &head;

	while (*nodePtr != nullptr)
	{
		std::cout << (*nodePtr)->data << " ";
		nodePtr = &((*nodePtr)->nextNode);
	}

	std::cout << std::endl;
}

template<typename Data>
int SingleLinkedList::List<Data>::Size()
{
	Node<Data>** nodePtr = &head;
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
template<typename Data>
void SingleLinkedList::List<Data>::Remove(Data elementToRemove)
{
	//NO NEED FOR TWO POINTERS-TO-PONITERS
	Node<Data>** nodePtr = &head;
	//While not null!

	while ((*nodePtr) != nullptr)
	{
 		if ((*nodePtr)->data == elementToRemove)
		{
			//Seems ok, investigate to confirm
			Node<Data>* nodeToRemove = *nodePtr;
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

#endif

//Test for contribution visibility
