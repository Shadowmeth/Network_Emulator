#pragma once

template<typename T>
class MaxHeap
{
private:
	struct HeapNode {
		T data;
		int priority;
	} *root;
	int rootSize;

public:
	MaxHeap() {
		rootSize = 0;
		root = nullptr;
	}

	int getSize() {
		return rootSize;
	}

	void insert(T data, int priority) {
		if (rootSize == 0) {
			// there is no root yet, new root will be created
			rootSize++;
			root = new HeapNode[rootSize];
			root[0].data = data;
			root[0].priority = priority;
		}
		else {
			// there is already a populated array, create new node and add to its end
			HeapNode* temp = new HeapNode[rootSize + 1];
			for (int i = 0; i < rootSize; i++) {
				temp[i] = root[i];
			}
			temp[rootSize].data = data;
			temp[rootSize].priority = priority;
			rootSize++;
			delete[] root;
			root = temp;
			shiftUp(rootSize - 1);

		}
	}

	void shiftUp(int index) {
		int parent = (index - 1) / 2;
		while (parent >= 0) {
			if (root[index].priority > root[parent].priority) {
				// MaxHeap properties not met
				// heapify the tree
				HeapNode temp;
				temp = root[parent];
				root[parent] = root[index];
				root[index] = temp;
				index = parent;
				parent = (index - 1) / 2;
			}
			else {
				// MaxHeap properties already met, break the loop
				break;
			}
		}
		
	}

	bool deleteNode(T& ref) {
		if (rootSize != 0) {
			if (rootSize == 1) {
				// root is deleted
				ref = root->data;
				delete[] root;
				rootSize--;
				return true;
			}
			else {
				HeapNode* temp = new HeapNode[rootSize - 1];
				ref = root->data;
				// first node is getting deleted
				root[0] = root[rootSize - 1];
				for (int i = 0; i < rootSize - 1; i++) {
					temp[i] = root[i];
				}
				rootSize--;
				delete[] root;
				root = temp;
				shiftDown();
				return true;
			}
		}

		return false;
	}

	// potential error here
	int max(int i, int j) {
		// min value index is returned
		if (i < rootSize) {
			if (j < rootSize) {
				if (root[i].priority < root[j].priority)
					return j;
				else if (root[i].priority > root[j].priority)
					return i;
			}

			return i;
		}
		else if (j < rootSize)
			return j;
		else
			return -1;
	}

	void shiftDown() {
		// heapify the tree
		int index = 0;
		while (index < rootSize) {
			int temp = max(2 * index + 1, 2 * index + 2);
			if (temp == -1) // index out of range
				break;
			else if (root[index].priority < root[temp].priority) {
				// swapping of nodes is needed here to maintain the heap structure
				HeapNode tempNode;
				tempNode = root[temp];
				root[temp] = root[index];
				root[index] = tempNode;
				index = temp;
			}
			else
				break;
		}

	}

	~MaxHeap() {
		int temp = rootSize;
		T useless;
		for (int i = 0; i < temp; i++) {
			deleteNode(useless);
		}
	}

};
