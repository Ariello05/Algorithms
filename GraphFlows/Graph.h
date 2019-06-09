#pragma once
#include "Route.h"

class List {
public:
	List(Route r) :val(r.v, r.capacity) {
		next = nullptr;
	}
	~List() {
		if (next != nullptr) {
			delete next;
		}
	}
	List* next;
	Route val;
};

class Graph
{
public:
	Graph();
	~Graph();

	virtual void print() = 0;
	virtual int getAmount() = 0;
	virtual List** getNeighbourList() = 0;
	virtual int getK() = 0;
	virtual void reset() = 0;
	virtual void shuffle() = 0;
};

