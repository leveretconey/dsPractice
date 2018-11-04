#include "HuffmanTree.h"
#include <iostream>


HuffmanTree::HuffmanTree()
{
}


HuffmanTree::~HuffmanTree()
{
}

int HuffmanTree::CreateFromWeightString(char *weights_string)
{
	if (*weights_string == '\0')
		return 1;
	int nodes_weight[MAX_NODE],length;
	StringToArray(weights_string, nodes_weight, length);
	int i;
	int min_position, min2_position;
	BiTreeNodePointer new_node;
	BiTreeNodePointer nodes_pointer[MAX_NODE];
	for (i = 0; i < length; i++)
		nodes_pointer[i] = CreateNewNode(nodes_weight[i]);

	while (length>1)
	{
		//寻找权重最小的两个结点
		if (nodes_weight[0] < nodes_weight[1])
		{
			min_position = 0;
			min2_position = 1;
		}
		else
		{
			min_position = 1;
			min2_position = 0;
		}
		for (i = 2; i < length; i++)
		{
			if (nodes_weight[i] < nodes_weight[min_position])
			{
				min2_position = min_position;
				min_position = i;
			}
			else if (nodes_weight[i] < nodes_weight[min2_position])
			{
				min2_position = i;
			}
		}

		new_node = new BiTreeNode;
		new_node->data = nodes_weight[min_position] + nodes_weight[min2_position];
		new_node->lchild = nodes_pointer[min_position];
		new_node->rchild = nodes_pointer[min2_position];

		if (min_position > min2_position)
		{
			min_position = min_position^min2_position;
			min2_position = min_position^min2_position;
			min_position = min_position^min2_position;
		}

		nodes_weight[min_position] = new_node->data;
		nodes_weight[min2_position] = nodes_weight[length - 1];
		nodes_pointer[min_position] = new_node;
		nodes_pointer[min2_position] = nodes_pointer[length - 1];
		length--;
	}
	SetRoot(nodes_pointer[0]);
	return 1;
}

int HuffmanTree::ShowHuffanCode(int weight_to_find)
{
	BiTreeNodePointer s[MAX_NODE], p = GetRoot(),last_visited;
	int top = 0, i;
	while (!(top == 0 && p == NULL))
	{
		if (p == NULL)
		{
			p = s[top - 1];
			if (!(p->rchild != NULL&& p->rchild != last_visited))
			{
				if (p->data == weight_to_find && CountOfChildren(p) == 0)
				{
					std::cout << weight_to_find << '\t';
					for (i = 1; i < top; i++)
					{
						if (s[i - 1]->lchild == s[i])
							std::cout << '0';
						else
							std::cout << '1';
					}
					std::cout << std::endl;
					return 0;
				}
				else
				{
					last_visited = p;
					top--;
					p = NULL;
				}
			}
			else
				p = p->rchild;
		}
		else
		{
			s[top++] = p;
			p = p->lchild;
		}
	}
	std::cout << weight_to_find << '\t' << "查不到此节点" << std::endl;
	return 1;
}