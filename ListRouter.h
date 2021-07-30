#pragma once
#include "Router.h"
#include "Misc.h"
#include "Queue.h"
#include "List.h"
#include "Router.h"
#include "Machine.h"
#include "Graph.h"
#include <iostream>
#include <Windows.h>
#include <string>

class ListRouter : public Router
{
private:
	struct Pair {
		Queue<Msg> outQueue;
		std::string name;
	};

	Pair* pair;
	int macSize;
	int routerSize;
	Machine* machines;
	ListRouter* routers; // routers are linked with each other

	List<std::string> destinationTable;
	List<std::string> outputTable;

public:
	ListRouter();
	void setRouterName(std::string&) override;
	void setRouterID(int&) override;
	int getRouterID() override;
	void makeRoutingTable(std::string&) override;
	void outQueueDequeue(Msg&) override;
	std::string& getRouterName() override;
	void printPath(Machine*&) override;
	void inQueueEnqueue(Msg&) override; //message is inserted into queue according to its priority
	bool inQueueDequeue() override; // message with highest priority is removed from queue
	void sendMessage();
	void makeRoutingTable(int**);
	void addRoutingTable(std::string&, std::string&);
	void removeRoutingTable(std::string&);
	void getMachineAndRouter(Machine*&, ListRouter*&, int, int);


	~ListRouter();
};

