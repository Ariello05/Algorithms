#include <iostream>
#include <random>
#include "Helper.hpp"
using std::cout;
using std::endl;
using std::rand;
namespace Help{

	void generate(int tab[], int size, int min, int max) {
		for (int i = 0; i < size; ++i) {
			tab[i] = rand() % (max - min) + min;
		}
	}

	/**
		returns true if str contains str2
	*/
	bool contains(char* str, std::string str2) {
		std::string conv = str;
		return conv.find(str2) != std::string::npos;
	}

	bool contains(std::string str, std::string str2) {
		return str.find(str2) != std::string::npos;
	}
}