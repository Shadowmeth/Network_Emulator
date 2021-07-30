#pragma once
#include "Misc.h"
#include "MaxHeap.h"
class Machine;
class ListRouter;

class Router {
protected:
	MaxHeap<Msg> inQueue;
	int outQueueSize;
	std::string routerName;
	int routerID;

public:
	virtual void setRouterName(std::string&) = 0;
	virtual void setRouterID(int&) = 0;
	virtual int getRouterID() = 0;
	virtual void makeRoutingTable(std::string&) = 0;
	virtual void outQueueDequeue(Msg&) = 0;
	virtual std::string& getRouterName() = 0;
	virtual void printPath(Machine*&) = 0;
	virtual void inQueueEnqueue(Msg&) = 0; // message is inserted into queue according to its priority
	virtual bool inQueueDequeue() = 0; // message with highest priority is removed from queue

};
