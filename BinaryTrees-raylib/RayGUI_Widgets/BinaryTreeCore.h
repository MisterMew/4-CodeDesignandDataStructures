#pragma once
#include <cstdlib>
#include <iostream>
using namespace std;

class TreeNode;

class BinaryTree {
private:
	TreeNode* mRoot_ptr;

	/// Functions
   /* Declare class functions */
	bool FindNode(int a_nSearchValue, TreeNode*& ppOutNode, TreeNode*& ppOutParent);

public:
	BinaryTree();
	~BinaryTree();

	void InsertNode(int newData);
	void DeleteNode(int nodeToDelete);
	TreeNode* SearchFor(int nodeToFind);

	void DrawRoot(TreeNode* selectedNode);
	void DrawTree(TreeNode* node, int posX, int posY, int horSpace, TreeNode* selectedNode);
};