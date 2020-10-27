#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

namespace DoublyLinkedList
{
	template<typename Data>
	class Node
	{
	public:
		Node();
		Node(Data data);
		Node(Data&& data);

		Data data;
		Node* nextNode;
		Node* prevNode;
	};

	template<typename Data>
	class List
	{
	public:
		List();
		~List();
		List(const List<Data>& list);
		List<Data>& operator=(const List<Data>& rhs);
	private:
		Node<Data>* head;
		Node<Data>* tail;
	};
}

template<typename Data>
DoublyLinkedList::List<Data>::List() : head(nullptr), tail(nullptr)
{
}

// TODO: Fork it onto two threads? The synchronization cost would be large?
// The overhead of creating and starting the threads?
template<typename Data>
DoublyLinkedList::List<Data>::~List()
{
	Node<Data>** head_pp = &head;
	Node<Data>** tail_pp = &tail;

	// TODO: Check for empty list at the beginning?
	// TODO: Maybe this is not needed - initialize only in the while loop?
	// Right now is needed for the delete at the end of function
	Node<Data>** leftNodeToDelete = head_pp;
	Node<Data>** rightNodeToDelete = tail_pp;
	// break conditions
	// if the addresses of head_pp and tail_pp are equal
	// both iterators are pointing to the same node - odd elements in list case
	// if the address of next node from node pointed by head_pp is equal to
	// the node pointed by tail_pp - even elements in list case
	while (head_pp != tail_pp)
	{
		// assign nodes to delete
		leftNodeToDelete = head_pp;
		rightNodeToDelete = tail_pp;

		// iterate pointers
		head_pp = (*head_pp)->nextNode;
		tail_pp = (*tail_pp)->prevNode;

		// delete nodes
		delete *leftNodeToDelete;
		delete *rightNodeToDelete;

		if((*head_pp)->nextNode == *tail_pp)
		{
			delete head_pp;
			delete tail_pp;
			return;
		}
	}
	// Both pointers pointing to the same node - invoke delete on one of them
	// Will call delete on nullptr of no elements in list
	delete *leftNodeToDelete;
}

#endif
