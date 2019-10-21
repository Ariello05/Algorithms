#pragma once
#include "stdafx.h"
#include "DFA.h"

class AutomatonMatcher
{
public:
	AutomatonMatcher(shared_ptr<DFA> df);
	void setDFA(shared_ptr<DFA> d);
	void setPattern(string pt);
	void runMatcher();
	void runMatcher(string pr, shared_ptr<DFA> d, int m);
	void runMatcher(string pr);
private:
	class Printer {
	public:
		void read(std::vector<int> acc, string matched, string map) {
			cout << "Matched(\"" << map << "\")" << " in: (\"" << matched << "\") at: ";
			string buffor = "[";

			for (int item : acc) {
				buffor += std::to_string(item) + ", ";
			}
			if (buffor.back() == ' ') {
				buffor.pop_back(); buffor.pop_back();
				buffor += "]";
			}
			else {
				buffor.pop_back();
				buffor += "empty.";
			}
			cout << buffor << "\n";
		}
	};

	shared_ptr<DFA> dfa;//pointer
	Printer r;
	string pattern;
};

