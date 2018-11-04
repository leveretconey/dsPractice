#pragma once
#include "Arraylist.h"
class Heap
{
	//´ó¸ù¶Ñ
public:
	static const int MAX_SIZE = 9999;
	int CreateFromArrayList(ArrayList *al);
	int Delete(int node);
	int Insert(int data);
	int GetAndDeleteRoot();
	int IsEmpty();
	int ShowAll();
	int GetLength();

	Heap();
	~Heap();
protected:
	int data[MAX_SIZE];
	int length;

	void AdjustDown(int node);
	void AdjustUp(int node);
};

