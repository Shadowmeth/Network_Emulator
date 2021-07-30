#pragma once
#include <string>

struct Msg
{
	int id; // unique id
	int priority; // 1 to 10
	std::string sourceAddress; // senders machine name
	std::string destinationAddress; // receivers machine name
	std::string payload; // the actual data/message
	std::string trace; // contains the path taken from start machine to the end machine

};

// array of pairs
class Set
{
private:
	int size;
	std::string* setData;

public:
	Set() {
		size = 0;
		setData = nullptr;
	}

	int getSize() {
		return size;
	}

	std::string getData(int index) {
		return setData[index];
	}

	// simple linear search through the array
	bool alreadyExists(std::string& data) {
		for (int i = 0; i < size; i++) {
			if (data == setData[i]) {
				return true;
			}
		}

		return false;
	}

	bool push(std::string& data) {
		if (!alreadyExists(data)) {
			if (size == 0) {
				size++;
				setData = new std::string[size];
				setData[0] = data;
			}
			else {
				std::string* temp = new std::string[size + 1];
				for (int i = 0; i < size; i++) {
					temp[i] = setData[i];
				}
				temp[size] = data;
				delete[] setData;
				size++;
				setData = temp;

			}
			return true;

		}

		return false;
	}

	void clear() {
		delete[] setData;
		setData = nullptr;
		size = 0;
	}

	~Set() {
		delete[] setData;
	}

};

