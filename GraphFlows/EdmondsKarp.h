#pragma once
#include "HyperCube.h"

class EdmondsKarp
{
public:
	EdmondsKarp(Graph * hc);
	~EdmondsKarp();

	int run();
	int getLastRoutes();
private:
	Graph* hc;
	bool wasRun;
	int sr;
};

