#pragma once
#include "Edge.h"

class Graph {
public:

	Graph(Edge* edges, const unsigned int vertices, const unsigned int edgesAmount);

	void SortEdges();
	void Print();
	Edge * getEdges();
	unsigned int getVerticeSize();
	unsigned int getEdgesSize();


private:
	
	Edge * edges;
	unsigned int v_size;
	unsigned int e_size;

};
