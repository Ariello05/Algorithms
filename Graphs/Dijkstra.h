#pragma once
#include "../PriorityQueueAndDijkstra/PriorityQueue.h"
#include "Edge.h"
#include "Graph.h"

class Dijkstra
{
public:
	Dijkstra(Graph g);
	~Dijkstra();

	void Generate(const unsigned int startingPoint);

private:

	void Prepare(const unsigned int startingPoint);
	void CheckDistance(int v, int curr, int weight, std::pair<int, unsigned int> *& p);

	int * distance;
	PriorityQueue pq;
	Graph g;
};

