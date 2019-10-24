#pragma once
#include"stdafx.h"

template<class T>
class UniqueVector {
public:
	void push_back(T val) {
		if (search(val)) {
			throw std::invalid_argument("This value already exists!");
		}
		vect.push_back(val);
	}

	bool soft_push_back(T val) {
		if (search(val)) {
			return true;
		}
		vect.push_back(val);
		return false;
	}

	size_t size()const {
		return vect.size();
	}

	T operator[](const int& index)const {
		return vect[index];
	}

	void clear() {
		vect.clear();
	}

	bool search(T val)const {
		auto beg = vect.begin();
		const auto end = vect.end();
		while (beg != end) {
			if (*beg == val) {
				return true;
			}
			beg++;
		}
		return false;
	}

private:
	std::vector<T> vect;
};