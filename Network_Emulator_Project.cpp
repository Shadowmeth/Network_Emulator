#include <iostream>
#include <string>
#include "Machine.h"


Machine* machineValidate(std::string name, Machine*& machines, int macSize)
{
	for (int i = 0; i < macSize; i++) {
		if (name == machines[i].getName()) {
			return (machines + i);
		}
	}

	return nullptr;
}

int main()
{
	bool check = true;
	std::string choice;
	std::string fileName;
	std::cout << "Enter file name to read an existing network: ";
	std::cin >> fileName;
	std::ifstream read;
	read.open(fileName);
	std::string a;
	if (!read.eof())
		std::getline(read, a, '\n');

	int m_count = std::count(a.begin(), a.end(), 'M');
	int r_count = std::count(a.begin(), a.end(), 'R');

	Machine* machines = new Machine[m_count];
	ListRouter* routers = new ListRouter[r_count];

	int i = 0, j = 0, x = 0;
	while (!read.eof()) {

		std::getline(read, a, ',');

		if (a[0] == 'M') {
			machines[i].setMachineName(a);
			machines[i].setMachineID(x);
			i++; x++;
		}
		else if (a[0] == 'R') {
			routers[j].setRouterName(a);
			routers[j].setRouterID(x);
			j++; x++;
		}
		std::getline(read, a, '\n');
	}
	read.close();
	for (i = 0; i < m_count; i++) {
		machines[i].getMachineAndRouter(machines, routers, m_count, r_count);
		machines[i].makeTableList(fileName);
	}

	for (i = 0; i < r_count; i++) {
		routers[i].getMachineAndRouter(machines, routers, m_count, r_count);
		routers[i].makeRoutingTable(fileName);
	}

	int** adjMatrix = new int* [m_count + r_count];
	for (int i = 0; i < m_count + r_count; i++) {
		adjMatrix[i] = new int[m_count + r_count];
	}
	read.open(fileName);
	i = 0;
	std::getline(read, a, '\n');
	while (!read.eof()) {
		std::getline(read, a, ',');
		for (int j = 0; j < m_count + r_count; j++) {
			if (j != m_count + r_count - 1)
				std::getline(read, a, ',');
			else
				std::getline(read, a, '\n');
			if (a == "?")
				adjMatrix[i][j] = 0;
			else
				adjMatrix[i][j] = stoi(a);
		}
		i++;
		if (i == m_count + r_count)
			break;
	}
	read.close();
	
	while (true) {
		std::cout << "Enter 1 To Send Message.\n";
		std::cout << "Enter 2 To Print Path.\n";
		std::cout << "Enter 'Exit' To Terminate the Program.\n";
		std::cout << "\nEnter command: ";
		std::cin.ignore();
		std::getline(std::cin, choice);
	
		std::cout << "\n";
		if (int(choice[0]) == int('1')) {
			std::cout << "Select source: \n\n";
			for (i = 0; i < m_count; i++) {
				std::cout << "Enter " << i << " for " << machines[i].getName() << ".\n";

			}
			while (i < 0 || i >= m_count) {
				std::cout << "\nEnter choice: ";
				std::cin >> i;
			}
			std::cout << "Select destination:\n\n";
			for (j = 0; j < m_count; j++) {
				std::cout << "Enter " << j << " for " << machines[j].getName() << ".\n";
			}
			while (j < 0 || j >= m_count || i == j) {
				std::cout << "\nEnter choice: ";
				std::cin >> j;
			}
			machines[i].sendMessageList(machines[j].getName());

		}
		else if (int(choice[0]) == int('2')) {
			std::cout << "Select source:\n\n";
			for (i = 0; i < m_count; i++) {
				std::cout << "Enter " << i << " for " << machines[i].getName() << ".\n";
			}

			std::cout << "Enter " << m_count << " for *.\n";
			i++;

			while (i < 0 || i >= m_count + 1) {
				std::cout << "\nEnter choice: ";
				std::cin >> i;
				if (i < 0 || i >= m_count + 1)
					std::cout << "\nInvalid choice!\n";
			}

			std::cout << "Select destination:\n\n";
			for (j = 0; j < m_count; j++) {
				std::cout << "Enter " << j << " for " << machines[j].getName() << ".\n";
			}
			std::cout << "Enter " << m_count << " for *.\n";
			j++;

			while (j < 0 || j >= m_count + 1 || i == j) {
				std::cout << "\nEnter choice: ";
				std::cin >> j;
				if (j < 0 || j >= m_count + 1 || i == j)
					std::cout << "\nInvalid choice! \n";
			}

			if (i == m_count) {
				// machine1 is *
				Machine* m = machineValidate(machines[j].getName(), machines, m_count);
				if (m == nullptr) {
					std::cout << "Machine destination not found!\n";
				}
				else {
					for (int i = 0; i < m_count; i++) {
						machines[i].printPathList(m);
					}
				}

			} 
			else if (j == m_count) {
				// machine2 is *
				Machine* m = machineValidate(machines[i].getName(), machines, m_count);
				if (m == nullptr) {
					std::cout << "Machine source not found!\n";
				}
				else {
					for (int i = 0; i < m_count; i++) {
						Machine* machine1 = (machines + i);
						m->printPathList(machine1);
					}
				}
			}
			else {
				// both machines are present
				Machine* m = machineValidate(machines[j].getName(), machines, m_count);
				if (m == nullptr) {
					std::cout << "Machine destination not found!\n";
				}
				else {
					Machine* machine1 = machineValidate(machines[i].getName(), machines, m_count);
					if (machine1 == nullptr) {
						std::cout << "Machine source not found!\n";
					}
					else {
						machine1->printPathList(m);
					}
				}

			}
		}
		else if (choice == "Exit") {
			break;
		}
		else {
			std::cout << "\nInvalid choice!\n";
		}
		std::cout << "\n\n";

	}

}