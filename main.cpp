//by leveretconey, JBMonster
#include <iostream>
#include "All.h"
using namespace std;
using namespace leveretconey;

int main()
{
	RBTree tree;
	tree.createFromFile("input.txt");
	tree.show();

	return 0;
}