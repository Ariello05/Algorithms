#include "BST.h"
#include <iostream>
#include <deque>
using std::string;

template class BST<string>;

template <typename T>
BST<T>::BST() {
	top = nullptr;
}

template <typename T>
void BST<T>::insert(T str)
{
	Tree<T>::insert(str);

	if (top == nullptr) {
		top = new BSTNode<T>(str);
		Tree<T>::swaps++;
	}
	else {
		stringNode<T> prev = top;
		stringNode<T> iter = top;
		while (iter != nullptr) {
			prev = iter;

			Tree<T>::checks+=2;//while + below
			if (*iter > str) {
				iter = iter->getLeftNode();
			}
			else {
				iter = iter->getRightNode();
			}
		}
		
		iter = new BSTNode<T>(str);
		Tree<T>::checks++;
		if (*prev > str) {
			prev->setLeftNode(iter);
		}
		else {
			prev->setRightNode(iter);
		}
		Tree<T>::swaps++;
	}
}



template <typename T>
void BST<T>::remove(T str)
{
	Tree<T>::remove(str);

	stringNode<T> prev = top;
	stringNode<T> iter = top;
	while (iter != nullptr) {
		Tree<T>::checks+=2;
		if (*iter == str) {
			if (Tree<T>::size > 0) {
				Tree<T>::size--;
			}

			Tree<T>::checks+=2;
			if (iter->getRightNode() == nullptr && iter->getLeftNode() == nullptr) {//no children
				Tree<T>::checks++;
				if (*iter < *prev) {
					prev->setLeftNode(nullptr);
				}
				else {
					prev->setRightNode(nullptr);
				}
				Tree<T>::swaps++;

				Tree<T>::checks++;
				if (iter == top) {//delete root
					delete top;
					top = nullptr;
					Tree<T>::swaps++;
				}
				else {
					delete iter;
				}
				break;
			}
			else if(iter->getRightNode() == nullptr) {//left children only
				Tree<T>::checks+=2;
				if (*iter < *prev) {
					prev->setLeftNode(iter->getLeftNode());
				}
				else {
					prev->setRightNode(iter->getLeftNode());
				}
				Tree<T>::swaps++;
				break;
			}
			else if (iter->getLeftNode() == nullptr) {//right children only
				Tree<T>::checks+=2;
				if (*iter < *prev) {
					prev->setLeftNode(iter->getRightNode());
				}
				else {
					prev->setRightNode(iter->getRightNode());
				}
				Tree<T>::swaps++;
				break;
			}
			else {//both children up
				stringNode<T> minPrev;//previous node to minN
				stringNode<T> minN = min(iter->getRightNode(), minPrev);//minimum of right subtree
				Tree<T>::checks+=2;
				if(iter->getRightNode() == minN) {
					minN->setLeftNode(iter->getLeftNode());
					Tree<T>::swaps++;
				}
				else {//harder case: have to translate right child left node to minimum right node
					minPrev->setLeftNode(minN->getRightNode());
					minN->setLeftNode(iter->getLeftNode());
					minN->setRightNode(iter->getRightNode()); 
					Tree<T>::swaps+=3;
				}
				Tree<T>::checks++;
				if (iter == top) {
					top = minN;
					Tree<T>::swaps++;
				}
				else {
					Tree<T>::checks++;
					if (*iter < *prev) {
						prev->setLeftNode(minN);
					}
					else {
						prev->setRightNode(minN);
					}
				}

				delete iter;
				break;
			}
		}
		else if (*iter > str) {
			Tree<T>::checks++;
			prev = iter;
			iter = iter->getLeftNode();
		}
		else {
			prev = iter;
			Tree<T>::checks++;
			iter = iter->getRightNode();
		}
	}
}

template <typename T>
bool BST<T>::search(T str)
{
	Tree<T>::search(str);

	stringNode<T> iter = top;
	while (iter != nullptr) {
		Tree<T>::checks+=2;
		if (*iter == str) {
			return true;
		}
		Tree<T>::checks++;
		if (*iter > str) {
			iter = iter->getLeftNode();
		}
		else {
			iter = iter->getRightNode();
		}
	}
	return false;
}

template <typename T>
void BST<T>::inOrder()
{
	Tree<T>::inOrder();

	printf("=inOrder= \n");
	Tree<T>::checks++;
	if (top == nullptr) {
		std::cout << "Empty...\n";
		return;
	}
	print(top);
}

template <typename T>
void BST<T>::bfs()
{
	printf("=BFS= \n");
	if (top != nullptr) {
		std::deque<BSTNode<T>> deq;
		deq.push_back(*top);
		BSTNode<T> temp;
		while (!deq.empty()) {
			temp = deq.front();
			std::cout << deq.front().getValue();
			deq.pop_front();
			if (temp.getLeftNode() != nullptr) {
				deq.push_back(*temp.getLeftNode());
				std::cout << "\t<-- \t";
			}
			else {
				std::cout << "\t";
			}
			if (temp.getRightNode() != nullptr) {
				deq.push_back(*temp.getRightNode());
				std::cout << "-->";
			}
			std::cout << std::endl;
		}

	}
	else {
		std::cout << "Empty...\n";
	}

}

template <typename T>
stringNode<T> BST<T>::min(stringNode<T> current, stringNode<T>& prev)
{
	while (current->getLeftNode() != nullptr) {
		Tree<T>::checks++;
		prev = current;
		current = current->getLeftNode();
	}
	return current;
}

template <typename T>
void BST<T>::print(stringNode<T> n)//dfs
{
	if (n != nullptr) {
		//Tree<T>::checks++;
		print(n->getLeftNode());
		std::cout << n->getValue() << std::endl;
		print(n->getRightNode());
	}
}

