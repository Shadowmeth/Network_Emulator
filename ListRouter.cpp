#include "ListRouter.h"


ListRouter::ListRouter()
{
	outQueueSize = 0;
	routerName = "";
}

void ListRouter::setRouterName(std::string& name)
{
	routerName = name;
}

void ListRouter::setRouterID(int& id)
{
	routerID = id;
}

void ListRouter::sendMessage()
{
	Msg a;
	for (int i = 0; i < outQueueSize; i++) {
		if (pair[i].outQueue.dequeue(a) == true)
			outQueueDequeue(a);
	}
}

int ListRouter::getRouterID()
{
	return routerID;
}

std::string& ListRouter::getRouterName()
{
	return routerName;
}

void ListRouter::inQueueEnqueue(Msg& a)
{
	a.trace += routerName + ":"; // message trace is updated
	inQueue.insert(a, a.priority); // message is inserted into the queue according to its priority
	inQueueDequeue();
	sendMessage();
}

void ListRouter::printPath(Machine*& m)
{
	bool check = false;
	for (int i = 0; i < destinationTable.getSize(); i++) {
		std::string str;
		destinationTable.getNode(i, str);
		if (m->getName() == str) {
			outputTable.getNode(i, str);
			if (str[0] == 'M') {
				// it's a machine
				for (int j = 0; j < macSize; j++) {
					if (str == machines[j].getName()) {
						std::cout << routerName << " -> " << m->getName() << std::endl;
						check = true;
					}
				}
			}
			else if (str[0] == 'R') {
				for (int j = 0; j < routerSize; j++) {
					if (str == routers[j].getRouterName()) {
						std::cout << routerName << " -> ";
						routers[j].printPath(m);
						check = true;
					}
				}
			}

			break;
		}

	}

	if (!check) {
		std::cout << "\nPath broken! :(\n";
	}

}

void ListRouter::addRoutingTable(std::string& machineName, std::string& routerName)
{
	std::string dummy;
	// search for machineName in destination table
	for (int i = 0; i < destinationTable.getSize(); i++) {
		destinationTable.getNode(i, dummy);
		if (dummy == machineName) {
			// machineName already exists, edit the routing table to add new routerName
			// for the corresponding machine
			outputTable.getNode(i, dummy);
			std::cout << "\n" << machineName << " -> " << dummy << " to ";
			outputTable.insert(routerName, i);
			std::cout << machineName << " -> " << routerName << "\n";
			break;
		}

	}

	bool check = false;
	for (int i = 0; i < outQueueSize; i++) {
		if (routerName == pair->name) {
			// check if pair has the new destination router/machine or not
			check = true;
			break;
		}
	}

	if (!check) {
		// if pair doesn't already contain the new destination router/machine, add it
		Pair* temp = new Pair[outQueueSize + 1];
		for (int i = 0; i < outQueueSize; i++) {
			temp[i] = pair[i];
		}
		temp[outQueueSize].name = routerName;
		outQueueSize++;
		delete[] pair;
		pair = temp;
	}
}

void ListRouter::removeRoutingTable(std::string& machineName)
{
	std::string dummy;
	for (int i = 0; i < destinationTable.getSize(); i++) {
		destinationTable.getNode(i, dummy);
		if (dummy == machineName) {
			std::cout << "\n" << machineName << " -> ";
			destinationTable.deleteNodeByIndex(i, dummy);
			outputTable.deleteNodeByIndex(i, dummy); // if found removes destination
			std::cout << dummy << " removed\n";
			break;
		}

	}
}

bool ListRouter::inQueueDequeue()
{
	Msg msg;
	bool check = inQueue.deleteNode(msg);
	bool check1 = false;

	if (check) {
		// we dequeued from input queue
		for (int i = 0; i < destinationTable.getSize(); i++) {
			std::string str;
			destinationTable.getNode(i, str);
			if (msg.destinationAddress == str) {
				outputTable.getNode(i, str);
				for (int j = 0; j < outQueueSize; j++) {
					if (str == pair[j].name) {
						// wait 0.5 second before forwarding the packet because of latency
						Sleep(500);
						pair[j].outQueue.enqueue(msg);
						check1 = true;
						break;
					}
				}
				break;
			}

		}
		if (!check1)
			std::cout << "\nPath broken! :(\n";
		return check;
	}
	else {
		return false;
	}

}

void ListRouter::outQueueDequeue(Msg& msg)
{
	bool check = false;
	for (int i = 0; i < destinationTable.getSize(); i++) {
		std::string str;
		destinationTable.getNode(i, str);
		if (msg.destinationAddress == str) {
			outputTable.getNode(i, str);
			if (str[0] == 'M') {
				for (int j = 0; j < macSize; j++) {
					if (str == machines[j].getName()) {
						machines[j].receiveMessage(msg);
						check = true;
						break;
					}
				}
			}
			else if (str[0] == 'R') {
				for (int j = 0; j < routerSize; j++) {
					if (str == routers[j].getRouterName()) {
						routers[j].inQueueEnqueue(msg);
						check = true;
						break;
					}
				}
			}
			break;
		}

	}

	if (!check) {
		std::cout << "\nPath broken! :(\n";
	}

}


void ListRouter::makeRoutingTable(std::string& fileName)
{
	Graph graph;
	Set set;
	for (int i = 0; i < macSize; i++) {
		List<int>* temp;
		destinationTable.insert(machines[i].getName(), i);
		temp = graph.setSource(routerID, fileName);
		for (int j = 0; j < graph.getSize(); j++) {
			int hello;
			temp[j].getNode(temp[j].getSize() - 1, hello);
			if (hello == machines[i].getID()) {
				int k = 0, m;
				temp[j].getNode(1, m);
				for (; k < macSize; k++) {
					if (m == machines[k].getID()) {
						outputTable.insert(machines[k].getName(), i);
						set.push(machines[k].getName());
						break;
					}
				}
				if (k != macSize)
					break;
				for (k = 0; k < routerSize; k++) {
					if (m == routers[k].getRouterID()) {
						outputTable.insert(routers[k].getRouterName(), i);
						set.push(routers[k].getRouterName());
						break;
					}
				}

			}

		}

	}
	pair = new Pair[set.getSize()];
	outQueueSize = set.getSize();
	for (int i = 0; i < outQueueSize; i++) {
		pair[i].name = set.getData(i);
	}
}

// build the routing table based on the adjacency matrix
void ListRouter::makeRoutingTable(int** matrix)
{
	Graph graph;
	Set set;
	std::string a;
	int destSize = destinationTable.getSize();
	for (int i = 0; i < destSize; i++) {
		// delete old routing table
		destinationTable.deleteNode(machines[i].getName());
		outputTable.deleteNode(machines[i].getName());
	}

	for (int i = 0; i < macSize; i++) {
		List<int>* temp;
		destinationTable.insert(machines[i].getName(), i);
		temp = graph.setSource(routerID, matrix, macSize + routerSize);
		for (int j = 0; j < graph.getSize(); j++) {
			int hello;
			temp[j].getNode(temp[j].getSize() - 1, hello);
			if (hello == machines[i].getID()) {
				int k = 0, m;
				temp[j].getNode(1, m);
				for (; k < macSize; k++) {
					if (m == machines[k].getID()) {
						outputTable.insert(machines[k].getName(), i);
						set.push(machines[k].getName());
						break;
					}
				}
				if (k != macSize)
					break;
				for (k = 0; k < routerSize; k++) {
					if (m == routers[k].getRouterID()) {
						outputTable.insert(routers[k].getRouterName(), i);
						set.push(routers[k].getRouterName());
						break;
					}
				}
			}
		}

	}
	delete[] pair;
	pair = new Pair[set.getSize()];
	outQueueSize = set.getSize();
	for (int i = 0; i < outQueueSize; i++) {
		pair[i].name = set.getData(i);
	}
}


void ListRouter::getMachineAndRouter(Machine*& machines, ListRouter*& routers, int machinesSize, int routersSize)
{
	this->machines = machines;
	this->routers = routers;
	this->macSize = machinesSize;
	this->routerSize = routersSize;
}

ListRouter::~ListRouter()
{

}
