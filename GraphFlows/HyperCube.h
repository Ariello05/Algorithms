#pragma once
#include "Graph.h"

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
	
	List** vect;

};

