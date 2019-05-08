#pragma once
#include "Graph.h"
#include "../PriorityQueueAndDijkstra/PriorityQueue.h"

class Prim {
public:
	void Run();
	Prim(Graph g);

private:

	void Prepare();
	void CheckDistance(int v, int u, int weight, int *& parent, int *& parentW);

	int * distance;
	bool * restricted;
	PriorityQueue pq;
	Graph g;

};
