#include "RB.h"
#include <iostream>
#include <deque>

RB::RB()
{
	top = new RBNode<string>();
	top->setSentinel(true);
}

void RB::insert(string str)
{
	node y = nullptr;

	node x = top;
	while (!(x->isSentinel())) {
		y = x;
		if (*x > str) {
			x = x->left;
		}
		else {
			x = x->right;
		}
	}
	node z = new RBNode<string>(str);
	z->parent = y;
	if (y == nullptr) {
		top = z;
	}
	else if (*y > str) {
		y->left = z;
	}
	else {
		y->right = z;
	}
	node leftSentinel = new RBNode<string>();
	leftSentinel->setSentinel(true);
	node rightSentinel = new RBNode<string>();
	rightSentinel->setSentinel(true);
	z->left = leftSentinel;
	z->right = rightSentinel;

	insertFix(z);

}

void RB::remove(string str)
{
	node z = get(str);
	if (z == nullptr) {
		return;
	}

	node y = z;
	node x;
	COLOR og = y->getColor();
	if (z->left->isSentinel()) {
		x = z->right;
		transplant(z, z->right);
		delete z->left;
	}
	else if (z->right->isSentinel()) {
		x = z->left;
		transplant(z, z->left);
		delete z->right;
	}
	else {
		y = min(z->right);					//   z
		og = y->getColor();					//     .
		x = y->right;						//   y  
		if (y->parent == z) {               //     x
			x->parent = y;
		}
		else {
			transplant(y, y->right);
			y->right = z->right;
			y->right->parent = y;
		}
		transplant(z, y);
		delete y->left;//delete left sentinel
		y->left = z->left;
		y->left->parent = y;
		y->setColor(z->getColor());
	}
	if (og == BLACK) {//if og was read tree will be balanced
		deleteFix(x);
	}
	delete z;
}

void RB::search(string str)
{
	node iter = top;
	while (!iter->isSentinel()) {
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

void RB::inOrder()
{
	printf("\n =inOrder= \n");
	print(top);
}

void RB::bfs()
{
	printf("\n =BFS= \n");
	if (!top->isSentinel()) {
		std::deque<RBNode<string>> deq;
		deq.push_back(*top);
		RBNode<string> temp;
		while (!deq.empty()) {
			temp = deq.front();
			std::cout << deq.front();
			deq.pop_front();
			if (!temp.left->isSentinel()) {
				deq.push_back(*temp.left);
				std::cout << "\t<-- \t";
			}
			else {
				std::cout << "\t";
			}
			if (!temp.right->isSentinel()) {
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

node RB::get(string str)
{
	node iter = top;
	while (!iter->isSentinel()) {
		if (*iter == str) {
			return iter;
		}
		if (*iter > str) {
			iter = iter->left;
		}
		else {
			iter = iter->right;
		}
	}
	return nullptr;
}

void RB::insertFix(node z)
{
	node y;

	while (z->parent != nullptr && z->parent->getColor() == RED) {

		if (z->parent == z->parent->parent->left) {// left subtree
			y = z->parent->parent->right;
			if (!y->isSentinel() && y->getColor() == RED) {// red aunt
				z->parent->setColor(BLACK);
				y->setColor(BLACK);
				z->parent->parent->setColor(RED);
				z = z->parent->parent;
			}
			else {// black aunt
				if (z == z->parent->right) {
					z = z->parent;
					leftRotate(z);
				}
				z->parent->setColor(BLACK);
				z->parent->parent->setColor(RED);
				rightRotate(z->parent->parent);
			}
		}
		else {// right subtree
			y = z->parent->parent->left;
			if (!y->isSentinel() && y->getColor() == RED) {// red aunt
				z->parent->setColor(BLACK);
				y->setColor(BLACK);
				z->parent->parent->setColor(RED);
				z = z->parent->parent;
			}
			else {// black aunt
				if (z == z->parent->left) {
					z = z->parent;
					rightRotate(z);
				}
				z->parent->setColor(BLACK);
				z->parent->parent->setColor(RED);
				leftRotate(z->parent->parent);
			}
		}
	}
	top->setColor(BLACK);
}

void RB::deleteFix(node x)
{
	//printf("\nmiddlebfs\n");
	//bfs();
	node w;
	while (x != top && x->getColor() == BLACK) {
		if (x == x->parent->left) {//left subtree
			w = x->parent->right;
			if (w->getColor() == RED) {//case1
				w->setColor(BLACK);
				x->parent->setColor(RED);
				leftRotate(x->parent); 
				w = x->parent->right;
			}
			if (w->getLeftColor() == BLACK && w->getRightColor() == BLACK) {//case2
				w->setColor(RED);
				x = x->parent;
			}
			else {
				if (w->getRightColor() == BLACK) {//change case 3 to case 4
					w->left->setColor(BLACK);
					w->setColor(RED);
					rightRotate(w);
					w = x->parent->right;
				}
				w->setColor(x->parent->getColor());//case4
				x->parent->setColor(BLACK);
				w->right->setColor(BLACK);
				leftRotate(x->parent);
				break;//always fine here
			}
		}
		else {//right subtree
			w = x->parent->left;
			if (w->getColor() == RED) {//case1
				w->setColor(BLACK);
				x->parent->setColor(RED);
				rightRotate(x->parent);
				w = x->parent->left;
			}
			if (w->getLeftColor() == BLACK && w->getRightColor() == BLACK) {//case2
				w->setColor(RED);
				x = x->parent;
			}
			else {
				if (w->getLeftColor() == BLACK) {//change case 3 to case 4
					w->right->setColor(BLACK);
					w->setColor(RED);
					leftRotate(w);
					w = x->parent->left;
				}
				w->setColor(x->parent->getColor());//case4
				x->parent->setColor(BLACK);
				w->left->setColor(BLACK);
				rightRotate(x->parent);
				break;//always fine here
			}
		}
	}
	x->setColor(BLACK);
}

void RB::transplant(node x, node y)
{
	if (x->parent == nullptr) {//top
		top = y;
		return;
	}
	else if (x == x->parent->left) {
		x->parent->left = y;
	}
	else {
		x->parent->right = y;
	}

	//if(y != nullptr)	
	y->parent = x->parent;
}

node RB::min(node current)
{
	while (!current->left->isSentinel()) {
		current = current->left;
	}
	return current;
}

void RB::leftRotate(node x)					//     x		     y
{											//   a   y    ->   x   c
	node y = x->right;						//		b  c      a  b
	x->right = y->left;//b switch					
	if (!y->left->isSentinel()) {
		y->left->parent = x;// b parent			
	}
	y->parent = x->parent;// parent switch
	if (x->parent == nullptr) {
		top = y;//tree root
	}
	else if (x == x->parent->left) {
		x->parent->left = y;//switch left parent node
	}
	else {
		x->parent->right = y;//switch right parent node
	}
	y->left = x;// x left subtree
	x->parent = y;// parent y
}

void RB::rightRotate(node y)				//	   y		   x	
{											//   x   c    -> a   y   
	node x = y->left;						//  a  b	       b   c 
	y->left = x->right;//b switch					
	if (!x->right->isSentinel()) {
		x->right->parent = y;// b parent			
	}
	x->parent = y->parent;// parent switch
	if (y->parent == nullptr) {
		top = y;//tree root
	}
	else if (y == y->parent->left) {
		y->parent->left = x;//switch left parent node
	}
	else {
		y->parent->right = x;//switch right parent node
	}
	x->right = y;// y right subtree
	y->parent = x;// parent x
}

void RB::print(node n)//dfs
{
	if (!n->isSentinel()) {
		print(n->left);
		std::cout << *n << std::endl;
		print(n->right);
	}
}
