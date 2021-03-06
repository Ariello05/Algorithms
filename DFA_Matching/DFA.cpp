#include "DFA.h"

void DFA::addRoute(int in, char c, int out) {
	routes.insert(std::make_pair(std::make_pair(in, c), out));
}

void DFA::addToAlphabet(char c) {
	alphabet.soft_push_back(c);
}

void DFA::printRoutes()const {
	for (auto item : routes) {
		std::cout << item.first.first << "\t" << item.first.second << "\t" << item.second << "\n";
	}
}

void DFA::addToAlphabet(const string& str) {
	for (char c : str) {
		alphabet.soft_push_back(c);
	}
}

void DFA::setRoutes(std::map<std::pair<int, char>, int> newroutes) {
	routes = newroutes;
}

void DFA::setLastMapped(string str)
{
	mapped = str;
}

void DFA::addToAccepting(int node) {
	accepting.push_back(node);
}

void DFA::clearRoutes() {
	routes.clear();
}

void DFA::clearAlphabet() {
	alphabet.clear();
}

void DFA::allClear() {
	clearAccepting();
	clearAlphabet();
	clearRoutes();
	mapped = "";
}

void DFA::clearAccepting() {
	accepting.clear();
}

string DFA::getLastMapped()
{
	return mapped;
}

const UniqueVector<char>& DFA::getAlphabet() const
{
	return alphabet;
}

const std::vector<int>& DFA::getAccepting()const {
	return accepting;
}

int DFA::step(int q, char c) {
	if (!alphabet.search(c)) {// can do the same for nodes
		std::string str; str += c;
		//throw std::invalid_argument(" is not present in alphabet!");
		throw std::invalid_argument("Argument:" + str + " is not present in alphabet!");
	}
	auto search = routes.find(std::make_pair(q, c));
	if (search != routes.end()) {
		return search->second;
	}
	else {
		q = 0;
		auto search = routes.find(std::make_pair(q, c));
		if (search == routes.end()) {
			throw std::logic_error("Routing graph met logical error");
		}
		else {
			return search->second;
		}
	}
}
