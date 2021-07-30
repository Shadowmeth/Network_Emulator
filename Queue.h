#pragma once
#include "Node.h"

template <typename T>
class Queue
{
private:
	Node<T>* front;
	Node<T>* rear;
	int size;

public:
	Queue();
	Queue<T>& enqueue(T& data);
	bool dequeue(T&);
	bool isEmpty();
	~Queue();
};

template<typename T>
Queue<T>::Queue()//default values are assigned
{
	front = rear = nullptr;
	size = 0;
}

template<typename T>
Queue<T>& Queue<T>::enqueue(T& data)
{
	Node<T>* temp;
	temp = new Node<T>;
	temp->data = data;
	temp->next = nullptr;
	if (isEmpty()) {
		front = temp;
		rear = temp;
	} else {
		rear->next = temp;
		rear = temp;
	}
	size++;
	return *this;
}

template<typename T>
bool Queue<T>::dequeue(T& ref)
{
	Node<T>* temp;
	if (isEmpty()) {
		return false;
	}
	else {
		ref = front->data;
		temp = front->next;
		delete front;
		front = temp;
		size--;
	}
	return true;
}

template<typename T>
bool Queue<T>::isEmpty()
{
	return size == 0;
}

template<typename T>
Queue<T>::~Queue()//empties the queue until no element is left
{
	T filler;
	while (!isEmpty())
		dequeue(filler);
	size = 0;
}

