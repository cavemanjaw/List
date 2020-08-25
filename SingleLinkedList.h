#ifndef SINGLE_LINKED_LIST_H
#define SINGLE_LINKED_LIST_H

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

		void Insert(Data data);
		void Insert(Node<Data>* node_p);
		void Insert(Node<Data>& node);

		void Clear();
		void Remove(Data elementToRemove);
		Node<Data>& Front();
		unsigned Size(); // std::size_t?
		bool Empty();
		void Reverse();

		//TODO: Should be private, moved here temporarily
		Node<Data>* head;

	private:

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
	//TODO: What if head is nullptr? std::list::front yields undefined behavior if container is empty
	return (*head);
}

template<typename Data>
bool SingleLinkedList::List<Data>::Empty()
{
	//TODO: We take advantage of implicit conversion here, make sure it works
	//return !head;
	return (head == nullptr) ? true : false;
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
void SingleLinkedList::List<Data>::Reverse()
{
	Node<Data>** headPtr = &head;

	Node<Data>* previousNode = nullptr; 
	Node<Data>* currentNode = *headPtr;
	Node<Data>* nextNode;

	//Check the logic!
	while (currentNode != nullptr)
	{
		nextNode = currentNode->nextNode;
		currentNode->nextNode = previousNode;
		previousNode = currentNode;
		currentNode = nextNode;
	}
	*headPtr = previousNode;
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
