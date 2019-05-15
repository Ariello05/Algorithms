#pragma once
#include "helper.h"
#include <time.h>
#include <random>
#include <iostream>
#include <stdio.h>

using std::cout;
using std::endl;
using std::cerr;

typedef struct counter_t {
	int checks;
	int swaps;

}counter_s;

bool ssCheckASC(int tab[], int j, int maxmin);
bool ssCheckDESC(int tab[], int j, int maxmin);
counter_s selectSort(int tab[], int size, bool asc);

bool isCheckASC(int tab[], int j, int elem);
bool isCheckDESC(int tab[], int j, int elem);
counter_s insertionSort(int tab[], int size, bool asc);

bool hscheckASC(int tab[], int indexL, int maxmin);
bool hscheckDESC(int tab[], int indexL, int maxmin);
void heapify(int tab[], int n, int i, counter_s & checks, bool(*f)(int *tab, int l, int r));
counter_s heapSort(int tab[], int n, bool asc);

int partition(int tab[], int p, int r, counter_s & counter, bool(*f)(int * tab, int j, int x));
bool qscheckASC(int tab[], int j, int x);
bool qscheckDESC(int tab[], int j, int x);
void quicksortFP2(int tab[], int p, int r, counter_s &checks, bool(*f)(int * tab, int j, int x));
counter_s quickSort(int tab[], int n, bool asc);

void mIS(int tab[], int p, int r, counter_s & counter, bool asc);
int partition3m(int tab[], int p, int r, counter_s & counter, bool(*f)(int * tab, int j, int x));
void mQS(int tab[], int p, int r, counter_s &checks, bool(*f)(int * tab, int j, int x), bool asc);
counter_s modifiedQuickSort(int tab[], int n, bool asc);
