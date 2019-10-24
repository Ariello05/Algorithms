#pragma once
#include "stdafx.h"

class Printer
{
public:
	void read(const std::vector<int> & acc, const string & matched, const string & map) {
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

