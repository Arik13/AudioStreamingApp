/*
 * Assignment 7 - Contains an interface and implementation for working with linked lists
 * Author:		Arik Dicks
 * Student #:	100312559
 * Class:		CPSC 1160 Section 2
 */

#pragma once
#include <cassert>
#include <iostream>
#include "LinkedList.h"

using namespace std;

template <class T> LinkedList<T>::LinkedList() {
	head = NULL;
	tail = NULL;
}

// Deletes every list item in a linked list
template <class T> LinkedList<T>::~LinkedList() {
	Node<T>* q = p->next();
	delete p;
	return deleteList(q);
}

// Returns the length of the linked list
template <class T> int LinkedList<T>::length(Node<T>* p) {
	if (p == nullptr) return 0;
	else return 1 + length(p->next());
}

// Attaches a new list item at the end of a list
template <class T> Node<T>* LinkedList<T>::append(T x) {
	if (p == nullptr) return new Node(x, p);
	Node<T>* q = p;
	while (q->next() != nullptr) {
		q = q->next();
	}
	q->setNext(new Node(x, nullptr));
	return p;
}

// Reverses a linked list and returns the previous tail as the new head
template <class T> Node<T>* LinkedList<T>::reverse(Node<T>* p) {
	// List contains 0 or 1 element
	if (p == nullptr || p->next() == nullptr) return p;

	// List contains 2 elements, point the nodes in the opposite directions and return the 2nd element
	if (p->next()->next() == nullptr) {
		Node<T>* q = p->next();
		p->setNext(nullptr);
		q->setNext(p);
		return q;
	}

	// List is 3 or more elements
	Node<T>* ptrs[3];
	int i = 0, j = 1, k = 2;
	ptrs[i] = p;
	ptrs[j] = ptrs[0]->next();
	ptrs[k] = ptrs[1]->next();

	// Re-link the first node
	ptrs[0]->setNext(nullptr);

	// Walk through the list, relinking the pointers in the opposite direction
	while (ptrs[j]->next() != nullptr) {
		ptrs[j]->setNext(ptrs[i]);
		ptrs[i] = ptrs[k]->next();
		i = (++i) % 3;
		j = (++j) % 3;
		k = (++k) % 3;
	}
	// Re-link the final node
	ptrs[j]->setNext(ptrs[i]);
	return ptrs[j];
}

// Returns the ith list item in a linked list
template <class T> Node<T>* LinkedList<T>::ithNode(Node<T>* p, int i) {
	if (p == nullptr || i == 0) return p;
	return ithNode(p->next(), --i);
}

// Constructs a linked list from the elements of an array
template <class T> Node<T>* LinkedList<T>::array2List(int A[], int n) {
	if (n == 0) return nullptr;
	Node<T>* head = new Node(A[0], nullptr);
	Node<T>* list = head;
	for (int i = 1; i < n; i++) {
		list->setNext(new Node(A[i], nullptr));
		list = list->next();
	}
	return head;
}

// Reads a list of integers from the user, terminated by a non-integer entry, and constructs a linked list from the values
template <class T> Node<T>* LinkedList<T>::readList() {
	Node<T>* head;
	Node<T>* list;
	int x;
	cout << "Input a list of integers, and when done, enter any non number character to exit" << endl;
	cin >> x;

	// Initialize the head of the list
	head = new Node(x, nullptr);
	list = head;
	while (true) {
		cin >> x;
		if (cin.fail()) {	// When a non-integer character is entered, finish constructing the list and clear the stream
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			break;
		}
		list->setNext(new Node(x, nullptr));
		list = list->next();
	}
	return head;
}

// Prints a linked list in sequence, between square brackets, delimited by single spaces
template <class T> void LinkedList<T>::printList(Node<T>* p) {
	if (p == nullptr) {
		cout << "[ ] ";
		return;
	}
	cout << "[ ";
	while (p != nullptr) {
		cout << p->val() << " ";
		p = p->next();
	}
	cout << "] ";
}

