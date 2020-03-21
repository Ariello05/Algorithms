#pragma once
#include "ISort.hpp"
#include <string>
#include <iostream>
using std::cerr;
using std::endl;


template <typename T>
class QuickSort :public ISort<T> {
public:
	QuickSort(bool asc = true, bool log = false);
private:

	virtual counter_s runSort(T tab[], int size);
	int partition(T tab[], int begin, int end, counter_s& counter);

	bool compare(T tab[], int j, T x);
	void quickSort(T tab[], int p, int r, counter_s& checks);

	bool qsCheckASC(T tab[], int j, T x);
	bool qsCheckDESC(T tab[], int j, T x);

};

template<typename T>
inline QuickSort<T>::QuickSort(bool asc, bool log)
	:ISort<T>(asc, log)
{
}

template<typename T>
inline counter_s QuickSort<T>::runSort(T tab[], int size)
{
	counter_s counter;
	counter.checks = 0;
	counter.swaps = 0;

	quickSort(tab, 0, size - 1, counter);

	return counter;
}

template<typename T>
inline int QuickSort<T>::partition(T tab[], int begin, int end, counter_s& counter) {
	T x = tab[end];
	int i = begin - 1;
	for (int j = begin; j <= end - 1; ++j) {
		counter.checks++;
		if (this->log) { cerr << Help::COMPARE<<"Index: [" << j << "] " << tab[j] << "\t WITH \t Pivot: " << x << endl; }
		if (compare(tab, j, x)) {
			++i;
			if (this->log) { cerr << Help::SWAP<<"Index: [" << i << "] " << tab[i] << "\t WITH \t Index: [" << j << "] " << tab[j] << endl; }
			Help::swap(tab, i, j);
			counter.swaps++;
		}
	}
	if (this->log) { cerr << Help::SWAP<<"Index: [" << i + 1 << "] " << tab[i + 1] << "\t WITH \t Pivot: " << x << endl; }
	Help::swap(tab, i + 1, end);
	counter.swaps++;
	return i + 1;
}

template<typename T>
inline bool QuickSort<T>::compare(T tab[], int j, T x)
{
	if (this->asc) {
		return qsCheckASC(tab, j, x);
	}
	else {
		return qsCheckDESC(tab, j, x);
	}
}

template<typename T>
inline void QuickSort<T>::quickSort(T tab[], int begin, int end, counter_s& checks)
{
	if (begin < end) {//only if beg is higher than end
		int q = partition(tab, begin, end, checks);

		quickSort(tab, begin, q - 1, checks);
		quickSort(tab, q + 1, end, checks);
	}
}

template<typename T>
inline bool QuickSort<T>::qsCheckASC(T tab[], int j, T x)
{
	return (tab[j] <= x);
}

template<typename T>
inline bool QuickSort<T>::qsCheckDESC(T tab[], int j, T x)
{
	return (tab[j] >= x);
}
