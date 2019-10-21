#pragma once
#include "stdafx.h"
#include "DFA.h"
#include "Printer.h"

class AutomatonMatcher
{
public:
	AutomatonMatcher();
	AutomatonMatcher(shared_ptr<DFA> df);
	void setDFA(shared_ptr<DFA> d);
	void setPattern(string pt);
	void runMatcher();
	void runMatcher(string pr, shared_ptr<DFA> d, int m);
	void runMatcher(string pr);
	void runMatcher(string text, string pattern, string alphabet);
private:

	shared_ptr<DFA> dfa;//pointer
	string pattern;
};

