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
	bool FindNode(int a_nSearchValue, TreeNode*& outNode, TreeNode*& outParent);

public:
	BinaryTree();
	~BinaryTree();


	void InsertNode(int newData);
	void DeleteNode(int nodeToDelete);

	TreeNode* Get(int dataToFind);
	TreeNode* Root() { return mRoot_ptr; }

	void DrawRoot(TreeNode* selectedNode);
	void DrawTree(TreeNode* node, int posX, int posY, int horSpace, TreeNode* selectedNode);
};