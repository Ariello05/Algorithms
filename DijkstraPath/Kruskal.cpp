#include "Kruskal.h"



Kruskal::Kruskal(Graph graph)
	:g(graph)
{

}


void Kruskal::Run()
{
	int sumW = 0;
	g.SortEdges();
	Edge * edges = g.getEdges();
	int V = g.getVerticeSize();
	int E = g.getEdgesSize();

	Sets ds(V);
	for (int i = 0; i < E;  ++i) // E LOG V
	{
		int u = edges[i].v1;
		int v = edges[i].v2;

		int set_u = ds.Find(u);
		int set_v = ds.Find(v);

		// Cycle check
		if (set_u != set_v)
		{
			// Current edge will be in the MST	
			std::cout << "(u, v, w): ";
			std::cout << u << " " << v << " " << edges[i].weight << std::endl;
			sumW += edges[i].weight;
			ds.Merge(set_u, set_v);
		}
	}
	std::cout << "Weight: " << sumW << std::endl;

}

Kruskal::Sets::Sets(int n)
{
	this->n = n;
	parent = new int[n + 1];// 1..n
	rank = new int[n + 1];

	for (int i = 0; i <= n; i++)
	{
		rank[i] = 0;
		parent[i] = i; //parent of itself in the beginning
	}
}

int Kruskal::Sets::Find(int u)
{
	// Path compression
	if (u != parent[u])
		parent[u] = Find(parent[u]);
	return parent[u];
}

void Kruskal::Sets::Merge(int x, int y)
{
	x = Find(x), y = Find(y);

	if (rank[x] > rank[y]) // small tree vs bigger tree
		parent[y] = x;
	else 
		parent[x] = y;

	if (rank[x] == rank[y])
		rank[y]++;

}
