#pragma once
#include <iostream>
#include "BSTNode.h"


template<class T>
class SplayNode{
public:
	SplayNode<T>() : value() {
		parent = nullptr;
		left = nullptr;
		right = nullptr;
	}
	SplayNode<T>(T v) {
		parent = nullptr;
		left = nullptr;
		right = nullptr;
		value = v;
	}
	~SplayNode<T>() {
	}


	operator T() {
		return value;
	}

	bool operator<= (T right) {
		return value <= right;
	}

	bool operator>= (T right) {
		return value >= right;
	}

	bool operator== (T right) {
		return value == right;
	}

	bool operator> (T right) {
		return value > right;
	}

	bool operator< (T right) {
		return value < right;
	}

	SplayNode* getLeftNode() {
		return left;
	}

	SplayNode* getRightNode() {
		return right;
	}

	SplayNode* getParent() {
		return parent;
	}

	T getValue() {
		return value;
	}

	void setParent(SplayNode* parent) {
		this->parent = parent;
	}

	void setRightNode(SplayNode* node) {
		right = node;
	}

	void setLeftNode(SplayNode* node) {
		left = node;
	}

	void setValue(T val) {
		value = val;
	}


private:
	SplayNode<T>* parent;
	SplayNode<T>* left;
	SplayNode<T>* right;
	T value;
};


template<class T>
std::ostream& operator<<(std::ostream& os, SplayNode<T>& rb) {
	os <<rb.getValue();
	return os;
}