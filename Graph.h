#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "List.h"

class Graph
{
private:
	int** adjMatrix; // adjacency matrix
	int* predecessor, * distance; // predecessor and distance arrays
	bool* mark; // boolean mark array
	int source; // source starting position used in dijkstra algorithm
	int numOfVertices; // total number of vertices in graph
	int index; // index variable used in functions
	List<int>* path; // path made from dijkstra algorithm saved here
	int trans;

public:
	Graph();
	int getSize(); // get size
	void read(std::string&); // read graph from file
	void initalize(); // initialize graph for dijkstra
	List<int>*& setSource(int&, std::string&);	// run dijkstra algorithm and return list of path
	List<int>*& setSource(int&, int**, int);	//  run dijkstra algorithm and return list of path
	int getClosestUnmarkedNode(); // gear nearest unvisited node in dijkstra algorithm
	void dijkstra(); // actual dijkstra algorithm
	void output();
	void printPath(int);
	~Graph();

};

