#ifndef SINGLE_LINKED_LIST_H
#define SINGLE_LINKED_LIST_H

namespace SingleLinkedList
{
	class Node
	{
	public:
		Node();
		Node(int data);

		int data;
		Node* nextNode;
	};

//Must have a node
	class List
	{
	public:
		List();
		~List();
		List(const List& list);
		void Insert(int data);
		void PrintList();
		void Remove(int elementToRemove);
		Node& Front();
	private:
		Node* head;

	};
}

#endif
