#pragma once
#include <string>

void swap(int tab[], int i1, int i2);

void printArray(int tab[], int size);

void copyArray(int source[], int dest[], int size);

int * copyArray(int source[], int size);

void generate(int tab[], int size, int min, int max);

bool isSorted(int tab[], int size, bool asc);

bool contains(char *, std::string);
