#pragma once
#include "Graph.h"
class Bipartite :
	public Graph
{
public:
	Bipartite(unsigned int k, unsigned int i);
	~Bipartite();

	// Odziedziczono za poœrednictwem elementu Graph
	virtual int getAmount() override;
	virtual List** getNeighbourList() override;
	virtual int getK() override;
	virtual void reset() override;
	virtual void shuffle() override;
private:
	List** vect;
	int sizeV;
	int k;
	int i;

	// Odziedziczono za poœrednictwem elementu Graph
	virtual void print() override;
};

