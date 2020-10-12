#ifndef SINGLE_LINKED_LIST_H
#define SINGLE_LINKED_LIST_H

// For std::function
#include <functional>

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

	template<typename Data>
	class List
	{
	public:
		List();
		~List();
		List(const List<Data>& list);
		List<Data>& operator=(const List<Data>& rhs);

		// TODO: Should hide implementation details and three version could be implemented:
		//       1. Insert node at the beginning - modify the head
		//       2. After a given node (or a value)
		//       3. Insert node at the end of the list
		// Name of a function should provide an abstraction of what is being done in the function body,
		// so InsertAfter() would be a good name for such function
		void Insert(Data data);
		void Insert(Node<Data>* node_p);
		void Insert(Node<Data>& node);

		Data PopFront();
		void PushFront(Data data);
		void PushFront(Data&& data);

		// Should remove element that is true by '==' comparison
		// What is usually return for such comparison function (probably bool?) what argument should this function take?
		// is std::function a template template argument? How to make it pass various number of possible argument types?
		// template arument 'class Predicate' that when operator() of the call is invoked a bool gets returned?
		// The predicate operator() or the lambda function of a binded function has to take an argument of Data type
		bool RemoveIf(Data elementToRemove, std::function<bool(const Data& data)>);

		// Resize(n) - could remove the element if n is less than current list size or allocate if n is greater than
		//             the current number of elements (probably has a big impact on other functions (to check
		//             if the allocation would be needed - for Insert for example)
		// RemoveIf() - could be feeded a general callable object (function, function obect, lambda), so it's better than function pointer
		// RemoveDuplicates() - this could remove all the same elements from the list
		// Unique() - would be based on == operator, std::forward_list removes only adjacent equal values
		// Slice() or SpliceAfter()
		// Merge()
		// Sort() - how this could be tailored to list data structure?
		void Clear();
		// TODO: Pointer to a element and reference to a element that would remove the node
		void Remove(Data elementToRemove);
		Node<Data>& Front();
		unsigned Size(); // std::size_t?
		bool Empty();
		void Reverse();
		void ReverseRecursive();
		void Reverse(Node<Data>* lastNode_p);

	private:
		Node<Data>* head;
		void ReverseRecursiveHelper(Node<Data>* previousNode, Node<Data>* currentNode);

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
void SingleLinkedList::List<Data>::Clear()
{
	this->~List();
	head = nullptr;
}

//TODO: Copy-and-swap idiom could give strong exception guarantee
template<typename Data>
SingleLinkedList::List<Data>::List(const List& list):
	head(nullptr)
{
	Node<Data>* const* orgNodePtr = &(list.head);
	Node<Data>** copiedNodePtr = &head;

	while (*orgNodePtr != nullptr)
	{
		//Allocate new Node objects to pointers
		*copiedNodePtr = new Node<Data>;
		(*copiedNodePtr)->data = (*orgNodePtr)->data;

		//Get the nextNode for original and copied pointer
		orgNodePtr = &((*orgNodePtr)->nextNode);
		copiedNodePtr = &((*copiedNodePtr)->nextNode);
	}
	*copiedNodePtr = nullptr;
}

//TODO: Actually test the performance of two described methods
template<typename Data>
SingleLinkedList::List<Data>& SingleLinkedList::List<Data>::operator=(const List<Data>& rhs)
{
	//There might be a need for allocating new memory to the list
	/*
	* Sure we can destroy whole array and create a new one reusing copy ctor code.
	* The drawback is, that this would be possibly less efficient.
	*/
	Node<Data>* const* rhsNodePtr = &(rhs.head);
	Node<Data>** nodePtr = &head;
	while (*rhsNodePtr)
	{
		// Memory is not allocated for left hand side
		if (*nodePtr == nullptr)
		{
			*nodePtr = new Node<Data>;
		}
		(*nodePtr)->data = (*rhsNodePtr)->data;
		
		//Get the next node of left and right side lists
		nodePtr = &((*nodePtr)->nextNode);
		rhsNodePtr = &((*rhsNodePtr)->nextNode);
	}
	return *this;
}

// Here is the other, alternative method
/*
template<typename Data>
SingleLinkedList::List<Data> SingleLinkedList::List<Data>::operator=(const List<Data>& rhs)
{
	~List<Data>();
	List<Data>(rhs);
}
*/

template<typename Data>
SingleLinkedList::Node<Data>& SingleLinkedList::List<Data>::Front()
{
	// TODO: What if head is nullptr?
	// std::list::front yields undefined behavior if container is empty
	return (*head);
}

template<typename Data>
Data SingleLinkedList::List<Data>::PopFront()
{
	// Pop the object - return and remove from the list
	// TODO: Creating a copy is not very efficient for large object of 'Data'
	// TODO: RVO kicking in?
	// If the object would have a control block of separately allocated pointer and data
	// then in case of assigning to a heap in the a caller of PopFront the object could
	// be sort of "moved" to a pointer (just assign - this would need the return value to be a pointer).
	Data dataToReturn = head->data;
	Node<Data>* nodeToRemove = head;
	head = head->nextNode;
	delete nodeToRemove;
	return dataToReturn;
}

// TODO: Should the argument have value semantics?
//       What about large objects, they could be moved from
//       The value semantics argument would be copied to times (but maybe can be moved in the body of PushFront?)
// Possibly two versions could be implemented:
// 1. Copy to function argument using value semantics (if called with an l-value) and the move from the argument
// 2. Move right away in the caller (?) (how will that behave in templated version of PushFront?)
// TODO: Unversal (forwarding) references issue

// Version 1 - value semantics (in case PushFront is called with an l-value)
// copy the object in argument list and move inside the body of PushFront
template<typename Data>
void SingleLinkedList::List<Data>::PushFront(Data data
{

}

// Version 2 - move semantics (in case PushFront is called with an r-value)
template<typename Data>
void SingleLinkedList::List<Data>::PushFront(Data&& data)
{

}

template<typename Data>
bool SingleLinkedList::List<Data>::Empty()
{
	return !head;
}

template<typename Data>
void SingleLinkedList::List<Data>::Insert(Data data)
{
	Node<Data>** nodePtr = &head;

	//Traverse to the nearest nullptr od Node* nextNode
	//Insert the value to the new node and assign pointers
	while (true)
	{
		//If head == nullptr for the first iteration
		if (*nodePtr == nullptr)
		{
			//Allocate memory to head for first iteration
			*nodePtr = new Node<Data>(data); //TODO: In case of "safe" list this would be bad
			(*nodePtr)->data = data;
			break;
		}
		else
		{
		//Assign the address of nextNode to nodePtr
			nodePtr = &((*nodePtr)->nextNode); //TODO: There is no need to reassign the pointers if nullptr has been found
		}
	}
}

//TODO: Investigate if it could be done more efficiently
template<typename Data>
void SingleLinkedList::List<Data>::Reverse()
{
	Node<Data>* previousNode = nullptr; 
	Node<Data>* currentNode = head;
	Node<Data>* nextNode;

	//Check the logic!
	while (currentNode != nullptr)
	{
		nextNode = currentNode->nextNode;
		currentNode->nextNode = previousNode;
		previousNode = currentNode;
		currentNode = nextNode;
	}
	head = previousNode;
}


template<typename Data>
void SingleLinkedList::List<Data>::ReverseRecursiveHelper(Node<Data>* previousNode, Node<Data>* currentNode)
{
	if (currentNode->nextNode != nullptr)
	{
		Node<Data>* nextNode = currentNode->nextNode;
		currentNode->nextNode = previousNode;
		ReverseRecursiveHelper(currentNode, nextNode);
	}
	else // base case - currentNode is the last node in the list
	{
		head = currentNode;
	}
}

// TODO: Could it be done without the help of a helper function to pass the argument down the recursive stack call?
template<typename Data>
void SingleLinkedList::List<Data>::ReverseRecursive()
{
	ReverseRecursiveHelper(nullptr, head);
}


// TODO: Could be done only for double-linked list,
// we do not have a pointer to previous node to go in reverse order
// with the back iterator
template<typename Data>
void SingleLinkedList::List<Data>::Reverse(Node<Data>* lastNode_p)
{
	// If the last node is known we could swap the elements
	//head
	Node<Data>* frontIter_p = head;
	Node<Data>* backIter_p = lastNode_p; // do not need to create additional variable, could use lastNode_p

	while (true)
	{
		frontIter_p = backIter_p->nextNode;
		backIter_p = frontIter_p->nextNode;

	}

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
unsigned SingleLinkedList::List<Data>::Size()
{
	Node<Data>** nodePtr = &head;
	unsigned size = 0;

	while (*nodePtr != nullptr)
	{
		++size;
		nodePtr = &((*nodePtr)->nextNode);
	}
	return size;
}

// It would be nice to be able to remove without iteration, when the place of element is known
// That is passing the element by known address (reference or pointer) - overloaded function?
// Returns true if deletion was successful?
// Removes all the elements that match - traverses the whole list
template<typename Data>
void SingleLinkedList::List<Data>::Remove(Data elementToRemove)
{
	Node<Data>** previousNodePtr = &head;
	Node<Data>** nodePtr = &head;

	// Iterate over elements of list
	// If found delete and rearrange the pointers
	while ((*nodePtr) != nullptr)
	{
 		if ((*nodePtr)->data == elementToRemove)
		{
			Node<Data>* nodeToRemove = *nodePtr;
			(*previousNodePtr)->nextNode = (*nodePtr)->nextNode; // Swapping element with itself for head only List
			delete nodeToRemove;
			*nodePtr = nullptr; // Can be reached with delete in ~List() in case of head only List
		}
 		else
 		{
 			// For function to remove all elements this won't be valid, since it's omitting one node
 			// Will keyword else here do the job? So we only go to the next node if there was no deletion?
 			previousNodePtr = nodePtr;
 			nodePtr = &((*nodePtr)->nextNode);
 		}
	}
}

#endif

//Test for contribution visibility
