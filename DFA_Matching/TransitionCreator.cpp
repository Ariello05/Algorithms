#include "TransitionCreator.h"

void TransitionCreator::computeTransition(DFA & d, const string & pattern, const string & alphabet)
{
	d.allClear();
	d.addToAlphabet(alphabet); d.setLastMapped(pattern);
	auto unique = d.getAlphabet();

	int last = 0;

	const int m = pattern.size();
	for (int q = 0; q <= m; ++q) {
		for (size_t i = 0; i < unique.size(); ++i) {
			int k = m + 1 > q + 2 ? q + 2 : m + 1;
			do {
				k--;
			} while (!isSuffix(pattern.substr(0, q) + unique[i], pattern.substr(0, k)));

			if (k > last) {
				last = k;
			}
			d.addRoute(q, unique[i],k);
		}
	}
	d.addToAccepting(last);
}

inline bool TransitionCreator::isSuffix(const string& text, const string& suf)
{
	return text.size() >= suf.size() && 0 == text.compare(text.size() - suf.size(), suf.size(), suf);

}
