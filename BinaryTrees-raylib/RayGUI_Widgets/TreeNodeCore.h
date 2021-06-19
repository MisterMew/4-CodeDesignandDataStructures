#pragma once
#include <string>
#include <iostream>
using namespace std;

class TreeNode {
private:
	TreeNode* mLeft_ptr = nullptr;
	TreeNode* mRight_ptr = nullptr;
	int mNodeData;


public:
	TreeNode();

	 /// Functions
    /* Declare class functions */
	TreeNode(int value);
	~TreeNode();

	void DrawNode(int posX, int posY, bool isSelected);

	/* Declare and Define class functions */
 	bool BranchesLeft() { return (mLeft_ptr != nullptr); }
	bool BranchesRight() { return (mRight_ptr != nullptr); }

	int NodeData() { return mNodeData; } 
	TreeNode* LeftNode() { return mLeft_ptr; }
	TreeNode* RightNode() { return mRight_ptr; }

	void SetData(int newData) { mNodeData = newData;  }
	void SetLeft(TreeNode* node) { mLeft_ptr = node; }
	void SetRight(TreeNode* node) { mRight_ptr = node; }
};