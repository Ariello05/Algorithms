#pragma once
#include "Tree.h"
#include "RBNode.h"
#include <string>

using std::string;
template<typename T>
using node = RBNode<T>*;

template<typename T>
class RB :public Tree<T>
{
public:
	RB();
	virtual void insert(T) override;
	virtual void remove(T) override;
	virtual bool search(T) override;
	virtual std::string inOrder() override;
	virtual void bfs() override;
	virtual std::string min() override;
	virtual std::string max() override;
	virtual std::string successor(T f) override;
	int getSize();

private:

	node<T> get(T);
	void insertFix(node<T> z);
	void deleteFix(node<T> z);
	void transplant(node<T> x, node<T> y);
	node<T> min(node<T> current);
	void leftRotate(node<T> n);
	void rightRotate(node<T> n);

	void print(node<T> n, std::string& buffor);
	node<T> top;

};


