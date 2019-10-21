#pragma once
#include "stdafx.h"
#include "UniqueVector.h"
#include "DFA.h"


class TransitionCreator {
public:
	void computeTransition(DFA& d, const string& pattern, const string& alphabet);

private:
	inline bool isSuffix(const string& text, const string& suf);

};
