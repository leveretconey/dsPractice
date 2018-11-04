#include "QueueLink.h"
#include "StackLink.h"
#include <iostream>
using namespace std;

int QueueLink::IsEmpty()
{
	return head->data == 0;
}

void QueueLink::ShowData()
{
	if (IsEmpty())
		cout << "╤сап©у";
	else
	{
		LinkNodeP p = head;
		while (p->next)
		{
			p = p->next;
			cout << p->data << " ";
		}
	}
	cout << endl;
}

void QueueLink::EnQueue(int data)
{
	LinkNodeP p = new LinkNode;
	p->data = data;
	tail->next = p;
	p->next = NULL;
	tail = p;
	head->data++;
}

int QueueLink::DeQueue()
{
	if (IsEmpty())
		return 0;
	else
	{
		head->data--;
		LinkNodeP p = head->next, temp = p->next;
		int result = p->data;
		if (p == tail)
			tail = head;
		delete p;
		head->next = temp;
		return result;
	}
}

int QueueLink::Top()
{
	if (IsEmpty())
		return 0;
	else
	{
		return head->next->data;
	}
}

int QueueLink::Count()
{
	return head->data;
}

void QueueLink::ReverseQueueUsingStack()
{
	StackLink s1, s2;
	while (!IsEmpty())
		s1.Push(DeQueue());
	s1.ShowData();
	/*while (!s1.IsEmpty())
		s2.Push(s1.Pop());*/
	while (!s1.IsEmpty())
		EnQueue(s1.Pop());
}

QueueLink::QueueLink()
{
	head = new LinkNode;
	head->data = 0;
	head->next = NULL;
	tail = head;
}


QueueLink::~QueueLink()
{
	LinkNodeP p = head, temp;
	while (p != NULL)
	{
		temp = p->next;
		delete p;
		p = temp;
	}
}

