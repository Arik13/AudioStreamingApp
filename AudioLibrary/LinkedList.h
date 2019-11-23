#pragma once

#pragma once
#include "Node.h"

template <class T>
class LinkedList {
public:
	LinkedList();
	~LinkedList();							// Deletes every list item in a linked list
	int length(Node<T>* p);					// Returns the length of the linked list
	void append(T x);						// Attaches a new list item at the end of a list
	void prepend(T x);						// Attaches a new list item at the end of a list
	Node<T>* reverse(Node<T>* p);			// Reverses a linked list and returns the previous tail as the new head
	Node<T>* ithNode(Node<T>* p, int i);	// Returns the ith list item in a linked list
	Node<T>* array2List(int A[], int n);	// Constructs a linked list from the elements of an array
	void printList(Node<T>* p);				// Prints a linked list in sequence, between square brackets, delimited by single spaces
private:
	Node<T>* head;
	Node<T>* tail;
};
