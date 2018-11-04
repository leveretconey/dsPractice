//by leveretconey, JBMonster
#include <iostream>
#include "All.h"
using namespace std;

int main()
{
	BiTreeV2 *bt = new BiTreeV2;
	bt->CreateFromString("1234567+8");
	bt->ShowAllData(BiTreeV2::POST_ORDER);

	while (1);
	return 0;
}