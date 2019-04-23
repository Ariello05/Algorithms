#include "Graph.h"
#include <limits>
#include <utility>
#include <algorithm>

Graph::Graph(Edge * edges, const unsigned int vertices, const unsigned int edgesAmount)
{
	this->edges = edges;
	this->v_size = vertices;
	this->e_size = edgesAmount;
}


void Graph::SortEdges()
{
	Edge * beg = edges;
	Edge * end = edges;
	end += e_size;
	std::sort(beg, end);

	
}

void Graph::Print() {

	for (int i = 0; i < e_size; ++i) {
		edges[i].Print();
	}
}


Edge * Graph::getEdges()
{
	return edges;
}

unsigned int Graph::getVerticeSize()
{
	return v_size;
}

unsigned int Graph::getEdgesSize()
{
	return e_size;
}