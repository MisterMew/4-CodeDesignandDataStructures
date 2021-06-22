#pragma once
#include <string>
#include <iostream>
using namespace std;

class TreeNode {
private:
	int mNodeData = 0;
	TreeNode* mParent_ptr = nullptr;
	TreeNode* mLeft_ptr = nullptr;
	TreeNode* mRight_ptr = nullptr;


public:
	TreeNode(int data, TreeNode* parentNode, TreeNode* leftNode, TreeNode* rightNode) {
		mNodeData = data;
		mParent_ptr = parentNode;
		mLeft_ptr = leftNode;
		mRight_ptr = rightNode;
	}

	 /// Functions
    /* Function declarations */
	TreeNode(int value);
	~TreeNode();

	void InsertNode(int newData);

	void DeleteNode(TreeNode* mNodeToDelete);
	void DeleteLeaf(TreeNode* mNodeToDelete);
	void DeleteLeft(TreeNode* mNodeToDelete);
	void DeleteRight(TreeNode* mNodeToDelete);
	void DeleteParent(TreeNode* mNodeToDelete);

	void DrawNode(int posX, int posY, bool isSelected);


	/* Function definitions */
 	bool BranchesLeft() { return (mLeft_ptr != nullptr); }
	bool BranchesRight() { return (mRight_ptr != nullptr); }

	int NodeData() { return mNodeData; } 
	TreeNode* Parent() { return mParent_ptr; }
	TreeNode* LeftNode() { return mLeft_ptr; }
	TreeNode* RightNode() { return mRight_ptr; }

	void SetData(int newData) { mNodeData = newData; }
	void SetParent(TreeNode* parent) { mParent_ptr = parent; }
	void SetLeft(TreeNode* node) { mLeft_ptr = node; }
	void SetRight(TreeNode* node) { mRight_ptr = node; }
};