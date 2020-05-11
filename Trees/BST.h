#pragma once
#include <string>
#include "Tree.h"
#include "BSTNode.h"

using std::string;

template <typename T>
using stringNode = BSTNode<T>*;

template <typename T>
class BST :public Tree<T> {
public:
	BST();
	virtual void insert(T) override;
	virtual void remove(T) override;
	virtual bool search(T) override;
	virtual std::string inOrder() override;
	virtual void bfs() override;
	virtual std::string min() override;
	virtual std::string max() override;
	virtual std::string successor(T f) override;
private:
	stringNode<T> min(stringNode<T> current);
	stringNode<T> min(stringNode<T> current, stringNode<T>& prev);
	void print(stringNode<T> n, std::string& buffor);
	stringNode<T> top;
};


/*
template<int>
class IntBST : Tree<int> {
public:
	virtual void insert(int) override;
	virtual void remove(int) override;
	virtual bool search(int) override;
	virtual void inOrder() override;
private:
};
*/