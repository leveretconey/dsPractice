#include "BiTreeV2.h"
#include "ListAll.h"
#include <iostream>
using namespace std;

void BiTreeV2::CreateFromArray(int *a, int length)
{
		BiTreeNodePointer pointers[MAX_NODE];
		int i;
		int parent;
		if (length <= 0 || length>MAX_NODE || a[0] == NULL_NODE)
		{
			root = NULL;
			return;
		}
		root = new BiTreeNode;
		root->data = a[0];
		root->lchild = NULL;
		root->rchild = NULL;
		pointers[0] = root;
		for (i = 1; i < length; i++)
		{
			parent = (i + 1) / 2 - 1;
			if (a[i] != NULL_NODE && pointers[parent] != NULL)
			{//建立一个新的节点
				pointers[i] = new BiTreeNode;
				pointers[i]->data = a[i];
				pointers[i]->lchild = NULL;
				pointers[i]->rchild = NULL;
				if (i % 2 == 1)
					pointers[parent]->lchild = pointers[i];
				else
					pointers[parent]->rchild = pointers[i];
			}
			else
				pointers[i] = NULL;
		}
}

void BiTreeV2::CreateFromString(char *nodes_value)
{
	int data[MAX_NODE],length=0;
	while (*nodes_value != '\0')
	{
		if (*nodes_value >= '0'&& *nodes_value <= '9')
			data[length++] = *nodes_value-'0';
		else if (*nodes_value >= 'a'&& *nodes_value <= 'z')
			data[length++] = *nodes_value-'a';
		else
			data[length++] = NULL_NODE;
		nodes_value++;
	}
	CreateFromArray(data, length);
}

void BiTreeV2::ShowAllData(int order)
{
	if (GetRoot() == NULL)
		cout << "空树！";
	else
	{
		switch (order)
		{
		case PRE_ORDER:
			ShowDataPreOrder();
			break;
		case IN_ORDER:
			ShowDataInOrder();
		case POST_ORDER:
			ShowDataPostOrder();
			break;
		case LEVEL_ORDER:
			ShowDataLevelOrder();
			break;
		default:
			cout << "参数错误";
		}
	}
	cout << endl;
}

BiTreeV2::BiTreeV2()
{
	root = NULL;
}


BiTreeV2::~BiTreeV2()
{
	DestroyTreeRecursion(GetRoot());
}

BiTreeNodePointer BiTreeV2::GetRoot()
{
	return root;
}

void BiTreeV2::DestroyTreeRecursion(BiTreeNodePointer bnp)
{
	if (bnp)
	{
		DestroyTreeRecursion(bnp->lchild);
		DestroyTreeRecursion(bnp->rchild);
		delete bnp;
	}
}

void BiTreeV2::ShowDataPreOrder()
{
	int top = 0;
	BiTreeNodePointer s[MAX_NODE], p=GetRoot();
	while (!(top == 0 && p == NULL))
	{
		if (p)
		{
			s[top++] = p;
			cout << p->data << " ";
			p = p->lchild;
		}
		else 
		{
			p = s[--top];
			p = p->rchild;
		}
	}
}

void BiTreeV2::ShowDataInOrder()
{
	int top = 0;
	BiTreeNodePointer s[MAX_NODE], p = GetRoot();
	while (!(top == 0 && p == NULL))
	{
		if (p)
		{
			s[top++] = p;
			p = p->lchild;
		}
		else
		{
			p = s[--top];
			cout << p->data << " ";
			p = p->rchild;
		}
	}
}

void BiTreeV2::ShowDataPostOrder()
{
	int top = 0;
	BiTreeNodePointer p=GetRoot(), s[MAX_NODE], last_visited=NULL;
	while (!(top == 0 && p == NULL))
	{
		if (p)
		{
			s[top++] = p;
			p = p->lchild;
		}
		else
		{
			p = s[top-1];
			if (p->rchild &&p->rchild != last_visited)
			{
				p = p->rchild;
			}
			else
			{
				cout << p->data << " ";
				last_visited = p;
				top--;
				p = NULL;
			}
		}
	}
}

void BiTreeV2::ShowDataLevelOrder()
{
	int rear = 0, front = 0;
	BiTreeNodePointer q[MAX_NODE], p;
	q[rear++] = GetRoot();
	while (rear != front)
	{
		p = q[front++];
		cout << p->data << " ";
		if (p->lchild)
			q[rear++] = p->lchild;
		if (p->rchild)
			q[rear++] = p->rchild;
	}
}
