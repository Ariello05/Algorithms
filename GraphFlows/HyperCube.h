#pragma once
#include "Graph.h"
#include <time.h>
#include <ctime>
#include <boost/random.hpp>

class HyperCube : public Graph
{
public:
	HyperCube(unsigned int k);
	~HyperCube();
	void print();
	virtual int getAmount() override;
	virtual List** getNeighbourList() override;
	virtual int getK() override;
	virtual void reset() override;
	virtual void shuffle() override;

private:
	unsigned int k;
	void addEdge(int u, int v);
	int lastVertice;
	std::time_t now;
	boost::random::mt19937 gen;
	
	List** vect;
};

