#pragma once
#include "Graph.h"
#include "../PriorityQueue/PriorityQueue.h"

class Prim {
public:
	void Run(int st);
	Prim(Graph g);

private:

	void Prepare(int st);
	void CheckDistance(int v, int u, int weight, int *& parent, int *& parentW);

	int * distance;
	bool * restricted;
	PriorityQueue pq;
	Graph g;

};
