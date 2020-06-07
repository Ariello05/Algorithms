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
	int buff;
	cout << "Type starting vertice!" << endl;
	cin >> buff;
	d.Generate(buff);
	Prim prim(g);
	prim.Run(1);
	Kruskal k(g);
	k.Run();
}

void defineOne(){
	int n = 9;
	int m = 14;
	Edge * edges = new Edge[m];
	edges[0] = Edge(1, 2, 4);
	edges[1] = Edge(2, 3, 8);
	edges[2] = Edge(3, 4, 7);
	edges[3] = Edge(4, 5, 9);
	edges[4] = Edge(5, 6, 10);
	edges[5] = Edge(6, 7, 2);
	edges[6] = Edge(7, 8, 1);
	edges[7] = Edge(8, 1, 8);
	edges[8] = Edge(2, 8, 11);
	edges[9] = Edge(3, 9, 2);
	edges[10] = Edge(3, 6, 4);
	edges[11] = Edge(4,6,14);
	edges[12] = Edge(7,9,6);
	edges[13] = Edge(8,9,7);
	Graph g(edges, n, m);
	Prim prim(g);
	int buff;
	cout << "Type starting vertice!" << endl;
	cin >> buff;
	prim.Run(buff);
	Kruskal k(g);
	k.Run();
}

void defineTwo() {
	int n = 6;
	int m = 9;
	Edge * edges = new Edge[m];
	edges[0] = Edge(1, 2, 9);
	edges[1] = Edge(3, 2, 6);
	edges[2] = Edge(4, 3, 15);
	edges[3] = Edge(4, 6, 10);
	edges[4] = Edge(5, 4, 7);
	edges[5] = Edge(6, 5, 9);
	edges[6] = Edge(1, 6, 2);
	edges[7] = Edge(5, 1, 14);
	edges[8] = Edge(6, 3, 11);

	Graph g(edges, n, m);
	Dijkstra d(g);
	int buff;
	cout << "Type starting vertice!" << endl;
	cin >> buff;
	d.Generate(buff);
}

void Define(Edge *& edg, int & E, int & V) {
	cout << "Type number of Vertices: " << endl;
	cin >> V;
	cout << "Type number of Edges: " << endl;
	cin >> E;
	cout << "Type m edges:" << endl;
	Edge * edges = new Edge[E];
	unsigned int buff;
	cout << "Type u v w \n";
	for (int i = 0; i < E; ++i) {
		cout << "> ";
		cin >> buff;
		edges[i].v1 = buff;
		cin >> buff;
		edges[i].v2 = buff;
		cin >> buff;
		edges[i].weight = buff;
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
		p.Run(1);
	}
	else if (argv[1][1] == 'k') {
		Define(e, E, V);
		Graph g(e, V, E);
		Kruskal k(g);
		k.Run();
	}
	else if (argv[1][1] == 'a'){
		autoDefine();
	}
	else if (argv[1][1] == '1') {
		defineOne();
	}
	else if (argv[1][1] == '2') {
		defineTwo();
	}
	else{
		cout << "Unkown arguments namely: " << argv[1] << ", use -k or -p" << endl;
	}

	int a;
	std::cin >> a;
}