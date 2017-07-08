#ifndef SINGLE_LINKED_LIST_H
#define SINGLE_LINKED_LIST_H

namespace SingleLinkedList
{
	class Node
	{
		int data;
		Node* nextNode;
	};

//Must have a node
	class List
	{
	public:
		List();
		void Insert(int data);

	private:
		Node* head;

	};
}

#endif
