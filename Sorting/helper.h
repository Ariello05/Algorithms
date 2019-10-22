#pragma once
#include <string>
#include <vector>

void swap(int tab[], int i1, int i2);
template<class T>
void swap(T tab, int i1, int i2);

void printArray(int tab[], int size);

void copyArray(int source[], int dest[], int size);

int * copyArray(int source[], int size);

void generate(int tab[], int size, int min, int max);

bool isSorted(int tab[], int size, bool asc);

bool contains(char *, std::string);

template<class T>
inline void swap(T tab, int i1, int i2)
{
	int buf = tab[i1];
	tab[i1] = tab[i2];
	tab[i2] = buf;
}
