#include "Splay.h"
#include <deque>

template class Splay<string>;

template<typename T>
Splay<T>::Splay()
{
	top = nullptr;
}

template<typename T>
Splay<T>::~Splay()
{
}

template<typename T>
void Splay<T>::insert(T val)
{
	Tree<T>::insert(val);

	SplayNode<T>* node = splay(top, val);
	Tree<T>::checks++;
	if (node == nullptr) {//empty tree
		top = new SplayNode<T>(val);
		Tree<T>::swaps++;
	}
	else {
		SplayNode<T>* add = new SplayNode<T>(val);
		add->setParent(node);
		Tree<T>::swaps++;
		Tree<T>::checks++;
		if (*node >= val) {//connect to left subtree
			add->setLeftNode(node->getLeftNode());
			node->setLeftNode(add);
			Tree<T>::swaps+=2;
			Tree<T>::checks++;
			if (add->getLeftNode() != nullptr) {
				add->getLeftNode()->setParent(add);
				Tree<T>::swaps++;
			}
		}
		else {//connect to right subtree
			add->setRightNode(node->getRightNode());
			node->setRightNode(add);
			Tree<T>::swaps+=2;
			Tree<T>::checks++;
			if (add->getRightNode() != nullptr) {
				add->getRightNode()->setParent(add);
				Tree<T>::swaps++;
			}
		}
	}
}

template<typename T>
void Splay<T>::remove(T val)
{
	Tree<T>::remove(val);
	//inOrder();
	Tree<T>::checks++;
	if (top != nullptr) {//empty tree
		splay(top, val);

		if (top->getValue() == val) {//if searched value exists
			if (Tree<T>::size > 0) {
				Tree<T>::size--;
			}

			SplayNode<T>* left = top->getLeftNode();
			SplayNode<T>* right = top->getRightNode();

			delete top;
			top = nullptr;

			Tree<T>::checks++;
			if (left == nullptr) {
				if(right != nullptr)
					right->setParent(nullptr);
				top = right;//right subtree
				Tree<T>::swaps++;
			}
			else {//left tree is not empty 
				top = left;
				top->setParent(nullptr);

				top = splay(top, val);
				while (top->getRightNode() != nullptr) {//we rotate duplicates
					leftRotate(top);
				}

				top->setRightNode(right);//right subtree
				if (right != nullptr) {
					right->setParent(top);
				}
				top->setParent(nullptr);
				Tree<T>::swaps++;
			}
		}
		else {
			std::cout << "didnt find: " << val << std::endl;
		}
	}
}

template<typename T>
bool Splay<T>::search(T val)
{
	Tree<T>::search(val);
	Tree<T>::checks++;
	if (splay(top, val) == nullptr) {
		return false;
	}
	else {
		return true;
	}
}

template<typename T>
std::string Splay<T>::inOrder()
{
	Tree<T>::inOrder();

	//printf("=inOrder= \n");
	Tree<T>::checks++;
	if (top == nullptr) {
		//std::cout << "Empty...\n";
		return "\n";
	}
	std::string buffor = "";
	print(top, buffor);
	return(buffor);
}

template<typename T>
SplayNode<T>* Splay<T>::splay(SplayNode<T>* root, T x)
{
	Tree<T>::checks++;
	if (root == nullptr) {
		return root;
	}

	SplayNode<T>* temp = root;
	SplayNode<T>* prev = nullptr;
	while (temp != nullptr) {
		Tree<T>::checks+=2;
		prev = temp;
		if (*temp == x) {
			break;
		}
		else if (*temp > x) {//go left
			Tree<T>::checks++;
			temp = temp->getLeftNode();
		}
		else {//go right
			Tree<T>::checks++;
			temp = temp->getRightNode();
		}
	}

	Tree<T>::checks++;
	if (temp == nullptr)															 
	{																				 
		temp = prev;//previous node													 
	}
	
	while (true) {											 
		Tree<T>::checks+=2;

		if (temp->getParent() == nullptr) {
			break;
		}

		if (temp->getParent()->getParent() == nullptr) {
			Tree<T>::checks++;
			if (temp->getParent()->getLeftNode() == temp) {
				rightRotate(temp->getParent());
			}																		  
			else {																	  
				leftRotate(temp->getParent());										  
			}
			break;																	  
		}																			  
		Tree<T>::checks+=2;
		if (temp->getParent()->getParent()->getLeftNode() == temp->getParent()//left left
			&& temp->getParent()->getLeftNode() == temp){
			rightRotate(temp->getParent()->getParent());								
			rightRotate(temp->getParent());												
 																			
		}
		else if (temp->getParent()->getParent()->getRightNode() == temp->getParent()//right right
			&& temp->getParent()->getRightNode() == temp){		
			Tree<T>::checks += 2;

			leftRotate(temp->getParent()->getParent());							
			leftRotate(temp->getParent());										
		}
		else if(temp->getParent()->getRightNode() == temp) {//left right	
			Tree<T>::checks++;
			leftRotate(temp->getParent());									
			rightRotate(temp->getParent());									
		}
		else {//right left
			Tree<T>::checks++;
			rightRotate(temp->getParent());										
			leftRotate(temp->getParent());										
		}
		
	}
	return temp;
}

template<typename T>
void Splay<T>::leftRotate(SplayNode<T>* x)				//     x		     y
{														//   a   y    ->   x   c
	SplayNode<T>* y = x->getRightNode();				//		b  c      a  b
	x->setRightNode(y->getLeftNode());//b switch		
	Tree<T>::swaps++;
	Tree<T>::checks++;
	if (!(y->getLeftNode() == nullptr)) {
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
	Tree<T>::swaps+=2;
	y->setLeftNode(x);// x left subtree
	x->setParent(y);// parent y
}

template<typename T>
void Splay<T>::rightRotate(SplayNode<T>* y)				//	   y		   x	
{														//   x   c    -> a   y   
	SplayNode<T>* x = y->getLeftNode();					//  a  b	       b   c 
	y->setLeftNode(x->getRightNode());//b switch					
	Tree<T>::swaps++;
	Tree<T>::checks++;
	if (!(x->getRightNode() == nullptr)) {
		x->getRightNode()->setParent(y);// b parent			
		Tree<T>::swaps++;
	}
	x->setParent(y->getParent());// parent switch
	Tree<T>::swaps++;
	Tree<T>::checks++;
	if (y->getParent() == nullptr) {
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
	Tree<T>::swaps+=2;
	x->setRightNode(y);// y right subtree
	y->setParent(x);// parent x
}

template<typename T>
void Splay<T>::print(SplayNode<T>* n, std::string& buffor)//dfs
{
	if (n!=nullptr) {
		//Tree<T>::checks++;
		print(n->getLeftNode(),buffor);
		buffor += n->getValue() + " ";
		//std::cout << n->getValue() << std::endl;
		print(n->getRightNode(), buffor);
	}
}

template<typename T>
void Splay<T>::bfs()
{
	printf("=BFS= \n");
	if (top != nullptr) {
		std::deque<SplayNode<T>> deq;
		deq.push_back(*top);
		SplayNode<T> temp;
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

//void TemporaryFunction()
//{
//	Splay<int> TempObj;
//}