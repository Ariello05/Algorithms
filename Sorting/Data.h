#pragma once
#include <vector>

template<typename T>		
class Data {
public:
	Data(T tab[], int length) {
		for (size_t i = 0; i < length; i++)
		{
			data.push_back(tab[i]);
		}
	}

	Data(std::vector<T> arr) {
		data = arr;
	}

	//... others

	std::vector<T> & get() {
		return data;
	}

private:
	std::vector<T> data;
};