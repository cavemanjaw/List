#ifndef SINGLE_LINKED_LIST_H
#define SINGLE_LINKED_LIST_H

namespace SingleLinkedList
{
	class Node
	{
	public:
		Node(int data);

		int data;
		Node* nextNode;
	};

//Must have a node
	class List
	{
	public:
		List();
		void Insert(int data);
		void PrintList();

	private:
		Node* head;

	};
}

#endif
