#include "CycleQueue.h"
#include <iostream>

CycleQueue::CycleQueue()
{
	rear = 0;
	front = 0;
}


CycleQueue::~CycleQueue()
{
}

int CycleQueue::IsEmpty()
{
	return rear == front;
}

int CycleQueue::IsFull()
{
	return (rear + 1) % MAX_QUEUE_LENGTH == front;
}
int CycleQueue::EnQueue(int x)
{
	if (IsFull())
		return false;
	else
	{
	data[rear] = x;
	rear = (rear + 1) % MAX_QUEUE_LENGTH;
	return true;
    }
}

void CycleQueue::Initialize()
{
	rear = 0;
	front = 0;
}

int CycleQueue::DeQueue(int &x)
{
	if (IsEmpty())
		return false;
	else
	{
		x = data[front];
		front = (front + 1) % MAX_QUEUE_LENGTH;
		return true;
	}
}


void CycleQueue::ShowData()
{
	if (IsEmpty())
		std::cout << "此队列为空";
	else
	{
		int i=front;
		while (i%MAX_QUEUE_LENGTH != rear)
		{
			std::cout << data[i%MAX_QUEUE_LENGTH] << " ";
			i++;
		}
		if (IsFull()) std::cout << "队列已满";
	}
	std::cout << std::endl;
}