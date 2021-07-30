#pragma once
#include "ListRouter.h"
#include <fstream>
#include <iostream>

class Machine
{
private:
	std::string machineName;
	int machineID;
	Queue<Msg> inQueue; // FIFO incoming queue
	Queue<Msg> outQueue; // FIFO outgoing queue
	int machineSize;
	int routerSize;
	Machine* machines;
	ListRouter* routers;
	
	static int id;

public:
	Machine();
	void setMachineName(std::string&);
	void setMachineID(int&);
	void makeTableList(std::string&); // set adjacent routers
	void getMachineAndRouter(Machine*&, ListRouter*&, int, int);
	void sendMessageList(std::string&); // set adjacent routers
	void makeTableList(int**, int);
	void sendBulkMessageList(Msg&);
	void printPathList(Machine*&);
	int getID();
	void receiveMessage(Msg&);
	std::string& getName();
	~Machine();

};

