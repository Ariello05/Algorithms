#include "RB.h"
#include <iostream>
#include <deque>
template class RB<string>;

template<typename T>
RB<T>::RB()
{
	top = new RBNode<T>();
	top->setSentinel(true);
}

template<typename T>
void RB<T>::insert(T str)
{
	Tree<T>::insert(str);

	RBNode<T>* y = nullptr;

	RBNode<T>* x = top;
	while (!(x->isSentinel())) {
		y = x;
		Tree<T>::checks+=2;//while + if
		if (*x > str) {
			x = x->getLeftNode();
		}
		else {
			x = x->getRightNode();
		}
	}
	RBNode<T>* z = new RBNode<T>(str);
	z->setParent(y);
	Tree<T>::checks++;
	if (y == nullptr) {
		top = z;
		Tree<T>::swaps++;
	}
	else if (*y > str) {
		Tree<T>::checks++;
		y->setLeftNode(z);
		Tree<T>::swaps++;
	}
	else {
		Tree<T>::checks++;
		y->setRightNode(z);
		Tree<T>::swaps++;
	}
	RBNode<T>* leftSentinel = new RBNode<T>();
	leftSentinel->setSentinel(true);
	RBNode<T>* rightSentinel = new RBNode<T>();
	rightSentinel->setSentinel(true);
	z->setLeftNode(leftSentinel);
	z->setRightNode(rightSentinel);
	Tree<T>::swaps += 4;

	insertFix(z);
}

template<typename T>
void RB<T>::remove(T str)
{
	Tree<T>::remove(str);

	RBNode<T>* z = get(str);
	Tree<T>::checks++;
	if (z == nullptr) {
		return;
	}

	if (Tree<T>::size > 0) {
		Tree<T>::size--;
	}

	RBNode<T>* y = z;
	RBNode<T>* x;
	COLOR og = y->getColor();

	if (z->getLeftNode()->isSentinel()) {
		Tree<T>::checks++;
		x = z->getRightNode();
		transplant(z, z->getRightNode());
		delete z->getLeftNode();
	}
	else if (z->getRightNode()->isSentinel()) {
		Tree<T>::checks++;
		x = z->getLeftNode();
		transplant(z, z->getLeftNode());
		delete z->getRightNode();
	}
	else {
		Tree<T>::checks++;
		y = min(z->getRightNode());					//   z
		og = y->getColor();					//     .
		x = y->getRightNode();						//   y  
		Tree<T>::checks++;
		if (y->getParent()== z) {               //     x
			x->setParent(y);
			Tree<T>::swaps++;
		}
		else {
			transplant(y, y->getRightNode());
			y->setRightNode(z->getRightNode());
			Tree<T>::swaps+=2;
			y->getRightNode()->setParent(y);
		}
		transplant(z, y);
		delete y->getLeftNode();//delete left sentinel
		y->setLeftNode(z->getLeftNode());
		Tree<T>::swaps+=3;//++color
		y->getLeftNode()->setParent(y);
		y->setColor(z->getColor());
	}
	if (og == BLACK) {//if og was read tree will be balanced
		Tree<T>::checks++;
		deleteFix(x);
	}
	delete z;
}

template<typename T>
bool RB<T>::search(T str)
{
	Tree<T>::search(str);

	RBNode<T>* iter = top;
	while (!iter->isSentinel()) {
		Tree<T>::checks += 2;
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

template<typename T>
void RB<T>::inOrder()
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

template<typename T>
void RB<T>::bfs()
{
	printf("=BFS= \n");
	if (top != nullptr && !top->isSentinel()) {
		std::deque<RBNode<T>> deq;
		deq.push_back(*top);
		RBNode<T> temp;
		while (!deq.empty()) {
			temp = deq.front();
			std::cout << deq.front();
			deq.pop_front();
			if (!temp.getLeftNode()->isSentinel()) {
				deq.push_back(*temp.getLeftNode());
				std::cout << "\t<-- \t";
			}
			else {
				std::cout << "\t";
			}
			if (!temp.getRightNode()->isSentinel()) {
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

template<typename T>
node<T> RB<T>::get(T str)
{
	RBNode<T>* iter = top;
	while (!iter->isSentinel()) {
		Tree<T>::checks+=2;
		if (*iter == str) {
			return iter;
		}
		Tree<T>::checks++;
		if (*iter > str) {
			iter = iter->getLeftNode();
		}
		else {
			iter = iter->getRightNode();
		}
	}
	return nullptr;
}

template<typename T>
void RB<T>::insertFix(node<T> z)
{
	RBNode<T>* y;

	while (z->getParent() != nullptr && z->getParent()->getColor() == RED) {
		Tree<T>::checks+=3;//while + below if

		if (z->getParent() == z->getParent()->getParent()->getLeftNode()) {// left subtree
			Tree<T>::checks+=2;//below if
			y = z->getParent()->getParent()->getRightNode();

			if (!y->isSentinel() && y->getColor() == RED) {// red aunt
				Tree<T>::swaps+=3;
				z->getParent()->setColor(BLACK);
				y->setColor(BLACK);
				z->getParent()->getParent()->setColor(RED);
				z = z->getParent()->getParent();
			}
			else {// black aunt
				if (z == z->getParent()->getRightNode()) {
					Tree<T>::checks++;
					z = z->getParent();
					leftRotate(z);
				}
				Tree<T>::swaps+=2;
				z->getParent()->setColor(BLACK);
				z->getParent()->getParent()->setColor(RED);
				rightRotate(z->getParent()->getParent());
			}
		}
		else {// right subtree
			Tree<T>::checks+=2;//below if
			y = z->getParent()->getParent()->getLeftNode();

			if (!y->isSentinel() && y->getColor() == RED) {// red aunt
				Tree<T>::swaps += 3;
				z->getParent()->setColor(BLACK);
				y->setColor(BLACK);
				z->getParent()->getParent()->setColor(RED);
				z = z->getParent()->getParent();
			}
			else {// black aunt
				if (z == z->getParent()->getLeftNode()) {
					Tree<T>::checks++;
					z = z->getParent();
					rightRotate(z);
				}
				Tree<T>::swaps += 2;
				z->getParent()->setColor(BLACK);
				z->getParent()->getParent()->setColor(RED);
				leftRotate(z->getParent()->getParent());
			}
		}
	}
	Tree<T>::swaps++;
	top->setColor(BLACK);
}

template<typename T>
void RB<T>::deleteFix(node<T> x)
{
	//printf("\nmiddlebfs\n");
	//bfs();
	RBNode<T>* w;
	while (x != top && x->getColor() == BLACK) {
		Tree<T>::checks+=3;//while+if

		if (x == x->getParent()->getLeftNode()) {//left subtree
			w = x->getParent()->getRightNode();
			Tree<T>::checks++;//color below
			if (w->getColor() == RED) {//case1
				Tree<T>::swaps+=2;//color twice
				w->setColor(BLACK);
				x->getParent()->setColor(RED);
				leftRotate(x->getParent()); 
				w = x->getParent()->getRightNode();
			}
			Tree<T>::checks+=2;
			if (w->getLeftColor() == BLACK && w->getRightColor() == BLACK) {//case2
				Tree<T>::swaps++;
				w->setColor(RED);
				x = x->getParent();
			}
			else {
				Tree<T>::checks++;
				if (w->getRightColor() == BLACK) {//change case 3 to case 4
					Tree<T>::swaps+=2;
					w->getLeftNode()->setColor(BLACK);
					w->setColor(RED);
					rightRotate(w);
					w = x->getParent()->getRightNode();
				}
				Tree<T>::swaps+=3;//3 below
				w->setColor(x->getParent()->getColor());//case4
				x->getParent()->setColor(BLACK);
				w->getRightNode()->setColor(BLACK);
				leftRotate(x->getParent());
				break;//always fine here
			}
		}
		else {//right subtree
			w = x->getParent()->getLeftNode();
			Tree<T>::checks++;
			if (w->getColor() == RED) {//case1
				Tree<T>::swaps+=2;
				w->setColor(BLACK);
				x->getParent()->setColor(RED);
				rightRotate(x->getParent());
				w = x->getParent()->getLeftNode();
			}
			Tree<T>::checks+=2;
			if (w->getLeftColor() == BLACK && w->getRightColor() == BLACK) {//case2
				Tree<T>::swaps++;
				w->setColor(RED);
				x = x->getParent();
			}
			else {
				Tree<T>::checks++;
				if (w->getLeftColor() == BLACK) {//change case 3 to case 4
					Tree<T>::swaps+=2;
					w->getRightNode()->setColor(BLACK);
					w->setColor(RED);
					leftRotate(w);
					w = x->getParent()->getLeftNode();
				}
				Tree<T>::swaps+=3;
				w->setColor(x->getParent()->getColor());//case4
				x->getParent()->setColor(BLACK);
				w->getLeftNode()->setColor(BLACK);
				rightRotate(x->getParent());
				break;//always fine here
			}
		}
	}
	Tree<T>::swaps++;
	x->setColor(BLACK);
}

template<typename T>
void RB<T>::transplant(node<T> x, node<T> y)
{
	Tree<T>::checks++;
	if (x->getParent() == nullptr) {//top
		top = y;
		Tree<T>::swaps++;
	}
	else if (x == x->getParent()->getLeftNode()) {
		Tree<T>::checks++;
		x->getParent()->setLeftNode(y);
		Tree<T>::swaps++;
	}
	else {
		Tree<T>::checks++;
		x->getParent()->setRightNode(y);
		Tree<T>::swaps++;
	}

	//if(y != nullptr)	
	y->setParent(x->getParent());
	Tree<T>::swaps++;
}

template<typename T>
node<T> RB<T>::min(node<T> current)
{
	while (!current->getLeftNode()->isSentinel()) {
		Tree<T>::checks++;
		current = current->getLeftNode();
	}
	return current;
}

template<typename T>
void RB<T>::leftRotate(node<T> x)					//     x		     y
{											//   a   y    ->   x   c
	RBNode<T>* y = x->getRightNode();				//		b  c      a  b
	x->setRightNode(y->getLeftNode());//b switch	
	Tree<T>::swaps++;
	Tree<T>::checks++;
	if (!y->getLeftNode()->isSentinel()) {
		y->getLeftNode()->setParent(x);// b parent		
		Tree<T>::swaps++;
	}
	y->setParent(x->getParent());// parent switch
	Tree<T>::swaps++;
	Tree<T>::checks++;
	if (x->getParent() == nullptr) {
		top = y;//tree root
		Tree<T>::swaps++;
	}
	else if (x == x->getParent()->getLeftNode()) {
		Tree<T>::checks++;
		x->getParent()->setLeftNode(y);//switch left parent node
		Tree<T>::swaps++;
	}
	else {
		Tree<T>::checks++;
		x->getParent()->setRightNode(y);//switch right parent node
		Tree<T>::swaps++;
	}
	y->setLeftNode(x);// x left subtree
	Tree<T>::swaps++;
	x->setParent(y);// parent y
	Tree<T>::swaps++;
}

template<typename T>
void RB<T>::rightRotate(node<T> y)				//	   y		   x	
{											//   x   c    -> a   y   
	RBNode<T>* x = y->getLeftNode();				//  a  b	       b   c 
	y->setLeftNode(x->getRightNode());//b switch	
	Tree<T>::swaps++;
	Tree<T>::checks++;
	if (!x->getRightNode()->isSentinel()) {
		x->getRightNode()->setParent(y);// b parent			
		Tree<T>::swaps++;
	}
	x->setParent(y->getParent());// parent switch
	Tree<T>::swaps++;
	if (y->getParent()  == nullptr) {
		Tree<T>::checks++;
		top = x;//tree root
		Tree<T>::swaps++;
	}
	else if (y == y->getParent()->getLeftNode()) {
		Tree<T>::checks++;
		y->getParent()->setLeftNode(x);//switch left parent node
		Tree<T>::swaps++;
	}
	else {
		Tree<T>::checks++;
		y->getParent()->setRightNode(x);//switch right parent node
		Tree<T>::swaps++;
	}
	x->setRightNode(y);// y right subtree
	Tree<T>::swaps+=2;
	y->setParent(x);// parent x
}

template<typename T>
void RB<T>::print(node<T> n)//dfs
{
	if (!n->isSentinel()) {
		//Tree<T>::checks++;
		print(n->getLeftNode());
		std::cout << n->getValue() << std::endl;
		print(n->getRightNode());
	}
}

