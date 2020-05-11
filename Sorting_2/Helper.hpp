#pragma once
#include <string>
#include <iostream>
/**
	Plik z funkcjami pomocniczymi
*/
typedef struct counter_t {
	long long checks;
	long long swaps;
	size_t memory;
}counter_s;

typedef struct select_t {
	long long checks;
	long long swaps;
	long long value;
}select_s;

using std::cout;
using std::endl;
using std::rand;

namespace Help{

	const std::string SWAP = "  \033[1;34mSWAP\033[0m   ";
	const std::string SET = "   \033[1;34mSET\033[0m   ";
	const std::string COMPARE = " \033[1;32mCOMPARE\033[0m ";
	const std::string PRINT = " \n\033[1;36mPRINT ARRAY!\033[0m ";

	//void swap(int tab[], int i1, int i2);
	//template<class T>
	//void swap(T tab, int i1, int i2);

	template <typename T>
	void copyArray(T source[], T dest[], int size) {
		for (int i = 0; i < size; ++i) {
			dest[i] = source[i];
		}
	}

	template <typename T>
	T* copyArray(T source[], int size) {
		T* tab = new T[size];

		for (int i = 0; i < size; ++i) {
			tab[i] = source[i];
		}

		return tab;
	}

	template <typename T>
	T* copyArray(T source[], int a, int b) {
		int size = (b - a) + 1;
		T* tab = new T[size];

		for (int i = 0; i < size; ++i) {
			tab[i] = source[a + i];
		}

		return tab;
	}

	void generate(int tab[], int size, int min, int max);

	template <typename T>
	bool isSorted(T tab[], int size, bool asc) {
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

	bool contains(char*, std::string);
	bool contains(std::string, std::string);

	template <typename T>
	void printArray(T tab[], int size) {
		cout << Help::PRINT << "\n";
		for (int i = 0; i < size; ++i) {
			cout << "I: " << i << "\t Value: " << tab[i] << endl;
		}
		cout << "-----------------\n";
	}

	template <typename T>
	void printStatisticArray(T tab[], int size, int statistic) {
		cout << Help::PRINT << "\n";
		for (int i = 0; i < size; ++i) {
			if (i == statistic) {
				cout << "STATISTIC: " << i << "\t Value: [" << tab[i] << "]" << endl;
			}
			else {
				cout << "I: " << i << "\t Value: " << tab[i] << endl;
			}
		}
		cout << "-----------------\n";
	}

	template <typename T>
	void printArray(T tab[], int a, int b) {
		cout << Help::PRINT << "\n";
		for (int i = a; i <= b; ++i) {
			cout << "I: " << i << "\t Value: " << tab[i] << endl;
		}
		cout << "-----------------\n";
	}

	template<class T>
	inline void swap(T tab[], int i1, int i2)
	{
		T buf = tab[i1];
		tab[i1] = tab[i2];
		tab[i2] = buf;
	}
}
