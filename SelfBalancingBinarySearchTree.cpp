#include "SelfBalancingBinarySearchTree.h"
#include <iostream>


SelfBalancingBinarySearchTree::SelfBalancingBinarySearchTree()
{
}


SelfBalancingBinarySearchTree::~SelfBalancingBinarySearchTree()
{
}

int SelfBalancingBinarySearchTree::IsBalanced(BiTreeNodePointer &imbalanced_node)
{
	int is_balanced=true;
	imbalanced_node = NULL;
	IsBalancedRecursion(GetRoot(), is_balanced, imbalanced_node);
	return is_balanced;
}

int SelfBalancingBinarySearchTree::IsBalancedRecursion(BiTreeNodePointer root, int &is_balanced,BiTreeNodePointer &imbalanced_node)
{
	if (root == NULL)
	{
		return 0;
	}
	else 
	{
		int lchild_depth = IsBalancedRecursion(root->lchild, is_balanced, imbalanced_node);
		int rchild_depth = IsBalancedRecursion(root->rchild, is_balanced, imbalanced_node);
		if (lchild_depth > rchild_depth + 1 || lchild_depth + 1 < rchild_depth)
		{
			is_balanced = false;
			if (imbalanced_node == NULL)
				imbalanced_node = root;
		}
		if (lchild_depth > rchild_depth)
			return lchild_depth + 1;
		else
			return rchild_depth + 1;
	}
}

int SelfBalancingBinarySearchTree::IsBalanced()
{
	int is_balanced = true;
	BiTreeNodePointer imbalanced_node = NULL;
	IsBalancedRecursion(GetRoot(), is_balanced, imbalanced_node);
	return is_balanced;
}

int SelfBalancingBinarySearchTree::LeftRotation(BiTreeNodePointer imbalanced_node)
{
	if (imbalanced_node == NULL)
		return 1;
	BiTreeNodePointer original_rchild = imbalanced_node->rchild;
	if (original_rchild == NULL)
		return 1;

	BiTreeNodePointer imbalanced_node_parent = GetParent(imbalanced_node);
	if (imbalanced_node_parent==NULL)//有可能这一旋转把根节点给转了，所以需要判断新的根节点
		SetRoot(original_rchild);
	else//也可能把别的节点给转了，需要改变父节点的指针
	{
		if (imbalanced_node_parent->lchild == imbalanced_node)
			imbalanced_node_parent->lchild = original_rchild;
		else
			imbalanced_node_parent->rchild = original_rchild;
	}

	imbalanced_node->rchild = original_rchild->lchild;
	original_rchild->lchild = imbalanced_node;
 
	return 0;
}

int SelfBalancingBinarySearchTree::RightRotation(BiTreeNodePointer imbalanced_node)
{//左旋和右旋在实际实现上的区别仅仅在于将所有的左右互换
	if (imbalanced_node == NULL)
		return 1;
	BiTreeNodePointer original_lchild = imbalanced_node->lchild;
	if (original_lchild == NULL)
		return 1;

	BiTreeNodePointer imbalanced_node_parent = GetParent(imbalanced_node);
	if (imbalanced_node_parent == NULL)
		SetRoot(original_lchild);
	else
	{
		if (imbalanced_node_parent->lchild == imbalanced_node)
			imbalanced_node_parent->lchild = original_lchild;
		else
			imbalanced_node_parent->rchild = original_lchild;
	}

	imbalanced_node->lchild = original_lchild->rchild;
	original_lchild->rchild = imbalanced_node;
	return 0;
}

BiTreeNodePointer SelfBalancingBinarySearchTree::InsertNodeWithValue(int value)
{
	BiTreeNodePointer new_node= this->BinarySortTree::InsertNodeWithValue(value);
	RebalanceOnce();
	return new_node;
}

int SelfBalancingBinarySearchTree::RebalanceOnce()
{
	BiTreeNodePointer imbalanced_node;
	if (!IsBalanced(imbalanced_node))
	{
		int imba_node_factor = GetBalanceFactor(imbalanced_node);
		int imba_node_lchild_factor = GetBalanceFactor(imbalanced_node->lchild);
		int imba_node_rchild_factor = GetBalanceFactor(imbalanced_node->rchild);
		if (imba_node_factor >= 0 && imba_node_lchild_factor >= 0)//LL
		{
			RightRotation(imbalanced_node);
			return 0;
		}
		else if (imba_node_factor >= 0 && imba_node_lchild_factor < 0)//LR
		{
			LeftRotation(imbalanced_node->lchild);
			RightRotation(imbalanced_node);
			return 0;
		}
		else if (imba_node_factor < 0 && imba_node_rchild_factor < 0)//RR
		{
			LeftRotation(imbalanced_node);
			return 0;
		}
		else if (imba_node_factor < 0 && imba_node_rchild_factor >= 0)//RL
		{
			RightRotation(imbalanced_node->rchild);
			LeftRotation(imbalanced_node);
			return 0;
		}
		else
			return 1;
	}
	else
		return 1;
}

int SelfBalancingBinarySearchTree::GetBalanceFactor(BiTreeNodePointer node)
{
	if (node == NULL)
		return 0;
	else
	{
		int lchild_depth = GetDpeth(node->lchild);
		int rchild_depth = GetDpeth(node->rchild);
		return lchild_depth - rchild_depth;
	}
}
int SelfBalancingBinarySearchTree::Balance()
{
	if (IsLegalBST())
	{
		while (!IsBalanced())
			RebalanceOnce();
		return 1;
	}
	return 0;
}
