#include "Node.h"

/// CONSTRUCTOR
Node::Node(Node* parent, int data) {
	mParent_ptr = parent;
	mData = data;
}

/* Function GET Definitions */
Node* Node::GetParent() { return mParent_ptr; }
Node* Node::GetRight() { return mRight_ptr; }
Node* Node::GetLeft() { return mLeft_ptr; }
int   Node::GetData() { return mData; }

/* Function SET Definitions */
void Node::SetParent(Node* parent) { mParent_ptr = parent; }
void Node::SetRight(Node* right) { mRight_ptr = right; }
void Node::SetLeft(Node* left) { mLeft_ptr = left; }
void Node::SetData(const int &data) { mData = data; }

 /// INSERT NODE
/* Insert Node Function */
void Node::Insert(int newData) {
	if (GetParent() != nullptr) {													   //Validate the node isn't a root
		if (GetParent()->GetRight() == nullptr && newData > GetParent()->GetData()) { //If the current node doesnt have a right child and the new nodes data is larger than the current nodes
			GetParent()->SetRight(new Node(GetParent(), newData));					 //Set the current nodes right to be the new node
			return;
		}

		if (GetParent()->GetLeft() == nullptr && newData < GetParent()->GetData()) { //If the current node doesnt have a left child and the new nodes data is smaller than the current nodes
			GetParent()->SetLeft(new Node(GetParent(), newData));					//Set the current nodes left to be the new node
			return;
		}
	}

	///Right Node Insert
	if (newData > GetData()) {			   //If newData is larger than the currentNode's data
		if (GetRight() != nullptr) {	  //and if the current node has a right child
			GetRight()->Insert(newData); //Reinsert the new node to the right
		}
		else {
			SetRight(new Node(this, newData)); //Otherwise insert the new node to the right
		}
	}

	///Left Node Insert
	if (newData < GetData()) {			  //If newData is smaller than the currentNode's data
		if (GetLeft() != nullptr) {		 //and if the current node has a left child
			GetLeft()->Insert(newData); //Reinsert the new node to the left
		}
		else {
			SetLeft(new Node(this, newData)); //Otherwise insert the new node to the left
		}
	}
}

 /// DRAW BINARY TREE
/* Recursive display function to Draw the binary tree */
void Node::Display(int posX, int posY, int hor) {
	if (this == nullptr) { return; }
	hor /= 2;

	///Draw Right node
	if (this->GetRight() != nullptr) {						    //Validate for right node
		DrawLine(posX, posY, posX + hor, posY + 80, BEIGE);    //Draw line from existing node to new node
		this->GetRight()->Display(posX + hor, posY + 80, hor);//Draw the new node
	}

	///Draw Left node
	if (this->GetLeft() != nullptr) {					   	   //Validate for left node
		DrawLine(posX, posY, posX - hor, posY + 80, BROWN);   //Draw line from existing node to new node
		this->GetLeft()->Display(posX - hor, posY + 80, hor);//Draw the new node
	}

	 /// DRAW NODE
    /* Draws the node */
	DrawCircle(posX, posY, 30, ORANGE); //Draw outer edge
	DrawCircle(posX, posY, 28, GOLD);  //Draw inside

	/* Draws the nodes data */
	DrawText(std::to_string(this->GetData()).c_str(), posX - 10, posY - 8, 18, RAYWHITE); //Draw node data
}