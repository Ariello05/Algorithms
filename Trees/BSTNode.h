#pragma once

template<class T>
class BSTNode {
public:
	BSTNode() :value() {
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

	BSTNode* getLeftNode() {
		return left;
	}

	BSTNode* getRightNode() {
		return right;
	}

	T getValue() {
		return value;
	}

	void setRightNode(BSTNode* node) {
		right = node;
	}

	void setLeftNode(BSTNode* node) {
		left = node;
	}

	void setValue(T val) {
		value = val;
	}

private:
	BSTNode* left;
	BSTNode* right;
	T value;
};