#pragma once
#include <iostream>

template<class T>
class BSTNode {
public:
	BSTNode() {
		left = nullptr;
		right = nullptr;
	}
	BSTNode(T v) {
		value = v;
		left = nullptr;
		right = nullptr;
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

	BSTNode* left;
	BSTNode* right;
	T value;
};

enum COLOR { RED, BLACK };

template<class T>
class RBNode {
private:
	COLOR color;
	bool sentinel;

public:
	RBNode<T>() {
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
		if (left ->isSentinel()) {
			return BLACK;
		}
		else {
			return left->color;
		}
	}

	RBNode<T>* parent;
	RBNode<T>* left;
	RBNode<T>* right;
	T value;
};


template<class T>
std::ostream& operator<<(std::ostream& os, RBNode<T>& rb) {

	if (rb.getColor() == RED) {
		os << "(R): " << rb.value;
	}
	else {
		os << "(B): " << rb.value;
	}
	return os;
}

template<class T>
bool operator<= (RBNode<T> left, T right) {
	return left.value <= right;
}

template<class T>
bool operator== (RBNode<T> left, T right) {
	return left.value == right;
}

template<class T>
bool operator> (RBNode<T> left, T right) {
	return left.value > right;
}






