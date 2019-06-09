#pragma once
#include <iostream>

class Route
{
public:
	Route();
	Route(unsigned int v, unsigned int l);

	bool operator<(const Route& s2);
	void Print();

	unsigned int v;
	unsigned int capacity;
	int flow;
};

