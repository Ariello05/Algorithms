#pragma once
#include <string>
typedef struct counter_t {
	int checks;
	int swaps;

}counter_s;

namespace Help{

	const std::string SWAP = "  \033[1;34mSWAP\033[0m   ";
	const std::string SET = "   \033[1;34mSET\033[0m   ";
	const std::string COMPARE = " \033[1;32mCOMPARE\033[0m ";
	const std::string PRINT = " \n\033[1;36mPRINT ARRAY!\033[0m ";

	void swap(int tab[], int i1, int i2);
	template<class T>
	void swap(T tab, int i1, int i2);
	void printArray(int tab[], int size);
	void printArray(int tab[], int a, int b);
	void copyArray(int source[], int dest[], int size);
	int* copyArray(int source[], int size);
	int* copyArray(int source[], int a, int b);
	void generate(int tab[], int size, int min, int max);
	bool isSorted(int tab[], int size, bool asc);
	bool contains(char*, std::string);

	template<class T>
	inline void swap(T tab, int i1, int i2)
	{
		int buf = tab[i1];
		tab[i1] = tab[i2];
		tab[i2] = buf;
	}
}
