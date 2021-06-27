#include "Node.h"

/// CONSTRUCTOR
Node::Node(Node* parent, int data) {
	mParent_ptr = parent;
	mData = data;
}

/// DECONSTRUCTOR
Node::~Node() {
	delete mParent_ptr;
}

void Node::Insert(int newData) {
	if (mParent_ptr != nullptr) {
		if (GetParent()->GetRight() == nullptr && newData > GetParent()->GetData()) {
			GetParent()->SetRight(new Node(GetParent(), newData));
			return;
		}

		if (GetParent()->GetLeft() == nullptr && newData < GetParent()->GetData()) {
			GetParent()->SetLeft(new Node(GetParent(), newData));
			return;
		}
	}

	//Check for current nodes right/left nodes
	if (newData > this->GetData()) {
		if (this->GetRight() != nullptr) {
			this->GetRight()->Insert(newData);
			return;
		}
		else {
			this->SetRight(new Node(this, newData));
		}
	}

	// Left
	if (newData < this->GetData()) {
		if (this->GetLeft() != nullptr) {
			this->GetLeft()->Insert(newData);
			return;
		}
		else {
			this->SetLeft(new Node(this, newData));
		}
	}
}

/* Function Get Definitions */
Node* Node::GetParent() { return mParent_ptr; }
Node* Node::GetRight() { return mRight_ptr; }
Node* Node::GetLeft() { return mLeft_ptr; }
int   Node::GetData() { return mData; }

void Node::SetParent(Node* parent) { mParent_ptr = parent; }
void Node::SetRight(Node* right) { mRight_ptr = right; }
void Node::SetLeft(Node* left) { mLeft_ptr = left; }
void Node::SetData(int data) { mData = data; }

/* Recursive display function */
void Node::Display(int posX, int posY, int hor) {
	if (this != nullptr) {
		static char buffer[10];
		sprintf(buffer, "%d", this->GetData());

		hor /= 2;

		DrawCircle(posX, posY, 30, ORANGE); //Draw outer edge
		DrawCircle(posX, posY, 28, GOLD);  //Draw inside

		DrawText(buffer, posX - 10, posY - 8, 18, RAYWHITE); //Draw node data
	}

	if (mLeft_ptr != nullptr) {
		DrawLine(posX, posY, posX - hor, posY + 80, BEIGE);
		mLeft_ptr->Display(posX - hor, posY + 80, hor);
	}

	if (mRight_ptr != nullptr) {
		DrawLine(posX, posY, posX + hor, posY + 80, BEIGE);
		mRight_ptr->Display(posX + hor, posY + 80, hor);
	}
}