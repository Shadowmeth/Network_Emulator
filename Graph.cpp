#include "Graph.h"

Graph::Graph()
{
	adjMatrix = nullptr;
	predecessor = nullptr;
	distance = nullptr;
	mark = nullptr;
	path = nullptr;
	source = numOfVertices = 0;
}

int Graph::getSize()
{
	return numOfVertices;
}

void Graph::read(std::string& fileName)
{
	std::ifstream read;
	read.open(fileName);
	std::string line;
	if (!read.eof()) {
		std::getline(read, line, '\n');
	}

	numOfVertices = std::count(line.begin(), line.end(), ',');

	adjMatrix = new int* [numOfVertices];
	for (int i = 0; i < numOfVertices; i++) {
		adjMatrix[i] = new int[numOfVertices];
	}

	predecessor = new int[numOfVertices];
	distance = new int[numOfVertices];
	mark = new bool[numOfVertices];

	int i = 0;
	while (!read.eof()) {
		std::getline(read, line, ',');
		for (int j = 0; j < numOfVertices; j++) {
			if (j != numOfVertices - 1)
				std::getline(read, line, ',');
			else
				std::getline(read, line, '\n');
			if (line == "?")
				adjMatrix[i][j] = 0;
			else
				adjMatrix[i][j] = stoi(line);
		}
		i++;
		if (i == numOfVertices)
			break;
	}
	read.close();
}

void Graph::initalize()
{
	for (int i = 0; i < numOfVertices; i++) {
		mark[i] = false;
		predecessor[i] = -1;
		distance[i] = INT_MAX; // assume distance to be infinite initially
	}
	distance[source] = 0;
}

List<int>*& Graph::setSource(int& x, std::string& fileName)
{
	source = x;
	index = 0;
	read(fileName);
	path = new List<int>[numOfVertices];
	trans = 0;
	dijkstra();
	output();
	return path;
}

List<int>*& Graph::setSource(int& x, int** matrix, int size)
{
	source = x;
	index = 0;
	numOfVertices = size;
	adjMatrix = new int* [numOfVertices];
	for (int i = 0; i < numOfVertices; i++) {
		adjMatrix[i] = new int[numOfVertices];
	}

	for (int i = 0; i < numOfVertices; i++) {
		for (int j = 0; j < numOfVertices; j++) {
			adjMatrix[i][j] = matrix[i][j];
		}
	}

	predecessor = new int[numOfVertices];
	distance = new int[numOfVertices];
	mark = new bool[numOfVertices];
	path = new List<int>[numOfVertices];
	trans = 0;
	dijkstra();
	output();
	return path;
}

int Graph::getClosestUnmarkedNode()
{
	int minDistance = 999;
	int closestUnmarkedNode = -1;
	for (int i = 0; i < numOfVertices; i++) {
		if ((!mark[i]) && (minDistance >= distance[i])) {
			minDistance = distance[i];
			closestUnmarkedNode = i;
		}
	}

	return closestUnmarkedNode;
}

void Graph::dijkstra()
{
	initalize();
	int minDistance = 999;
	int closestUnmarkedNode;
	int count = 0;
	while (count < numOfVertices) {
		// visit all vertices
		closestUnmarkedNode = getClosestUnmarkedNode();
		mark[closestUnmarkedNode] = true;

		for (int i = 0; i < numOfVertices; i++) {
			if ((!mark[i]) && (adjMatrix[closestUnmarkedNode][i] > 0)) {
				if (distance[i] > distance[closestUnmarkedNode] + adjMatrix[closestUnmarkedNode][i]) {
					distance[i] = distance[closestUnmarkedNode] + adjMatrix[closestUnmarkedNode][i];
					predecessor[i] = closestUnmarkedNode;
				}
			}
		}

		count++;
	}
}


void Graph::printPath(int node)
{
	if (node == source) {
		path[trans].insert(node, index);
		index++;
	}
	else if (predecessor[node] == -1) {
		std::cout << "No path from " << source << " to " << node << "\n";
	}
	else {
		printPath(predecessor[node]);
		path[trans].insert(node, index);
		index++;

	}
}

void Graph::output()
{
	for (int i = 0; i < numOfVertices; i++) {
		if (i == source)
		{
			path[trans].insert(source, index);
			index++;
			path[trans].insert(source, index);
			index++;
		}
		else
			printPath(i);
		trans++;
		index = 0;
	}
}

Graph::~Graph()
{

}
