#pragma once
#include <string>
namespace leveretconey {
	enum TraverseType{
		PRE,IN,POST
	};
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
		RBTreeNodePointer getNewNode(Color color, int key,RBTreeNodePointer parent);
		void deleteNode(RBTreeNodePointer node);
		void rotateLeft(RBTreeNodePointer node);
		void rotateRight(RBTreeNodePointer node);
		void adjustInsert(RBTreeNodePointer node);
		void adjustDelete();
		void traversePre(RBTreeNodePointer node, void(*callback)(RBTreeNodePointer));
		void traverseIn(RBTreeNodePointer node, void(*callback)(RBTreeNodePointer));
		void traversePost(RBTreeNodePointer node, void(*callback)(RBTreeNodePointer));
	public:
		void insert(int key);
		void show();
		RBTreeNodePointer getNil();
		void del(int key);
		void del(RBTreeNodePointer node);
		RBTreeNodePointer search(int key);
		void traverse(TraverseType type, void (*callback)(RBTreeNodePointer));
		void createFromFile(std::string path);
		RBTree();
		~RBTree();
	};
}