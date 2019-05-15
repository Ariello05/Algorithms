#pragma once
#include "Graph.h"
#include "../PriorityQueue/PriorityQueue.h"



class Kruskal
{
public:
	void Run();
	Kruskal(Graph g);

private:

	class Sets {
	public:
		Sets(int n);

		int Find(int u);
		void Merge(int x, int y);

	private:
		int *parent, *rank;
		int n;
	};

	Graph g;
};

