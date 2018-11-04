#pragma once
class CycleQueue
{
	//循环队列，这里使用牺牲一个元素的方法来标记满和空
public:
	static const int MAX_QUEUE_LENGTH = 9999;

	CycleQueue();
	~CycleQueue();

	int IsEmpty();
	int IsFull();
	int DeQueue(int &);
	int EnQueue(int);
	void Initialize();
	void ShowData();

	
private:
	int data[MAX_QUEUE_LENGTH];
	int front, rear;//front是下一个进队列的位置，rear是下一个读出的位置
};

