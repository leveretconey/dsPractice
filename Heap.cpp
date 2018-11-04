#include "Heap.h"
#include "iostream"
using namespace std;


int Heap::CreateFromArrayList(ArrayList * al)
{
	int i;
	length = al->GetLength();
	for(i= 0; i < length; i++)
		data[i+1] = al->GetElement(i);
	for (i = length / 2; i >= 1; i--)
		AdjustDown(i);
	return 0;
}

int Heap::Delete(int node)
{
	if (node<=0 || node >length)
		return 1;
	else
	{
		swap(data[length], data[node]);
		length--;
		AdjustDown(node);
		return 0;
	}
}

int Heap::Insert(int element)
{
	if (length == MAX_SIZE - 1)
		return 1;
	length++;
	data[length] = element;
	AdjustUp(length);
	return 0;
}

int Heap::GetAndDeleteRoot()
{
	if (IsEmpty())
		return -1;
	int root = data[1];
	Delete(1);
	return root;
}

int Heap::IsEmpty()
{
	return length == 0;
}

int Heap::ShowAll()
{
	if (IsEmpty())
		cout << "±íÎª¿Õ";
	else
	{
		for (int i = 1; i <= length; i++)
			cout << data[i] << " ";
		cout << endl;
	}
	return 0;
}

int Heap::GetLength()
{
	return length;
}

Heap::Heap()
{
	length = 0;
}


Heap::~Heap()
{
}

void Heap::AdjustDown(int node)
{
	int current = node, son = current*2;
	int temp = data[current];
	while (son<=length)
	{
		if (son + 1 <= length && data[son + 1] >= data[son])
			son++;
		if (data[son] <= temp)
			break;
		data[current] = data[son];
		current = son;
		son = current * 2;
	}
	data[current] = temp;
}

void Heap::AdjustUp(int node)
{
	int current = node, parent = current / 2;
	int temp = data[current];
	while (!(current == 1|| temp <= data[parent]))
	{
		data[current] = data[parent];
		current = parent;
		parent = current / 2;
	}
	data[current] = temp;
}
