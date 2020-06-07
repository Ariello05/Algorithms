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
	virtual void updateVariables() override;
	virtual void resetSwapsChecks() override;
private:
	const int nt = 2; 
	const int m = 2011;
	std::pair<RB<T>,std::list<T>>* map;
	int hash(T item);
};

template<typename T>
inline int HashMap<T>::hash(T item)
{
	int hash_sum = 0;
	int order = 1;
	for (int i = 0; i < item.length(); ++i) {
		hash_sum += int(item[i]) * order;
		order += 1;
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
	if (item.length() > nt) {
		
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
	
	if (item.length() > nt) {
		auto initial_size = map[mapped].first.getSize();
		map[mapped].first.remove(item);
		if (initial_size != map[mapped].first.getSize()) {
			this->size--;
		}

	}
	else {
		
		auto start = map[mapped].second.begin();

		while (start != map[mapped].second.end()) {
			this->checks++;
			if (*start == item) {
				this->swaps++;
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
	if (item.length() > nt) {
		return map[mapped].first.search(item);
	}
	else {
		auto start = map[mapped].second.begin();
		while (start != map[mapped].second.end()) {
			this->checks++;
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

template<typename T>
inline void HashMap<T>::updateVariables()
{
	for (int i = 0; i < m; ++i) {
		this->swaps += map[i].first.getSwaps();
		this->checks += map[i].first.getChecks();
	}
}

template<typename T>
inline void HashMap<T>::resetSwapsChecks()
{
	Tree<T>::resetSwapsChecks();
	
	for (int i = 0; i < m; ++i) {
		map[i].first.resetSwapsChecks();
		//std::cout << pair.first.getSwaps() << std::endl;
	}
}

