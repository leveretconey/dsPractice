#pragma once
class QueueLink
{
public:
	int IsEmpty();
	void ShowData();
	void EnQueue(int data);
	int DeQueue();
	int Top();
	int Count();


	void ReverseQueueUsingStack();
	QueueLink();
	~QueueLink();
protected:
	struct LinkNode
	{
		int data;
		LinkNode *next;
	};
	typedef LinkNode *LinkNodeP;

	LinkNodeP head,tail;
};

