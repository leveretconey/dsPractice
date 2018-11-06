#pragma once
namespace leveretconey {
	enum Color
	{
		RED, BLACK
	};
	struct RBTreeNode {

		Color color;
		int key;
		RBTreeNode *left, *right, *parent;
	};
	typedef RBTreeNode* RBTreeNodePointer;
	class RBTree
	{
	private:
		RBTreeNodePointer root, nil;
		RBTreeNodePointer getNewNode(Color color, int key);
		void deleteNode(RBTreeNodePointer node);
	public:
		RBTree();
		~RBTree();
	};
}
