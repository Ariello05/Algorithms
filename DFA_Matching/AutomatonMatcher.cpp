#include "AutomatonMatcher.h"
#include "TransitionCreator.h"

AutomatonMatcher::AutomatonMatcher()
{
	dfa = std::make_shared<DFA>();
}

AutomatonMatcher::AutomatonMatcher(shared_ptr<DFA> df)
{
	this->dfa = df;
}
void AutomatonMatcher::setDFA(shared_ptr<DFA> d)
{
	dfa = d;
}

void AutomatonMatcher::setPattern(string pt)
{
	pattern = pt;
}

void AutomatonMatcher::runMatcher()
{
	Printer r;
	std::vector<int> offsets;
	int n = pattern.size();
	int q = 0;
	for (int i = 0; i < n; ++i) {
		q = dfa->step(q, pattern[i]);
		//cout << q << '\t' << '\n';

		for (int item : dfa->getAccepting()) {
			if (q == item) {
				int s = i - item + 1;
				offsets.push_back(i - item + 1);
				break;
			}
		}
	}
	r.read(offsets, pattern, dfa->getLastMapped());
}

void AutomatonMatcher::runMatcher(string pr, shared_ptr<DFA> d, int m)
{
	setPattern(pr); setDFA(d); dfa->addToAccepting(m);
	runMatcher();
}

void AutomatonMatcher::runMatcher(string pr)
{
	setPattern(pr);
	runMatcher();
}

void AutomatonMatcher::runMatcher(string text, string pattern, string alphabet)
{
	TransitionCreator tc;

	tc.computeTransition(*dfa, pattern, alphabet);
	this->runMatcher(text);

}
