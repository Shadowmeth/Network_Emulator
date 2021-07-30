#include "Machine.h"

int Machine::id = 89; // unique id is given default initial value

Machine::Machine()
{
	machineName = "";
	machineID = 0;
}

void Machine::setMachineName(std::string& name)
{
	machineName = name;
}

void Machine::setMachineID(int& x)
{
	machineID = x;
}

int Machine::getID()
{
	return machineID;
}

std::string& Machine::getName()
{
	return machineName;
}

void Machine::receiveMessage(Msg& msg)
{
	msg.trace += machineName;
	std::ofstream write;
	write.open("path.txt", std::ios::app | std::ios::out);
	write << msg.id << ":";
	write << msg.trace << ":";
	write << msg.payload << "\n";

}

// message is made here
void Machine::sendMessageList(std::string& x)
{
	Msg msg;
	bool check = false;
	while (check) {
		std::cout << "Enter priority: ";
		std::cin >> msg.priority;
		if (msg.priority >= 0 && msg.priority <= 10) {
			check = false;
		}
		else {
			std::cout << "Priority out of range!\n\n";
		}

	}

	msg.trace = machineName + ":";
	msg.sourceAddress = machineName;
	std::cout << "Enter message: ";
	std::cin.ignore();
	std::getline(std::cin, msg.payload);
	msg.destinationAddress = x;
	msg.id = id;
	id++;
	outQueue.enqueue(msg);
	routers->inQueueEnqueue(msg);
}

void Machine::printPathList(Machine*& m)
{
	std::cout << machineName << " -> ";
	routers->printPath(m);
}

void Machine::sendBulkMessageList(Msg& msg)
{
	msg.trace = machineName + ":";
	routers->inQueueEnqueue(msg);
}

void Machine::getMachineAndRouter(Machine*& machines, ListRouter*& routers, int macSize, int routSize)
{
	this->machines = machines;
	this->routers = routers;
	this->machineSize = macSize;
	this->routerSize = routSize;
}

void Machine::makeTableList(std::string& fileName)
{
	Graph graph;
	List<int>* temp;
	temp = graph.setSource(machineID, fileName);
	for (int i = 0; i < machineSize; i++) {
		int hello;
		temp[i].getNode(1, hello);
		if (hello != machines[i].machineID) {
			for (int j = 0; j < routerSize; j++) {
				if (routers[j].getRouterID() == hello) {
					routers = (routers + j); // pointer arithmetic
					routerSize = 1;
					break;
				}
			}
		}
	}
}

void Machine::makeTableList(int** matrix, int size)
{
	Graph graph;
	List<int>* temp;
	temp = graph.setSource(machineID, matrix, machineSize + size);
	for (int i = 0; i < machineSize; i++) {
		int hello;
		temp[i].getNode(1, hello);
		if (hello != machines[i].machineID) {
			for (int j = 0; j < routerSize; j++) {
				if (routers[j].getRouterID() == hello) {
					routers = (routers + j);
					routerSize = 1;
					break;
				}
			}
		}
	}

}

Machine::~Machine()
{

}
