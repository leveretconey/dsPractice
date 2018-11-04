#include "CSTree.h"
#include<iostream>


CSTree::CSTree()
{
	root = NULL;
}


CSTree::~CSTree()
{
	Traverse(root, ROOT_LAST_REVERSE_ORDER, &DeleteNode);
}

void CSTree::CreateFromBiTree(BiTree *bi_tree)
{
	root = CreateFromBiTreeRecursion(bi_tree->GetRoot());
}

 CSTreePointer CSTree::CreateFromBiTreeRecursion(BiTreeNodePointer bi_tree_root)
{
	 if (bi_tree_root == NULL)
		 return NULL;
	 CSTreePointer new_node = new CSTreeNode;
	 new_node->data = bi_tree_root->data;
	 new_node->first_child = CreateFromBiTreeRecursion(bi_tree_root->lchild);
	 new_node->next_subling = CreateFromBiTreeRecursion(bi_tree_root->rchild);
	 return new_node;
}

 int CSTree::ShowNodeData(CSTreePointer Node)
 {
	 if (Node != NULL)
		 std::cout << Node->data << " ";
	 return 0;
 }

 void CSTree::RootFisrtOrderTraverse(CSTreePointer tree, int(*visit)(CSTreePointer))
 {
	 if (tree != NULL)
	 {
		 visit(tree);
		 RootFisrtOrderTraverse(tree->first_child,visit);
		 RootFisrtOrderTraverse(tree->next_subling,visit);
	 }
 }

 void CSTree::RootLastOrderTraverse(CSTreePointer tree, int(*visit)(CSTreePointer))
 {
	 if (tree != NULL)
	 {
		 RootLastOrderTraverse(tree->first_child, visit);
		 visit(tree);
		 RootLastOrderTraverse(tree->next_subling, visit);
	 }
 }

 void CSTree::Traverse(CSTreePointer tree, int order, int(*visit)(CSTreePointer))
 {
	 if (tree == NULL)
		 std::cout << "¿ÕÊ÷" << std::endl;
	 else
	 {
		 switch (order)
		 {
		 case ROOT_FISRT_ORDER:
			 RootFisrtOrderTraverse(tree, visit); break;
		 case ROOT_LAST_ORDER:
			 RootLastOrderTraverse(tree, visit); break;
		 case ROOT_LAST_REVERSE_ORDER:
			 RootLastReverseOrderTraverse(tree, visit); break;
		 default:
			 std::cout << "²ÎÊý´íÎó" << std::endl; break;
		 }
	 }
 }

 void CSTree::ShowAllData(int order)
 {
	 int(*visit)(CSTreePointer) = &(CSTree::ShowNodeData);
	 Traverse(root, order, visit);
	 std::cout << std::endl;
 }

 int CSTree::DeleteNode(CSTreePointer Node)
 {
	 if (Node != NULL)
		 delete Node;
	 return 0;
 }

 void CSTree::RootLastReverseOrderTraverse(CSTreePointer tree, int(*visit)(CSTreePointer))
 {
	 if (tree != NULL)
	 {
		 RootLastReverseOrderTraverse(tree->first_child, visit);
		 RootLastReverseOrderTraverse(tree->next_subling, visit);
		 visit(tree);
	 }
 }

 int CSTree::LeafCount()
 {
	 return LeafCountRecursion(root);
 }

 int CSTree::LeafCountRecursion(CSTreePointer tree)
 {
	 int result = 0;
	 if (tree != NULL)
	 {
		 if (tree->first_child == NULL)
			 result = 1;
		 return result + LeafCountRecursion(tree->first_child) + LeafCountRecursion(tree->next_subling);
	 }
	 else
		 return 0;
}

 void CSTree::CreateFromLevelDegree(int *level, int *degree, int length)
 {
	 int i, father=0, child_visited=0;
	 CSTreePointer nodes[MAX_NODE];
	 nodes[0] = NULL;
	 for (i = 0; i < length; i++)
	 {
		 nodes[i] = new CSTreeNode;
		 nodes[i]->data = level[i];
		 nodes[i]->first_child = NULL;
		 nodes[i]->next_subling = NULL;
		 if (i == 0) 
			 continue;
		 if (child_visited == 0)
			 nodes[father]->first_child = nodes[i];
		 else
			 nodes[i - 1]->next_subling = nodes[i];
		 child_visited++;
		 if (degree[father] == child_visited && i != length - 1)
		 {
			 father++;
			 while (degree[father] == 0)
				 father++;
			 child_visited = 0;
		 }
	 }
	 root = nodes[0];
 }

 CSTreePointer CSTree::GetRoot()
 {
	 return root;
 }
