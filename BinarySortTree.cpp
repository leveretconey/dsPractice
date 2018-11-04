#include "BinarySortTree.h"
#include <iostream>


BinarySortTree::BinarySortTree()
{
}


BinarySortTree::~BinarySortTree()
{
}

int BinarySortTree::IsLegalBST()
{
	BiTreeNodePointer s[MAX_NODE], p = GetRoot(),pre=NULL;//由于是public继承，基类中是private，因此不能直接访问root
	int top = 0;
	while (!(p == NULL && top == 0))
	{ 
		if (p == NULL)
		{
			p = s[--top];
			if (pre != NULL)
			{
				if (p->data < pre->data)
					return false;
			}
			pre = p;
			p = p->rchild;
		}
		else
		{
			s[top++] = p;
			p = p->lchild;
		}
	}
	return true;
}

BiTreeNodePointer BinarySortTree::SearchNodeWithValue(int value)
{
	BiTreeNodePointer p = GetRoot();
	while (p != NULL)
	{
		if (p->data == value)
			break;
		else if (p->data < value)
			p = p->rchild;
		else
			p = p->lchild;
	}
	return p;
}

BiTreeNodePointer BinarySortTree::InsertNodeWithValue(int value)
{
	BiTreeNodePointer p = GetRoot();
	if (p == NULL)
	{
		int a[1];
		a[0] = value;
		CreateFromArray(a, 1);
		return GetRoot();
	}
	while (1)
	{
		if (p->data == value)
			return p;
		else if (p->data > value)
			if(p->lchild!=NULL)
			    p = p->lchild;
			else
			{
				p->lchild = CreateNewNode(value);
				return p->lchild;
			}
		else
			if (p->rchild != NULL)
				p = p->rchild;
			else
			{
				p->rchild = CreateNewNode(value);
				return p->rchild;
			}
	}
	return NULL;
}

int BinarySortTree::CreateBSTreeFromString(char *nodes_data)
{
	int data_array[MAX_NODE];
	int length;
	StringToArray(nodes_data, data_array, length);
	int i;
	for (i = 0; i < length; i++)
		InsertNodeWithValue(data_array[i]);
	return 0;
}

int BinarySortTree::DeleteBSTreeNodeWithValue(int value)
{
	BiTreeNodePointer node_to_delete, node_to_delete_parent,node_victim;
	node_to_delete = SearchNodeWithValue(value);
	for (;;)
	{
		switch (CountOfChildren(node_to_delete))
		{
		    case 0:
				node_to_delete_parent = GetParent(node_to_delete);
				BreakLink(node_to_delete_parent, node_to_delete);
				delete node_to_delete;
				return 0;
				break;
			case 1:
				node_to_delete_parent = node_to_delete;
				if (node_to_delete->lchild != NULL)
					node_to_delete = node_to_delete -> lchild;
				else
					node_to_delete = node_to_delete->rchild;
				node_to_delete_parent->data = node_to_delete->data;
				BreakLink(node_to_delete_parent, node_to_delete);
				delete node_to_delete;
				return 0;
				break;
			case 2:
				//search victim
				node_victim = node_to_delete->rchild;
				while (node_victim->lchild != NULL)
					node_victim = node_victim->lchild;

				node_to_delete->data = node_victim->data;
				node_to_delete = node_victim;
				break;
			default:
				return 1;
		}
	}
}

BiTreeNodePointer BinarySortTree::GetParent(BiTreeNodePointer child)
{
	int child_data = child->data;
	BiTreeNodePointer p = GetRoot();
	if (p == child)
		return NULL;
	while (p != NULL)
	{
		if ((p->lchild != NULL&&p->lchild->data == child_data)\
		|| (p->rchild != NULL&&p->rchild->data == child_data))
			return p;
		if (p->data < child_data)
			p = p->rchild;
		else
			p = p->lchild;
	}
	return NULL;
}