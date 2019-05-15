#pragma once
#include <iostream>

class Edge
{
public:
	Edge() {}
	Edge(unsigned int u, unsigned int v, unsigned int w) {
		this->v1 = u;
		this->v2 = v;
		this->weight = w;
	}

	bool operator<(const Edge& s2)
	{
		return this->weight < s2.weight;
	}

	void Print() {
		std::cerr << "v1: " << v1 << "\t v2: " << v2 << "\t weight: " << weight << std::endl;
	}

	unsigned int v1;
	unsigned int v2;
	unsigned int weight;
};

