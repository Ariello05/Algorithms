#pragma once
#include "Helper.hpp"
#ifdef _WIN32
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include "psapi.h"
#endif
/**
	Interfejs...
*/
template <typename T>
class ISort
{
public:
	ISort(bool asc = true, bool log = false)
		:asc(asc), log(log) {}

	virtual ~ISort() {};

	counter_s sort(T tab[], int size) {
		return runSort(tab, size);
	}

	counter_s sort(T tab[], int size, bool asc) {
		setASC(asc);
		return sort(tab, size);
	}

protected:
	bool asc;
	bool log;

private:
	virtual void setASC(bool asc) { this->asc = asc; }
	virtual counter_s runSort(T arr[], int size) = 0;

};

