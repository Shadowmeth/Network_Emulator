#pragma once
#include "Node.h"
#include <iostream>

template <typename T>
class List
{
private:
	int size;
	Node<T>* head;

public:
	List();
	Node<T>* insert(T x, int index);
	bool isEmpty();
	bool getNode(int x, T&);
	T getNode(T data) const;
	int getSize() const;
	List<T>& display();
	List<T>& deleteNode(T&);
	bool deleteNodeByIndex(int index, T& ref);
	~List();

};

template <typename T>
List<T>::List()
{
	head = nullptr;
	size = 0;
}

template <typename T>
Node<T>* List<T>::insert(T x, int index)
{
	if (index < 0) {
		return nullptr; // obviously index can't be negative
	}

	int i = 1;
	Node<T>* temp = head;
	while (temp && index > i) {
		temp = temp->next;
		i++;
	}

	if (index > 0 && temp == nullptr) {
		return nullptr;
	}

	Node<T>* newNode = new Node<T>;
	newNode->data = x;
	if (index == 0) {
		// insert at beginning
		newNode->next = head;
		head = newNode;
	}
	else {
		newNode->next = temp->next;
		temp->next = newNode;
	}
	size++; // we increment the size every time we add a new node to the list
	// note that this is never executed if the indexes were invalid
	return newNode; // the function returns the address of the newly inserted node in the list
}

template <typename T>
int List<T>::getSize() const
{
	return size;
}

template <typename T>
bool List<T>::isEmpty()
{
	return size == 0;
}

template <typename T>
bool List<T>::getNode(int index, T& ref)
{
	if (!isEmpty() && index <= size) {
		// we want to ensure that the node we need even exists in the list
		Node<T>* temp = head;
		for (int i = 0; i < index; i++) {
			temp = temp->next;
		}
		ref = temp->data;
		// not that we are assigning the data to ref instead of returning it as 
		// a return value of function call
		return true; // we got the node we were looking for
	}

	return false; // failed to get the node
}

template <typename T>
T List<T>::getNode(T data) const
{
	if (!isEmpty()) {
		Node<T>* temp = head;
		while (temp) {
			if (temp->data == data) {
				return temp;
			}
		}
	}
	// we reach here only if the data doesn't exist in any node in the list
	return static_cast<T>(nullptr);
}

template <typename T>
List<T>& List<T>::display()
{
	// display the list
	Node<T>* temp = head;
	while (temp) {
		std::cout << temp->data;
		temp = temp->next;
	}
	
	// and return the reference back
	return *this;
}

// use ref only if this function returns true
template <typename T>
bool List<T>::deleteNodeByIndex(int index, T& ref)
{
	if (!isEmpty() && index <= size) {
		Node<T>* last = nullptr;
		Node<T>* temp = head;
		int i = 0;
		while (temp && i != index) {
			last = temp;
			temp = temp->next;
			i++;
		}

		if (temp) {
			if (last) {
				// not head
				last->next = temp->next;
				ref = temp->data;
				delete temp;
			}
			else {
				// head
				head = temp->next;
				ref = temp->data;
				delete temp;
			}
			--size;
			return true;

		}

	}

	return false;
}

template <typename T>
List<T>& List<T>::deleteNode(T& ref)
{
	if (!isEmpty()) {
		Node<T>* last = nullptr;
		Node<T>* temp = head;
		int i = 1;
		while (temp && temp->data != ref) {
			last = temp;
			temp = temp->next;
			i++;
		}
		if (temp) {
			if (last) {
				// not head
				last->next = temp->next;
				delete temp;
			}
			else {
				// head
				head = temp->next;
				delete temp;
			}
			--size;
		}

	}
	
	return *this; // return the list no matter if we deleted the data or not
}

template <typename T>
List<T>::~List()
{
	// update head and keep deleting the old head
	while (head) {
		Node<T>* temp = head;
		head = head->next;
		delete temp;
	}
	size = 0; // and obviously set size back to 0 again
}
