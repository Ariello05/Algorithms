#pragma once
#include "Tree.h"
#include "Node.h"
#include <string>

using std::string;
using node = RBNode<string>*;

class RB :public Tree<string>
{
public:
public:
	RB();
	virtual void insert(string) override;
	virtual void remove(string) override;
	virtual void search(string) override;
	virtual void inOrder() override;
	void bfs();
private:
	node get(string);
	void insertFix(node z);
	void deleteFix(node z);
	void transplant(node x, node y);
	node min(node current);
	void leftRotate(node n);
	void rightRotate(node n);

	void print(node n);
	node top;
};


