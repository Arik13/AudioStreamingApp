#pragma once
#include "Node.h"

template <class T>
class Queue {
public:
	Queue() {
		head = nullptr;
		tail = nullptr;
		size = 0;
	}
	~Queue() {
		//deleteList(head);
	}
	void enqueue(T element) {
		if (size == 0) {
			tail = new Node<T>(element, nullptr);
			head = tail;
		}
		else {
			tail->setNext(new Node<T>(element, nullptr));
			tail = tail->next();
		}
		size++;
	}
	T dequeue() {
		T element;
		if (size == 0) throw "Nothing to dequeue";
		else if (size == 1) {
			element = head->val();
			delete head;
			head = nullptr;
			tail = nullptr;
		}
		else {
			element = head->val();
			Node<T>* p = head->next();
			delete head;
			head = p;
		}
		size--;
		return element;
	}
	T peek() {
		return head->val();
	}
	bool isEmpty() {
		return size == 0;
	}
private:
	Node<T>* head;
	Node<T>* tail;
	int size;
};