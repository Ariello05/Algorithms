#include <iostream>
#include <random>
#include "helper.hpp"
using std::cout;
using std::endl;
using std::rand;
namespace Help{
	void swap(int tab[], int i1, int i2) {
		int buf = tab[i1];
		tab[i1] = tab[i2];
		tab[i2] = buf;
	}

	void printArray(int tab[], int size) {
		cout << Help::PRINT<<"\n";
		for (int i = 0; i < size; ++i) {
			cout << "I: " << i << "\t Value: " << tab[i] << endl;
		}
		cout << "-----------------\n";
	}

	void printArray(int tab[], int a, int b) {
		cout << Help::PRINT << "\n";
		for (int i = a; i <= b; ++i) {
			cout << "I: " << i << "\t Value: " << tab[i] << endl;
		}
		cout << "-----------------\n";
	}

	void copyArray(int source[], int dest[], int size) {
		for (int i = 0; i < size; ++i) {
			dest[i] = source[i];
		}
	}

	int* copyArray(int source[], int size) {
		int* tab = new int[size];

		for (int i = 0; i < size; ++i) {
			tab[i] = source[i];
		}

		return tab;
	}

	int* copyArray(int source[], int a, int b) {
		int size = (b - a) + 1;
		int* tab = new int[size];

		for (int i = 0; i < size; ++i) {
			tab[i] = source[a+i];
		}

		return tab;
	}

	void generate(int tab[], int size, int min, int max) {
		for (int i = 0; i < size; ++i) {
			tab[i] = rand() % (max - min) + min;
		}
	}

	bool isSorted(int tab[], int size, bool asc) {
		if (asc) {
			for (int i = 0; i < size - 1; ++i) {
				if (tab[i + 1] < tab[i]) {
					return false;
				}
			}
		}
		else {
			for (int i = 0; i < size - 1; ++i) {
				if (tab[i + 1] > tab[i]) {
					return false;
				}
			}
		}
		return true;
	}

	/**
		returns true if str contains str2
	*/
	bool contains(char* str, std::string str2) {
		std::string conv = str;
		return conv.find(str2) != std::string::npos;
	}
}