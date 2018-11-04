#include "BiTree.h"
#include <iostream>
#include "StackLink.h"

BiTree::BiTree()
{
	root = NULL;
}


BiTree::~BiTree()
{
	PostOrderTraverse(root, &DeleteNode);
}
void BiTree::CreateFromArray(int *a, int length)
{
	BiTreeNodePointer pointers[MAX_NODE];
	int i;
	int parent;
	if (length<=0 || length>MAX_NODE || a[0] == NULL_NODE)
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
		if (a[i] != NULL_NODE && pointers[parent]!=NULL)
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

int BiTree::ShowNodeData(BiTreeNodePointer Node)
{
	if (Node != NULL)
    	std::cout << Node->data <<" ";
	return 0;
}

void BiTree::PreOrderTraverse(BiTreeNodePointer tree, int (*visit)(BiTreeNodePointer))
{
	if (tree != NULL)
	{
		visit(tree);
		PreOrderTraverse(tree->lchild, visit);
		PreOrderTraverse(tree->rchild, visit);
	}
}

void BiTree::ShowAllData(int order)
{
	switch (order)
	{
	case TABLE_FORMAT:
		ShowInTable();
		break;
	default:
		int(*visit)(BiTreeNodePointer) = &(BiTree::ShowNodeData);
		Traverse(root, order, visit);
		break;
	}
	std::cout << std::endl;
}

void BiTree::InOrderTraverse(BiTreeNodePointer tree, int(*visit)(BiTreeNodePointer))
{
	if (tree != NULL)
	{
		InOrderTraverse(tree->lchild, visit);
		visit(tree);
		InOrderTraverse(tree->rchild, visit);
	}
}

void BiTree::PostOrderTraverse(BiTreeNodePointer tree, int(*visit)(BiTreeNodePointer))
{
	if (tree != NULL)
	{
		PostOrderTraverse(tree->lchild, visit);
		PostOrderTraverse(tree->rchild, visit);
		visit(tree);
	}
}

void BiTree::LevelOrderTraverse(BiTreeNodePointer tree, int(*visit)(BiTreeNodePointer))
{
	BiTreeNodePointer q[MAX_NODE];
	int front = 0, rear = 1;
	BiTreeNodePointer p;
	if (tree == NULL)
		return;
	else
	{
		q[0] = tree;
		while (rear != front)
		{
			p = q[front++];
			visit(p);
			if (p->lchild != NULL) q[rear++] = p->lchild;
			if (p->rchild != NULL) q[rear++] = p->rchild;
		}
	}
}

int BiTree::DeleteNode(BiTreeNodePointer Node)
{
	if (Node != NULL)
		delete Node;
	return 0;
}

void BiTree::InOrderTraverseNoRecursion(BiTreeNodePointer tree, int(*visit)(BiTreeNodePointer))
{
	BiTreeNodePointer s[MAX_NODE], p=tree;
	int top = 0;
	while (!(top == 0 && p == NULL))
	{
		if (p == NULL)
		{
			p = s[--top];
			visit(p);
			p = p->rchild;
		}
		else 
		{
			s[top++] = p;
			p=p->lchild;
		}
	}
}

void BiTree::Traverse(BiTreeNodePointer tree, int order,int(*visit)(BiTreeNodePointer))
{
	if (tree == NULL)
		std::cout << "空二叉树"<<std::endl;
	else
	{
		switch (order)
		{
		case PRE_ORDER:  
			PreOrderTraverse(tree, visit); break;
		case IN_ORDER:   
			InOrderTraverse(tree, visit); break;
		case POST_ORDER: 
			PostOrderTraverse(tree, visit); break;
		case LEVEL_ORDER:
			LevelOrderTraverse(tree, visit); break;
		case PRE_ORDER + NO_RECURSION:
			PreOrderTraverseNoRecursion(tree, visit); break;
		case IN_ORDER + NO_RECURSION:
			InOrderTraverseNoRecursion(tree, visit); break;
		case POST_ORDER + NO_RECURSION:
			PostOrderTraverseNoRecursion(tree, visit); break;
		case LEVEL_ORDER_REVERSE:
			LevelOrderReverseTraverse(tree, visit); break;
		default:         
			std::cout << "参数错误"<<std::endl; break;
		}
	}
}

void BiTree::PreOrderTraverseNoRecursion(BiTreeNodePointer tree, int(*visit)(BiTreeNodePointer))
{
	BiTreeNodePointer s[MAX_NODE];
	int top = 0;
	BiTreeNodePointer p = tree;
	while (!(p == NULL && top == 0))
	{
		if (p == NULL)
		{
			p = s[--top];
			p = p->rchild;
		}
		else
		{
			s[top++] = p;
			visit(p);
			p = p->lchild;
		}
	}
}

void BiTree::PostOrderTraverseNoRecursion(BiTreeNodePointer tree, int(*visit)(BiTreeNodePointer))
{
	int state[MAX_NODE];
	int top=0;
	BiTreeNodePointer s[MAX_NODE];
	BiTreeNodePointer p=tree;
	while (!(p == NULL && top == 0))
	{
		if (p != NULL)
		{//暂存这个节点，令左下角已访问，往左下角走
			s[top] = p;
			state[top]=1;
			top++;
			p = p->lchild;
		}
		else
		{
			p = s[top-1];
			if (state[top - 1] == 2)
			{
				//左右都已访问,则访问根节点
				visit(p);
				top--;
				p = NULL;
			}
			else
			{
				//右侧还没访问，朝右侧走
				state[top - 1] = 2;
				p = p->rchild;
			}
		}
	}
}
void BiTree::LevelOrderReverseTraverse(BiTreeNodePointer tree, int(*visit)(BiTreeNodePointer))
{
	BiTreeNodePointer s[MAX_NODE], q[MAX_NODE],p;
	int top = 0, rear = 0, front = 0;
	q[rear++] = tree;
	while (rear != front)
	{
		p = q[front++];
		s[top++] = p;
		if (p->lchild != NULL)
			q[rear++] = p->lchild;
		if (p->rchild != NULL)
			q[rear++] = p->rchild;
	}
	while (top > 0)
		visit(s[--top]);
}

void BiTree::CreateFromString(char *nodes_value)
{
	int i;
	int a[MAX_NODE];
	StringToArray(nodes_value, a, i);
	CreateFromArray(a, i);
}

int BiTree::GetHeight(BiTreeNodePointer root)//求深度必须要后序遍历
{
	BiTreeNodePointer s[MAX_NODE], p = root,last_visited;
	int top=0, height=0;
	while (!(top == 0 && p == NULL))
	{
		if (p == NULL)
		{
			p = s[top-1];
			if (p->rchild != NULL && p->rchild != last_visited)
			{
				p = p->rchild;
			}
			else
			{
				if (top > height)
					height = top;
				last_visited = p;
				top--;
				p = NULL;
			}
		}
		else
		{
			s[top++] = p;
			p = p->lchild;
		}
	}
	return height;
}

int BiTree::GetHeightV2()
{
	int top = 0;
	int height=0;
	BiTreeNodePointer p = GetRoot(),last_visited=NULL, s[MAX_NODE];

	while (!(p == NULL && top==0))
	{
		if (p == NULL)
		{
			p = s[top - 1];
			if (p->rchild == NULL || p->rchild == last_visited)
			{
				last_visited = p;
				if (top > height)
					height = top;
				top--;
				p = NULL;
			}
			else
			{
				p = p->rchild;
			}
		}
		else
		{
			s[top++] = p;
			p = p->lchild;
		}
	}
	return height;
}

void BiTree::StringToArray(char *input, int *arr, int &length)
{
	length = 0;
	char c = input[length];
	while (c != '\0')
	{
		if (c >= '0'&& c <= '9')
			arr[length] = c & 0xf;
		else if (c >= 'a'&&c <= 'z')
			arr[length] = c - 'a' + 10;
		else
			arr[length] = BiTree::NULL_NODE;
		length++;
		c = input[length];
	}
}

void BiTree::CreateFromPreInString(char *pre, char *in)
{
	int pre_array[MAX_NODE], in_array[MAX_NODE];
	int pre_length, in_length;
	StringToArray(pre, pre_array, pre_length);
	StringToArray(in, in_array, in_length);
	if (!(pre_length != in_length || pre_length == 0))
	    root = CreateFromPreInStringRecursion(pre_array, in_array, pre_length);
}

BiTreeNodePointer BiTree::CreateFromPreInStringRecursion(int *pre, int *in, int length)
{
	if (length != 0)
	{
		BiTreeNodePointer root = new BiTreeNode;
		root->data = pre[0];
		int root_posiotion = 0;
		while (pre[0] != in[root_posiotion])
			root_posiotion++;
		root->lchild = CreateFromPreInStringRecursion(&pre[1], &in[0], root_posiotion);
		root->rchild = CreateFromPreInStringRecursion(&pre[root_posiotion +1], 
			&in[root_posiotion +1], length-root_posiotion-1);
		return root;
	}
	else
		return NULL;
}

int BiTree::IsComleteBiTree()
{
	BiTreeNodePointer q[MAX_NODE], p;
	int rear=0,front=0;
	if (root == NULL)
		return true;
	else
	{
		q[rear++] = root;
		while (rear != front)
		{
			p = q[front++];
			//发现空子女，就开始扫描队列，发现非空值则为非完全二叉树
			if (p == NULL)
			{
				while (rear != front)
				{
					p = q[front++];
					if (p != NULL)
						return false;
				}
				return true;
			}
			else
			{
				q[rear++] = p->lchild;
				q[rear++] = p->rchild;
			}
		}
	}
	return true;
}

int BiTree::GetKthNodePreOrder(int k)
{
	if (k <= 0)
		return NULL_NODE;
	BiTreeNodePointer s[MAX_NODE], p=root;
	int top = 0, count = 0;
	while (!(top == 0 && p == NULL))
	{
		if (p == NULL)
		{
			p = s[--top];
			p = p->rchild;
		}
		else
		{
			count++;
			if (count == k)
				return p->data;
			s[top++] = p;
			p = p->lchild;
		}
	}
	return NULL_NODE;
}

void  BiTree::ShowNodeAncestors(int node_value)
{
	int top = 0,i;
	BiTreeNodePointer s[MAX_NODE], p = root, last_visited;
	while (!(p == NULL && top == 0))
	{
		if (p == NULL)
		{
			p = s[top-1];
			//决定是向右走还是退栈
			if (p->rchild != NULL && p->rchild != last_visited)
			{
				p = p->rchild;
			}
			else
			{
				//已找到，输出
				if (p->data == node_value)
				{
					for (i = 0; i < top; i++)
					{
						std::cout << s[i]->data << " ";
					}
					std::cout << std::endl;
					return;
				}
				else
				{
					last_visited = p;
					top--;
					p = NULL;
				}
			}
		}
		else
		{
			s[top++] = p;
			p = p->lchild;
		}
	}
	std::cout << "查无此值" << std::endl;
	return;
}

int BiTree::ReverseChilds(BiTreeNodePointer node)
{
	BiTreeNodePointer temp;
	temp = node->lchild;
    node->lchild = node->rchild;
    node->rchild = temp;
	return 0;
}

void BiTree::ReverseBiTree()
{
	int(*visit)(BiTreeNodePointer) = ReverseChilds;
	Traverse(root, POST_ORDER, visit);
}

void BiTree::ShowAllDataLevelV2()
{
	int rear = 0, front = 0;
	BiTreeNodePointer p = GetRoot(),q[MAX_NODE];
	if (p == NULL)
		std::cout << "空树" << std::endl;
	else
	{
		q[rear++] = root;
		while (rear != front)
		{
			p = q[front++];
			std::cout << p->data << " ";
			if (p->lchild)
				q[rear++] = p->lchild;
			if (p->rchild)
				q[rear++] = p->rchild;
		}
		std::cout<< std::endl;
	}
	
}

int BiTree::GetWidth()
{
	if (root == NULL)
		return 0;
	BiTreeNodePointer q[MAX_NODE], p;
	int rear = 0, front = 0, level_start = 0, level_end = 0, width=0;
	q[rear++] = root;
	while (front != rear)
	{
		p = q[front++];
		if (p->lchild != NULL) 
			q[rear++] = p->lchild;
		if (p->rchild != NULL) 
			q[rear++] = p->rchild;
		if (front > level_end)
		{
			if (level_end - level_start + 1 > width)
				width = level_end - level_start + 1;
			level_start = front; 
			level_end = rear - 1;
		}
	}
	return width;
}

int BiTree::GetWeightedPathLength()
{
	BiTreeNodePointer s[MAX_NODE], p=root,last_visited;
	int wpl=0, top = 0;
	while (!(p == NULL && top == 0))
	{
		if (p == NULL)
		{
			p = s[top - 1];
			if (p->rchild != NULL && last_visited != p->rchild)
			{
				p = p->rchild;
			}
			else
			{
				top--;
				if (p->lchild == NULL && p->rchild == NULL)
					wpl += p->data*top;
				last_visited = p;
				p = NULL;
			}
		}
		else
		{
			s[top++] = p;
			p = p->lchild;
		}
	}
	return wpl;
}

BiTreeNodePointer BiTree::CreateNewNode(int data)
{
	BiTreeNodePointer new_node = new BiTreeNode;
	new_node->data = data;
	new_node->lchild = NULL;
	new_node->rchild = NULL;
	return new_node;
}

int BiTree::CountOfChildren(BiTreeNodePointer root)
{
	if (root == NULL)
		return -1;
	int count_children = 0;
	if (root->lchild != NULL)
		count_children++;
	if (root->rchild != NULL)
		count_children++;
	return count_children;
}

BiTreeNodePointer BiTree::GetParent(BiTreeNodePointer node_to_search)
{
	int rear = 0, front = 0;
	BiTreeNodePointer q[MAX_NODE], p=root;
	if (root == NULL || node_to_search==NULL)
		return NULL;
	q[rear++] = root;
	while (rear != front)
	{
		p = q[front++];
		if (p->lchild == node_to_search || p->rchild == node_to_search)
			return p;
		if (p->lchild != NULL) q[rear++] = p->lchild;
		if (p->rchild != NULL) q[rear++] = p->rchild;
	}
	return NULL;
}

int BiTree::BreakLink(BiTreeNodePointer parent, BiTreeNodePointer child)
{
	if (parent == NULL || child == NULL)
		return 1;
	if (child == parent->lchild)
		parent->lchild = NULL;
	//parent->lchild == NULL;  如果你写出这样的语句，那么编译器优化过之后根本什么都不会执行
	//而且下面会跳出来warnign，所以说以后warning中的内容还是要看一看的
	else if (child == parent->rchild)
		parent->rchild = NULL;
	else
		return 1;
	return 0;
}

void BiTree::ShowInTable()
{
}