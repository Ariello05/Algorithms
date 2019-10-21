#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <exception>
#include <windows.h>
#include <cstdio>
#include <algorithm>

using std::string;
using std::wstring;
using std::u32string;
using std::cout;
using std::wcout;

template<class T>
class UniqueVector {
public:
	void push_back(T val) {
		if (search(val)) {
			throw std::invalid_argument("This value already exists!");
		}
		vect.push_back(val);
	}

	bool soft_push_back(T val) {
		if (search(val)) {
			return true;
		}
		vect.push_back(val);
		return false;
	}

	size_t size()const {
		return vect.size();
	}

	T operator[](const int& index)const {
		return vect[index];
	}

	void clear() {
		vect.clear();
	}

	bool search(T val)const {
		auto beg = vect.begin();
		const auto end = vect.end();
		while (beg != end) {
			if (*beg == val) {
				return true;
			}
			beg++;
		}
		return false;
	}

private:
	std::vector<T> vect;
};

class TransitionCreator {
public:
	std::map<std::pair<int, char>, int> cumputeTransitions(const string& pattern, const UniqueVector<char>& alphabet) {
		last = 0;
		std::map<std::pair<int, char>, int> routes;

		const int m = pattern.size();
		for (int q = 0; q <= m; ++q) {
			for (size_t i = 0; i < alphabet.size(); ++i) {
				int k = m + 1 > q + 2 ? q + 2 : m + 1;
				do {
					k--;
				} while (!isSuffix(pattern.substr(0, q) + alphabet[i], pattern.substr(0, k)));

				if (k > last) {
					last = k;
				}
				routes.insert(std::make_pair(std::make_pair(q, alphabet[i]), k));
			}
		}
		return routes;
	}

	inline bool isSuffix(const string & text, const string & suf) {
		return text.size() >= suf.size() && 0 == text.compare(text.size() - suf.size(), suf.size(), suf);
	}

	int last;
};

class DFA {
public:
	void addRoute(int in, char c, int out) {
		routes.insert(std::make_pair(std::make_pair(in, c), out));
	}

	void addToAlphabet(char c) {
		alphabet.soft_push_back(c);
	}

	void printRoutes() {
		for (auto item : routes) {
			std::cout << item.first.first << "\t" << item.first.second << "\t" << item.second << "\n";
		}
	}

	void addToAlphabet(const string& str) {
		for (wchar_t c : str) {
			alphabet.soft_push_back(c);
		}
	}

	void cumputeTransitions(const string& pattern, const string & alphabet) {
		allClear();
		addToAlphabet(alphabet);
		TransitionCreator tc;
		setRoutes(tc.cumputeTransitions(pattern, this->alphabet));
		addToAccepting(tc.last);
		last = tc.last;
	}

	void setRoutes(std::map<std::pair<int, char>, int> newroutes) {
		routes = newroutes;
	}

	void addToAccepting(int node) {
		accepting.push_back(node);
	}

	void clearRoutes() {
		routes.clear();
	}

	void clearAlphabet() {
		alphabet.clear();
	}

	void allClear() {
		clearAccepting();
		clearAlphabet();
		clearRoutes();
	}

	void clearAccepting() {
		accepting.clear();
	}

	const std::vector<int> & getAccepting() {
		return accepting;
	}

	int step(int q, char c) {
		if (!alphabet.search(c)) {// can do the same for nodes
			std::string str; str += c;
			//throw std::invalid_argument(" is not present in alphabet!");
			throw std::invalid_argument("Argument:" + str + " is not present in alphabet!");
		}
		auto search = routes.find(std::make_pair(q, c));
		//cout << search->second << std::endl;
		return search == routes.end() ? 0 : search->second;
	}

private:
	std::map<std::pair<int, char>, int> routes;
	UniqueVector<char> alphabet;
	//UniqueVector dla stanów
	std::vector<int> accepting;
	int last;
};

class Printer {
public:
	void read(std::vector<int> acc, string matched) {

		cout << "Matched(\""<< matched << "\") at: ";
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

class Automaton_Matcher {
public:
	void setDFA(DFA d) {
		dfa = d;
	}

	void setPattern(string pt) {
		pattern = pt;
	}

	void runMatcher() {
		std::vector<int> offsets;
		int n = pattern.size();
		int q = 0;
		for (int i = 0; i < n; ++i) {
			q = dfa.step(q, pattern[i]);
			//cout << q << '\t' << '\n';

			for (int item : dfa.getAccepting()) {
				if (q == item) {
					int s = i - item + 1;
					offsets.push_back(i - item + 1);
					break;
				}
			}
		}
		r.read(offsets, pattern);
	}

	void runMatcher(string pr, DFA d, int m) {
		setPattern(pr); setDFA(d); dfa.addToAccepting(m);
		runMatcher();
	}

private:
	DFA dfa;//pointer
	Printer r;
	string pattern;
};
/*
class InputAutomator {
public:
	InputAutomator():end('q'){}

	void runLoop() {
		char c;
		std::cin >> c;
		while (c != end) {
			std::cin >> c;
		}
	}

private:
	const char end;
};
*/

int wmain()
{
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

	try {
		DFA d;
		UniqueVector<char> alphabet;
		d.cumputeTransitions("d", "abcd");
		d.printRoutes();

		//d.clearRoutes(); d.clearAccepting();
		//d.addRoute(0, 'a', 1);
		//d.addToAccepting(1);
		//d.addToAlphabet("a");

		Automaton_Matcher am;
		am.setDFA(d);
		am.setPattern("ababcbababababc");
		am.runMatcher();
	}
	catch (std::exception e) {
		cout << e.what();
	}
}

