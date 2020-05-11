#pragma once
#include <string>
#include <list>
#include "Tree.h"
#include "RB.h"

using std::string;


template <typename T>
class HashMap :public Tree<T> {
public:
	HashMap();
	~HashMap();
	virtual void insert(T) override;
	virtual void remove(T) override;
	virtual bool search(T) override;
	virtual std::string inOrder() override;
	virtual void bfs() override;
	virtual std::string min() override;
	virtual std::string max() override;
	virtual std::string successor(T f) override;
private:
	const int nt = 5;
	const int m = 1500;
	std::pair<RB<T>,std::list<T>>* map;
	int hash(T item);
};

template<typename T>
inline int HashMap<T>::hash(T item)
{
	int hash_sum = 0;
	for (int i = 0; i < item.length(); ++i) {
		hash_sum += int(item[i]);
	}
	hash_sum %= m;

	return hash_sum;
}


template<typename T>
inline HashMap<T>::HashMap()
{
	map = new std::pair<RB<T>, std::list<T>>[m];
}

template<typename T>
inline HashMap<T>::~HashMap()
{
	delete[] map;
}

template<typename T>
inline void HashMap<T>::insert(T item)
{
	Tree<T>::insert(item);
	int mapped = hash(item);
	if (item.length() >= nt) {
		map[mapped].first.insert(item);
	}
	else {
		map[mapped].second.push_front(item);
	}
}

template<typename T>
inline void HashMap<T>::remove(T item)
{
	Tree<T>::remove(item);
	int mapped = hash(item);
	
	if (item.length() >= nt) {
		auto initial_size = map[mapped].first.getSize();
		map[mapped].first.remove(item);
		if (initial_size != map[mapped].first.getSize()) {
			this->size--;
		}

	}
	else {
		
		auto start = map[mapped].second.begin();
		while (start != map[mapped].second.end()) {
			if (*start == item) {
				map[mapped].second.erase(start);
				this->size--;
				break;
			}
			start++;
		}
	}
}

template<typename T>
inline bool HashMap<T>::search(T item)
{
	Tree<T>::search(item);
	int mapped = hash(item);
	if (item.length() >= nt) {
		return map[mapped].first.search(item);
	}
	else {
		auto start = map[mapped].second.begin();
		while (start != map[mapped].second.end()) {
			if (*start == item) {
				return true;
			}
			start++;
		}
	}
	return false;
}

template<typename T>
inline std::string HashMap<T>::inOrder()
{
	Tree<T>::inOrder();
	return std::string();
}

template<typename T>
inline void HashMap<T>::bfs()
{
	return;
}

template<typename T>
inline std::string HashMap<T>::min()
{
	Tree<T>::min();
	return std::string();
}

template<typename T>
inline std::string HashMap<T>::max()
{
	Tree<T>::max();
	return std::string();
}

template<typename T>
inline std::string HashMap<T>::successor(T f)
{
	Tree<T>::successor(f);
	return std::string();
}

