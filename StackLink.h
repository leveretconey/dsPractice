#pragma once

class StackLink
{
public:
	int IsEmpty();
	void ShowData();
	void Push(int data);
	int Pop();
	int Top();
	int Count();

	StackLink();
	~StackLink();
protected:
	struct LinkNode
	{
		int data;
		LinkNode *next;
	};
	typedef LinkNode *LinkNodeP;

	LinkNodeP head;
};

