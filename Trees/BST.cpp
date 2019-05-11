#include "BST.h"
#include <iostream>
#include <deque>
using std::string;

BST::BST() {
	top = nullptr;
}

void BST::insert(string str)
{
	if (top == nullptr) {
		top = new BSTNode<string>(str);
	}
	else {
		stringNode prev = top;
		stringNode iter = top;
		bool left;
		while (iter != nullptr) {
			if (*iter > str) {
				prev = iter;
				iter = iter->left;
				left = true;
			}
			else {
				prev = iter;
				iter = iter->right;
				left = false;
			}
		}
		iter = new BSTNode<string>(str);
		if (left) {
			prev->left = iter;
		}
		else {
			prev->right = iter;
		}
	}
}


void BST::remove(string str)
{
	stringNode prev = top;
	stringNode iter = top;
	bool left = true;
	while (iter != nullptr) {
		if (*iter == str) {
			if (iter->right == nullptr && iter->left == nullptr) {//no children
				if (left) {//subtree root update
					prev->left = nullptr;
				}
				else {
					prev->right = nullptr;
				}

				if (iter == top) {//delete root
					top = nullptr;
					delete top;
				}
				else {
					delete iter;
				}
				break;
			}
			else if(iter->right == nullptr) {//left children only
				if (left) {//subtree root update
					prev->left = iter->left;
				}
				else {
					prev->right = iter->left;
				}
				break;
			}
			else if (iter->left == nullptr) {//right children only
				if (left) {//subtree root update
					prev->left = iter->right;
				}
				else {
					prev->right = iter->right;
				}
				break;
			}
			else {//both children up
				stringNode temp = min(iter->right);
				if (left) {//subtree root update
					prev->left = temp;
				}
				else {
					prev->right = temp;
				}

				if (iter->right == temp) {//simpler case: right child is minimal
					temp->left = iter->left;
				}
				else {//harder case: have to translate right child left node to minimum right node
					stringNode r = temp->right;
					r->left = temp->right;
					temp->right = r;
				}
				delete iter;
				break;
			}
		}
		if (*iter > str) {
			left = true;
			prev = iter;
			iter = iter->left;
		}
		else {
			left = false;
			prev = iter;
			iter = iter->right;
		}
	}
}

void BST::search(string str)
{
	stringNode iter = top;
	while (iter != nullptr) {
		if (*iter == str) {
			std::cout << "1" << std::endl;
			return;
		}
		if (*iter > str) {
			iter = iter->left;
		}
		else {
			iter = iter->right;
		}
	}
	std::cout << "0" << std::endl;
}

void BST::inOrder()
{
	printf("\n =inOrder= \n");
	print(top);
}

void BST::bfs()
{
	printf("\n =BFS= \n");
	if (top != nullptr) {
		std::deque<BSTNode<string>> deq;
		deq.push_back(*top);
		BSTNode<string> temp;
		while (!deq.empty()) {
			temp = deq.front();
			std::cout << deq.front().value;
			deq.pop_front();
			if (temp.left != nullptr) {
				deq.push_back(*temp.left);
				std::cout << "\t<-- \t";
			}
			else {
				std::cout << "\t";
			}
			if (temp.right != nullptr) {
				deq.push_back(*temp.right);
				std::cout << "-->";
			}
			std::cout << std::endl;
		}

	}
	else {
		std::cout << "Empty...\n";
	}

}

stringNode BST::min(stringNode current)
{
	while (current->left != nullptr) {
		current = current->left;
	}
	return current;
}

void BST::print(stringNode n)//dfs
{
	if (n != nullptr) {
		print(n->left);
		std::cout << n->value << std::endl;
		print(n->right);
	}
}

