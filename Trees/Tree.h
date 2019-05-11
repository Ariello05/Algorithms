#pragma once
#include <string>
#include <fstream>

template <typename T>
class Tree {
public:
	virtual void insert(T) = 0;
	virtual void remove(T) = 0;
	virtual void search(T) = 0;
	void load(std::string f) {
		std::fstream file(f);
		T var;
		while (file) {
			file >> var;
			insert(var);
		}
	}
	virtual void inOrder() = 0;

};