#pragma once
#include "stdafx.h"
#include "Printer.h"

//Knuth Morris Pratt
class KMP
{
public:
	void runMatcher(const string& text, const string& pattern);
	KMP();

private:
	void compute_prefix_function(const string& pattern);

	std::vector<int> pi;
};

