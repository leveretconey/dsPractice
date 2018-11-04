#pragma once
#include "BinarySortTree.h"

class SelfBalancingBinarySearchTree :
	public BinarySortTree
{
public:
	SelfBalancingBinarySearchTree();
	~SelfBalancingBinarySearchTree();
	int IsBalanced(BiTreeNodePointer &imbalanced_node);
	int IsBalanced();
	static int GetBalanceFactor(BiTreeNodePointer node);
	BiTreeNodePointer InsertNodeWithValue(int value);
	int Balance();
private:
	static int IsBalancedRecursion(BiTreeNodePointer root, int &is_balanced, BiTreeNodePointer &imbalanced_node);
	int LeftRotation(BiTreeNodePointer imbalanced_node);
	int RightRotation(BiTreeNodePointer imbalanced_node);
	int RebalanceOnce();
};
typedef SelfBalancingBinarySearchTree AVLTree;


