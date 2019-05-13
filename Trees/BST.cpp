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
		while (iter != nullptr) {
			prev = iter;

			if (*iter > str) {
				iter = iter->left;
			}
			else {
				iter = iter->right;
			}
		}
		
		iter = new BSTNode<string>(str);
		
		if (*prev > str) {
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
	while (iter != nullptr) {
		if (*iter == str) {
			if (iter->right == nullptr && iter->left == nullptr) {//no children
				if (*iter < *prev) {
					prev->left = nullptr;
				}
				else {
					prev->right = nullptr;
				}

				if (iter == top) {//delete root
					delete top;
					top = nullptr;
				}
				else {
					delete iter;
				}
				break;
			}
			else if(iter->right == nullptr) {//left children only
				if (*iter < *prev) {
					prev->left = iter->left;
				}
				else {
					prev->right = iter->left;
				}
				break;
			}
			else if (iter->left == nullptr) {//right children only
				if (*iter < *prev) {
					prev->left = iter->right;
				}
				else {
					prev->right = iter->right;
				}
				break;
			}
			else {//both children up
				stringNode minPrev;//previous node to minN
				stringNode minN = min(iter->right, minPrev);//minimum of right subtree

				if(iter->right == minN) {
					minN->left = iter->left;
				}
				else {//harder case: have to translate right child left node to minimum right node
					minPrev->left = minN->right;
					minN->left = iter->left;
					minN->right = iter->right; 
				}

				if (iter == top) {
					top = minN;
				}
				else {
					if (*iter < *prev) {
						prev->left = minN;
					}
					else {
						prev->right = minN;
					}
				}

				delete iter;
				break;
			}
		}
		else if (*iter > str) {
			prev = iter;
			iter = iter->left;
		}
		else {
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

stringNode BST::min(stringNode current, stringNode & prev)
{
	while (current->left != nullptr) {
		prev = current;
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

