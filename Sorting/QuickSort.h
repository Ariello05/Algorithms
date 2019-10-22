#pragma once
#include "ISort.h"

template<class T>
class QuickSort: public ISort<T>{
public:
	QuickSort<T>(bool asc = true, bool log = false)
		:ISort<T>(asc,log){
		func = asc ? &QuickSort::ASC : &QuickSort::DESC;
	}

	/*virtual void sort(T tab[], int size) {
		std::vector<T> ob;
		for (int i = 0; i < size; ++i) {
			ob.push_back(tab[i]);
		}
		quick(ob, 0, size-1);
	}*/

	/*template <class K>
	virtual void sort(K <T> & ob, int size, bool asc) {
		setASC(asc);
		sort(ob, 0);
	}*/

private:
	bool (QuickSort::*func)(int j, int x);
	T ob;

	virtual void setASC(bool asc) {
		func = asc ? &QuickSort::ASC : &QuickSort::DESC;
	}

	virtual void runSort(T & ob, int size) {
		this->ob = ob;
		quick(0, size);
	}

	int partition(int left, int right);
	bool ASC(int j, int x);
	bool DESC(int j, int x);
	void quick(int left, int right);
};

template<class T>
inline int QuickSort<T>::partition(int left, int right)
{
	int x = ob[right];
	int il = left - 1;
	for (int j = left; j <= right - 1; ++j) {
		//counter.checks++;
		//cerr << "COMPERING Index: [" << j << "] " << tab[j] << "\twith Pivot: " << x << endl;
		if ((this->*func)(j, x)) {
			++il;
			//cerr << "SWAPPING Index: [" << i << "] " << tab[i] << "\twith Index: [" << j << "] " << tab[j] << endl;
			swap(ob, il, j);
			//counter.swaps++;
		}
	}
	//cerr << "SWAPPING Index: [" << i+1 << "] " << tab[i+1] << "\twith Pivot: " << x << endl;
	swap(ob, il + 1, right);
	//counter.swaps++;
	return il + 1;
}
template<class T>
inline bool QuickSort<T>::ASC(int j, int x)
{
	return (ob[j] <= x);
}
template<class T>
inline bool QuickSort<T>::DESC(int j, int x)
{
	return (ob[j] >= x);
}
template<class T>
inline void QuickSort<T>::quick(int left, int right)
{
	if (left < right) {//only if beg is higher than end
		int q = partition(left, right);

		quick(left, q - 1);
		quick(q + 1, right);
	}
}

