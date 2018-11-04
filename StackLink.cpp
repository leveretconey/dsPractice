#include "StackLink.h"
#include <iostream>
using namespace std;

int StackLink::IsEmpty()
{
	return head->data == 0;
}

void StackLink::ShowData()
{
	if (IsEmpty())
		cout << "Õ»¿Õ";
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

void StackLink::Push(int data)
{
	LinkNodeP p = new LinkNode, temp=head->next;
	p->data = data;
	head->next = p;
	p->next = temp;
	head->data++;
}

int StackLink::Pop()
{
	if (IsEmpty())
		return 0;
	else
	{
		head->data--;
		LinkNodeP p = head->next,temp=p->next;
		int result = p->data;
		delete p;
		head->next = temp;
		return result;
	}
}

int StackLink::Top()
{
	if (IsEmpty())
		return 0;
	else
	{
		return head->next->data;
	}
}

int StackLink::Count()
{
	return head->data;
}

StackLink::StackLink()
{
	head = new LinkNode;
	head->data = 0;
	head->next = NULL;
}


StackLink::~StackLink()
{
	LinkNodeP p = head,temp;
	while (p != NULL)
	{
		temp = p->next;
		delete p;
		p = temp;
	}
}
