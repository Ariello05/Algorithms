#pragma once
#include "Graph.h"

class GLPKCreator
{
public:
	GLPKCreator();
	~GLPKCreator();

	static void make(Graph * g, std::string fileName);
};

