#pragma once
#include "stdafx.h"
#include "UniqueVector.h"

class DFA {
public:
	void addRoute(int in, char c, int out);
	void addToAlphabet(char c);
	void addToAlphabet(const string& str);
	void addToAccepting(int node);

	void setRoutes(std::map<std::pair<int, char>, int> newroutes);
	void setLastMapped(string str);

	void allClear();
	void clearRoutes();
	void clearAlphabet();
	void clearAccepting();

	string getLastMapped();
	const UniqueVector<char>& getAlphabet()const;
	const std::vector<int>& getAccepting()const;

	int step(int q, char c);
	void printRoutes()const;

private:
	std::map<std::pair<int, char>, int> routes;
	UniqueVector<char> alphabet;
	//UniqueVector dla stanów
	std::vector<int> accepting;
	string mapped;
	int last;
};