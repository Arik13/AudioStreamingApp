#pragma once
#include <mutex>
#include <atomic>
#include <iostream>

template <class T>
class QueueArray {
public:
	QueueArray() {
		arr = new T[BUFFER_SIZE];
		hi = BUFFER_SIZE - 1;
		lo = BUFFER_SIZE - 1;
		size = 0;
	}
	QueueArray(int bufferSize) : BUFFER_SIZE(bufferSize) {
		arr = new T[BUFFER_SIZE];
		hi = BUFFER_SIZE - 1;
		lo = BUFFER_SIZE - 1;
		size = 0;
	}
	~QueueArray() {
		delete arr;
	}
	bool push(T element) {
		std::lock_guard<std::mutex> lock(queueMutex);
		if (size == BUFFER_SIZE) throw "Buffer overflow";
		arr[lo--] = element;
		lo = (lo == -1) ? BUFFER_SIZE -1 : lo;
		size++;
		return true;
	}
	bool pop(T& element) {
		std::lock_guard<std::mutex> lock(queueMutex);
		if (size == 0) return false;
		element = arr[hi--];
		hi = (hi == -1)? BUFFER_SIZE -1 : hi;
		size--;
		return true;
	}
	T peek() {
		std::lock_guard<std::mutex> lock(queueMutex);
		return arr[hi];
	}
	bool empty() {
		std::lock_guard<std::mutex> lock(queueMutex);
		return size == 0;
	}
	int length() {
		std::lock_guard<std::mutex> lock(queueMutex);
		return size;
	}
private:
	std::mutex queueMutex;
	T* arr;
	int hi;
	int lo;
	int size;
	const int BUFFER_SIZE = 1024;
};