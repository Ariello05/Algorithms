#pragma once
#include "Data.h"

template <typename T>
class ISort
{
public:
	ISort(bool asc = true, bool log = false)
		:asc(asc), log(log){}

	virtual ~ISort() {};
	
	/*
	 void sort(T tab[], int size) {
		std::vector<T> ob;
		for (size_t i = 0; i < size; i++)
		{
			ob.push_back(tab[i]);
		}
		runSort(ob);
	}

	void sort(T tab[], int size, bool asc) {
		setASC(asc);
		sort(tab, size);
	}*/

	void sort(const T arr[], int size) {
		runSort(&arr[0], size);
	}

	void sort(T & tab, int size) {
		runSort(tab, size);
	}

	void sort(T & tab, int size, bool asc) {
		setASC(asc);
		sort(tab, size);
	}

protected:
	bool asc;
	bool log;

private:
	virtual void setASC(bool asc) { this->asc = asc; }
	virtual void runSort(T & ob, int size) = 0;

};

