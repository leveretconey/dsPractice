//by leveretconey, JBMonster
#include <iostream>
#include "All.h"
#include <vector>
#include <random>
using namespace std;
using namespace leveretconey;

int main()
{
	
	/*
	tree.createFromFile("input.txt");
	
	vector<int> v(11);
	for(int i = 0; i < 11; i++) {
		v[i] = i+1;
	}
	shuffle(v.begin(), v.end(), default_random_engine(3));
	
	//vector<int> v({4});
	for (int i : v) {
		cout << "delete " << i << " :";
		tree.del(i);
		tree.show();
	}
	*/
	Timer timer;
	for (int i = 1; i <= 10000; i++) {
		RBTree tree;
		vector<int> v;
		for (int i = 0; i < 100; i++) {
			v.push_back(i + 1);
		}
		shuffle(v.begin(), v.end(), default_random_engine(i));
		for (int i : v) {
			tree.insert(i);
		}
		//tree.show();
		shuffle(v.begin(), v.end(), default_random_engine(11));
		for (int i : v) {
			//cout << "del " << i << " :";
			tree.del(i);
			//tree.show();
			if (!tree.isValid())
			{
				cout << "break! "<<i;
				break;
			}
		}
	}
	timer.ShowTime();
	return 0;
}