#pragma once
#include "Tree.h"
#include "Node.h"
#include <string>
using std::string;

template<typename T>
class Splay :public Tree<T>{
public:
	Splay();
	~Splay();
	virtual void insert(T val);
	virtual void remove(T val);
	virtual bool search(T val);
	virtual std::string inOrder();
	virtual void bfs();
private:

	SplayNode<T>* splay(SplayNode<T>* root, T x);
	void leftRotate(SplayNode<T>* n);
	void rightRotate(SplayNode<T>* n);
	void print(SplayNode<T>* n, std::string & buffor);
	SplayNode<T>* top;

};


//#include "Splay.cpp"