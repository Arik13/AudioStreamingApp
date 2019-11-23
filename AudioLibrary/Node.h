#pragma once

template <class T>
class Node {
public:
	// construct a new node (allocate memory)
	Node(T val, Node* p) {
		value = val;
		nextNode = p;
	}

	// Returns the value field of the Node
	T val() {
		return value;
	}

	Node<T>* next() {
		return nextNode;
	}

	// Sets the value field of the Node to the given x
	void setVal(T x) {
		value = x;
	}

	// Sets the next field of the Node to the given p
	void setNext(Node<T>* p) {
		nextNode = p;
	}
private:
	T value;
	Node<T>* nextNode;
	void deleteNodes(Node* p);
};
