#pragma once
#include <iostream>
enum COLOR { RED, BLACK };

template<class T>
class RBNode {
public:
	RBNode<T>():value() {
		parent = nullptr;
		left = nullptr;
		right = nullptr;
		color = COLOR::RED;
		sentinel = false;
	}
	RBNode<T>(T v) {
		parent = nullptr;
		left = nullptr;
		right = nullptr;
		color = COLOR::RED;
		sentinel = false;
		value = v;
	}
	~RBNode<T>() {
	}

	bool isSentinel() {
		return sentinel;
	}

	void setSentinel(bool s) {
		sentinel = s;
		if (sentinel) {
			color = BLACK;
		}
	}

	COLOR getColor() {
		return color;
	}

	void setColor(COLOR c) {
		color = c;
	}

	COLOR getRightColor() {
		if (right->isSentinel()) {
			return BLACK;
		}
		else {
			return right->color;
		}
	}

	COLOR getLeftColor() {
		if (left->isSentinel()) {
			return BLACK;
		}
		else {
			return left->color;
		}
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

	RBNode* getLeftNode() {
		return left;
	}

	RBNode* getRightNode() {
		return right;
	}

	RBNode* getParent() {
		return parent;
	}

	T getValue() {
		return value;
	}

	void setParent(RBNode* parent) {
		this->parent = parent;
	}

	void setRightNode(RBNode* node) {
		right = node;
	}

	void setLeftNode(RBNode* node) {
		left = node;
	}

	void setValue(T val) {
		value = val;
	}


private:
	COLOR color;	
	bool sentinel;
	RBNode<T>* parent;
	RBNode<T>* left;
	RBNode<T>* right;
	T value;
};


template<class T>
std::ostream& operator<<(std::ostream& os, RBNode<T>& rb) {

	if (rb.getColor() == RED) {
		os << "(R): " << rb.getValue();
	}
	else {
		os << "(B): " << rb.getValue();
	}
	return os;
}
