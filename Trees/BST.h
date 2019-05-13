#pragma once
#include <string>
#include "Tree.h"
#include "Node.h"

using std::string;

using stringNode = BSTNode<string>*;

class BST :Tree<string> {
public:
	BST();
	virtual void insert(string) override;
	virtual void remove(string) override;
	virtual void search(string) override;
	virtual void inOrder() override;
	void bfs();
private:
	stringNode min(stringNode current, stringNode& prev);
	void print(stringNode n);
	stringNode top;
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