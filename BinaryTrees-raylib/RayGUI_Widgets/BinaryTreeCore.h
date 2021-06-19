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
public:
	void InsertNode(int newData);
	void DeleteNode(int nodeToDelete);
	TreeNode* SearchTree(int nodeToFind);

	void DrawRoot(TreeNode* selectedNode);
};