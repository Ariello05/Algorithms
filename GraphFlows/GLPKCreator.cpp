#include "GLPKCreator.h"
#include <fstream>


GLPKCreator::GLPKCreator()
{
}

using std::endl;

GLPKCreator::~GLPKCreator()
{
}

void GLPKCreator::make(Graph* g, std::string fileName)
{
	std::ofstream myfile;
	myfile.open(fileName);

	myfile << "/* Number of nodes: */" << endl;
	myfile << "param n, integer, >= 2;" << endl << endl;

	myfile << "/* Set of nodes: */" << endl;
	myfile << "set V, default {1..n};" << endl << endl;

	myfile << "/* Set of arcs: */" << endl;
	myfile << "set E, within V cross V;" << endl << endl;

	myfile << "/* Capacity of arc(i,j): */" << endl;
	myfile << "param a{(i,j) in E}, > 0;" << endl << endl;

	myfile << "/* Beginning and End: */" << endl;
	myfile << "param s, symbolic, in V, default 1;" << endl;
	myfile << "param t, symbolic, in V, != s, default n;" << endl << endl;

	myfile << "/* Elementray flow through arc(i,j): */" << endl;
	myfile << "var x{(i,j) in E}, >= 0, <= a[i,j];" << endl << endl;

	myfile << "/* Total flow: */" << endl;
	myfile << "var flow, >= 0;" << endl << endl;

	myfile << "/* Constraints: */" << endl << endl;

	myfile << "s.t. node{i in V}:" << endl;
	myfile << "sum{(j,i) in E} x[j,i] + (if i = s then flow)" << endl;
	myfile << "=" << endl;
	myfile << "sum{(i,j) in E} x[i,j] + (if i = t then flow);" << endl << endl;

	myfile << "/* Objective : */" << endl << endl;

	myfile << "maximize obj: flow;" << endl << endl;
	myfile << "solve;" << endl;
	myfile << "printf \"Maximum flow:%g\",flow;" << endl << endl;

	myfile << "/* Array: */" << endl << endl;

	myfile << "data;" << endl;
	myfile << "param n :=" << g->getAmount() << ";" << endl;
	myfile << "param : E :   a :=";

	List** pars = g->getNeighbourList();
	int last = g->getAmount();

	for (int i = 0; i < last; ++i) {
		List* begin = pars[i];
		while (begin) {
			myfile << endl << i << " " << begin->val.v << "   " << begin->val.capacity;
			begin = begin->next;
		}
	}

	myfile << ";" << endl;
	myfile << "end;" << endl;
}
