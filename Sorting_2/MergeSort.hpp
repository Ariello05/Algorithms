#pragma once
#include "ISort.hpp"
#include <string>
#include <iostream>
using std::cerr;
using std::endl;


template <typename T>
class MergeSort :public ISort<T> {
public:
	MergeSort(bool asc = true, bool log = false);
private:

	virtual counter_s runSort(T tab[], int size);
	void merge(T tab[], int begin, int end, counter_s& counter);

	bool compare(T tab[], T copy[], int j, int i);

	bool msCheckASC(T tab[], T copy[], int j, int i);
	bool msCheckDESC(T tab[], T copy[], int j, int i);

};

template<typename T>
inline MergeSort<T>::MergeSort(bool asc, bool log)
	:ISort<T>(asc, log)
{

}

template<typename T>
inline counter_s MergeSort<T>::runSort(T tab[], int size)
{
	counter_s counter;
	counter.checks = 0;
	counter.swaps = 0;

	if (size == 1) {
		return counter;
	}
	merge(tab,0,size-1, counter);

	return counter;
}

template<typename T>
inline void MergeSort<T>::merge(T tab[], int begin, int end, counter_s& counter)
{
	if (end <= begin) {
		return;
	}
	else {
		int mid = (end+begin) / 2;
		merge(tab, begin, mid, counter);
		merge(tab, mid + 1, end, counter);

		int i = 0;
		int j = mid + 1;
		T* copy = Help::copyArray(tab, begin, mid);
		for (int k = begin; k <= end; k++) {

			counter.checks++;
			if ((i+begin <= mid && compare(tab,copy,j,i)) || j > end) {
				counter.swaps++;
				if (this->log) { cerr << Help::SET << "Index [" << k << "]\t = \t" << copy[i] << "\n"; }
				tab[k] = copy[i++];
			}
			else {
				counter.swaps++;
				if (this->log) { cerr << Help::SET << "Index [" << k << "] \t = \t" << tab[j] << "\n"; }
				tab[k] = tab[j++];
			}
		}
		delete[] copy;
	}
}

template<typename T>
inline bool MergeSort<T>::compare(T tab[], T copy[], int j, int i)
{
	if (this->asc) {
		return msCheckASC(tab, copy, j, i);
	}
	else {
		return msCheckDESC(tab, copy, j, i);
	}
}

template<typename T>
inline bool MergeSort<T>::msCheckASC(T tab[], T copy[], int j, int i)
{
	if (this->log) { cerr << Help::COMPARE << "Index [" << i << "] \t WITH \t Index[" << j << "]\n"; }
	return copy[i] < tab[j];
}

template<typename T>
inline bool MergeSort<T>::msCheckDESC(T tab[], T copy[], int j, int i)
{
	if (this->log) { cerr << Help::COMPARE << "Index [" << i << "] \t WITH \t Index[" << j << "]\n"; } 
	return copy[i] > tab[j];
}
