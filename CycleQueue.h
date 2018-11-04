#pragma once
class CycleQueue
{
	//ѭ�����У�����ʹ������һ��Ԫ�صķ�����������Ϳ�
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
	int front, rear;//front����һ�������е�λ�ã�rear����һ��������λ��
};

