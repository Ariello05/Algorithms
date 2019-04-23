#include <iostream>
#include "Edge.h"
#include "Graph.h"
#include "Dijkstra.h"
#include "Prim.h"
#include "Kruskal.h"

using std::cout;
using std::endl;
using std::cin;

void autoDefine() {
	int n = 7;
	int m = 10;
	Edge * edges = new Edge[m];
	edges[0] = Edge(1, 2, 1);
	edges[1] = Edge(1, 3, 2);
	edges[2] = Edge(2, 4, 3);
	edges[3] = Edge(2, 5, 1);
	edges[4] = Edge(3, 4, 2);
	edges[5] = Edge(3, 5, 1);
	edges[6] = Edge(5, 6, 2);
	edges[7] = Edge(4, 6, 2);
	edges[8] = Edge(1, 7, 8);
	edges[9] = Edge(6, 7, 3);
	Graph g(edges, n, m);
	Dijkstra d(g);
	d.Generate(4);
	Prim prim(g);
	prim.Run();
	Kruskal k(g);
	k.Run();
}

void Define(Edge *& edg, int & E, int & V) {
	cout << "Type number of Vertices: " << endl;
	cin >> V;
	cout << "Type number of Edges: " << endl;
	cin >> E;
	cout << "Type m edges: [ ]" << endl;
	Edge * edges = new Edge[E];
	unsigned int buff;
	for (int i = 0; i < E; ++i) {
		cout << "Type u:" << endl;
		cin >> buff;
		edges[i].v1 = buff;
		cout << "Type v:" << endl;
		cin >> buff;
		edges[i].v2 = buff;
		cout << "Type w:" << endl;
		cin >> buff;
		edges[i].weight = buff;
		cout << "------NEW EDGE-------" << endl;
	}
	edg = edges;
}

int main(int argc, char * argv[]) {
	Edge * e;
	int V, E;
	if (argc < 2) {
		Define(e,E,V);
		int buff;
		cout << "Type starting vertice!" << endl;
		cin >> buff;
		Graph g(e, V, E);
		Dijkstra d(g);
		d.Generate(buff);
	}
	else if (argv[1][1] == 'p') {
		Define(e,E,V);
		Graph g(e, V, E);
		Prim p(g);
		p.Run();
	}
	else if (argv[1][1] == 'k') {
		Define(e, E, V);
		Graph g(e, V, E);
		Kruskal k(g);
		k.Run();
	}
	else if (argv[1][1] == '-a'){
		autoDefine();
	}else{
		cout << "Unkown arguments namely: " << argv[1] << ", use -k or -p" << endl;
	}

	int a;
	std::cin >> a;
}