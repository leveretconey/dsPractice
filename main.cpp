//by leveretconey, JBMonster
#include <iostream>
#include "All.h"
using namespace std;

int main()
{
	int a = 0x12345678;
	char *p = (char *)&a;
	for (int i = 0; i < 4; i++) {
		cout << (int *)(p + i) << "  " << (int)*(p + i) << endl;
	}

	while (1);
	return 0;
}