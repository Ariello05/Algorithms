#pragma once

template <typename T>
class ISort;

class Array {

};

class Sort{
	
	template <class Alg, class K>
	void sort(K & tab, int size) {
		ISort<K> *alg = new Alg();
		alg->sort(tab, size);
	}

	template <class Alg, class K>
	void sort(K & tab, int size, bool asc) {
		ISort<K> *alg = new Alg();
		alg->sort(tab,size,asc);
	}

private:
	ISort<int> *alg;
};