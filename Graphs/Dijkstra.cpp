#include "Dijkstra.h"
#include <ctime>

#include "Graph.h"
#include <limits>
#include <utility>

Dijkstra::Dijkstra(Graph graph):
	pq(graph.getEdgesSize()),
	g(graph)
{
	distance = new int[g.getVerticeSize() + 1];//1..n
}

Dijkstra::~Dijkstra()
{
}

void Dijkstra::Generate(const unsigned int startingPoint)
{
	double begin = clock();
	Prepare(startingPoint);
	std::pair<int, unsigned int> * tab = new std::pair<int, unsigned int>[g.getVerticeSize() + 1];//index - current, first - previous, second - edge weigh
	for (int i = 0; i < g.getVerticeSize() + 1; ++i) {
		tab[i].first = -1;
	}
	tab[startingPoint].first = startingPoint;


	//ELOGV + VlOGV = (E + V)LOG V = [if all vertices can be reached from source] E LOG V

	while (!pq.isEmpty())// V
	{
		int curr = pq.pop();// log 

		int weight;
		int v;
		for (int i = 0; i < g.getEdgesSize(); ++i) {// E
			if (g.getEdges()[i].v1 == curr) {// v1 starting point
				weight = g.getEdges()[i].weight;

				v = g.getEdges()[i].v2;
				CheckDistance(v, curr, weight, tab); // log 
			}
			else if (g.getEdges()[i].v2 == curr) {// v2 starting point \ so two side directed graph = undirected
				weight = g.getEdges()[i].weight;

				v = g.getEdges()[i].v1;
				CheckDistance(v, curr, weight, tab); // log 
			}

		}
	}
	double end = clock();
	double time = double(end - begin) / CLOCKS_PER_SEC;

	for (int i = 1; i <= g.getVerticeSize(); ++i) {
		if (i != startingPoint) {
			int prev = tab[i].first;
			int cur = i;
			std::cerr << "Routing: " << cur << std::endl;
			while (cur != startingPoint) {
				std::cerr << "  " << cur << "\t to \t";
				std::cerr << tab[cur].first << "\t weight: ";
				std::cerr << tab[cur].second << '\n';
				cur = prev;
				prev = tab[cur].first;
			}
		}
	}


	std::cout << "Vertex \t    Sum Weight\n";
	for (int i = 1; i <= g.getVerticeSize(); ++i) {
		std::cout << "  " << i << "\t\t" << distance[i] << std::endl;
	}

	std::cout << "CPU time elapsed: " << time << std::endl;

}


void Dijkstra::Prepare(const unsigned int startingPoint)
{
	while (!pq.isEmpty()) {
		pq.pop();
	}
	
	for (int i = 1; i <= g.getVerticeSize(); i++) {
		distance[i] = INT_MAX;
	}
	distance[startingPoint] = 0;
	pq.insert(0, startingPoint);
}

void Dijkstra::CheckDistance(int v, int curr, int weight, std::pair<int, unsigned int>*& tab)
{
	if (distance[v] > distance[curr] + weight) {
		distance[v] = distance[curr] + weight;
		tab[v].first = curr;
		tab[v].second = weight;
		pq.insert(distance[v], v);
	}
}
