#include "Prim.h"
#include <iostream>

void Prim::Run(int startingPoint)
{
	Prepare(startingPoint);
	int E = g.getEdgesSize();

	int *parent = new int[E];
	int *parentWeight = new int[E];
	for (int i = 0; i < E; ++i) {
		parentWeight[i] = 0;
	}

	Edge * edges = g.getEdges();

	int weight;
	int v;

	// E LOG V
	while (!pq.isEmpty())
	{
		int u = pq.pop();
		restricted[u] = true;

		for (int i = 0; i < E; ++i) {// E
			if (edges[i].v1 == u) {// v1 starting point
				v = edges[i].v2;
				CheckDistance(v, u, edges[i].weight, parent, parentWeight);
			}
			else if (edges[i].v2 == u) {// v2 starting point \ so two side directed graph = undirected
				v = edges[i].v1;
				CheckDistance(v, u, edges[i].weight, parent, parentWeight);
			} 
		}
	}

	int sumW = 0;
	for (int i = 1; i <= g.getVerticeSize(); ++i) {
		if (i != startingPoint) {
			std::cout << "(u, v, w): " << parent[i] << " " << i << " " << parentWeight[i] << std::endl;
			sumW += parentWeight[i];
		}
	}
	std::cout << "Weight: " << sumW << std::endl;
}

Prim::Prim(Graph graph)
	:g(graph),
	pq(graph.getEdgesSize())
{
	distance = new int[g.getVerticeSize() + 1];//1..n
	restricted = new bool[g.getVerticeSize() + 1];//1..n
}

void Prim::Prepare(int startingPoint)
{
	for (int i = 1; i <= g.getVerticeSize(); i++) {
		distance[i] = INT_MAX;
		restricted[i] = false;
	}

	distance[startingPoint] = 0;//key
	pq.insert(0, startingPoint);
}

void Prim::CheckDistance(int v, int u, int weight, int *& parent, int *& parentW)
{
	if (!restricted[v] && distance[v] > weight) {
		distance[v] = weight;
		pq.insert(distance[v], v); // LOG V
		parent[v] = u;
		parentW[v] = weight;
	}
}
