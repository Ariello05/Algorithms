#include <iostream>

#include "BST.h"
#include "RB.h"

int main()
{
	std::cout << "What is love?\n" << std::endl;
	//RB t;
	//t.insert("AAA");
	//t.insert("BBB");
	//t.insert("111");
	//t.insert("DDD");
	//t.insert("CCC");
	//t.insert("XXX");
	//t.insert("YYY");
	//t.insert("OOO");
	//t.insert("OOO");
	//t.bfs();
	//printf("----");
	//t.remove("BBB");
	//t.bfs();
	
	RB t;
	t.insert("AAA");
	t.insert("CCC");
	t.insert("BBB");
	t.insert("DDD");
	t.insert("EEE");
	t.insert("FFF");
	t.insert("III");
	t.insert("GGG");
	t.insert("JJJ");
	t.insert("HHH");
	t.insert("ZZZ");
	t.insert("LLL");
	t.insert("KKK");
	t.insert("QQQ");
	t.insert("YYY");
	t.insert("XXX");
	t.insert("VVV");
	t.insert("MMM");
	t.insert("NNN");
	t.insert("OOO");

	std::cout << "--\n";
	t.bfs();
	std::cout << "--\n";

	
	t.remove("VVV");
	t.remove("AAA");
	t.remove("GGG");
	t.remove("ZZZ");
	t.remove("VVV");
	t.remove("MMM");
	t.remove("AAA");
	t.remove("VVV");
	t.remove("JJJ");
	t.remove("QQQ");
	t.remove("LLL");
	t.remove("NNN");
	t.remove("OOO");
	t.remove("DDD");
	t.bfs();
	//t.inOrder();
	////RB rb;
	////rb.insert("AA");

}