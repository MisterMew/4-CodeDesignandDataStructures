#include "DLLCore.h"
#include "raylib.h"

namespace DLL {
	LinkedList::Node* LinkedList::Get(int index) {
		Node* currentNode = mhead_ptr;

		if (index > mNodeCount) {
			return mtail_ptr;
		}
		if (index < 0) {
			return mhead_ptr;
		}

		for (int i = 0; i < index; i++) {		   //Loop through until we reach index
			if (currentNode->next != nullptr) {   //If the next node isn't null
				currentNode = currentNode->next; //Go to the next Node
			}
		}

		return currentNode;
	}

#pragma region // Insert Nodes //

	 /// INSERT to FRONT
	/* Insert a node to the front of the list */
	void LinkedList::InsertHead(int newData) {
		Node* newNode = new Node(newData, nullptr, nullptr); //Allocate memory for a new Node

		 /// Safety Flag
		/* Null Head */
		if (mhead_ptr == nullptr) {   //Check if the head is null
			newNode->prev = nullptr; //Make newNodes previous node, null
			newNode->next = nullptr;//Make newNodes next node, null
			mhead_ptr = newNode;   //Make the head the new node.

			mNodeCount++;		 //Increment NodeCount
			return;			    //Exit Function
		}

		/* Null Tail */
		if (mtail_ptr == nullptr) {		    //Check if the tail is null
			newNode->prev = mhead_ptr;	   //Make newNodes previous node, the head
			newNode->next = nullptr;	  //Make newNodes next node, the head
			mtail_ptr = newNode;		 //Make the tail the newNode.
			mhead_ptr->next = mtail_ptr;//Make the head's next node, the tail

			mNodeCount++;		      //Increment NodeCount
			return;					 //Exit Function
		}

		Node* currentNode = mhead_ptr;

		currentNode->prev = newNode;
		newNode->next = currentNode;
		newNode->prev = nullptr;
		mhead_ptr = newNode;
		
		mNodeCount++; //Increment NodeCount
	}

	 /// INSERT to ARBITRARY
	/* Insert a node to an arbitrary point in the list */
	void LinkedList::InsertNode(int newData, int nodePos) {
		Node* newNode = new Node(newData, nullptr, nullptr);

		 /// Safety Flags
		/* Null Head */
		if (mhead_ptr == nullptr || nodePos <= 0) {
			InsertHead(newData);
			return;
		}

		/* Null Tail */
		if (mtail_ptr == nullptr || nodePos >= mNodeCount) {
			InsertTail(newData);
			return;
		}

		Node* currentNode = Get(nodePos);

		newNode->next = currentNode;
		newNode->prev = currentNode->prev;
		currentNode->prev->next = newNode;
		currentNode->prev = newNode;

		mNodeCount++; //Increment NodeCount
	}

	 /// INSERT to END
	/* Insert a node to the end of the list */
	void LinkedList::InsertTail(int newData) {
		Node* newNode = new Node(newData, nullptr, nullptr);

		 /// SAFETY FLAGS 
		/* Null Head */
		if (mhead_ptr == nullptr) {   //Check if the head is null
			newNode->prev = nullptr; //Make newNodes previous node, null
			newNode->next = nullptr;//Make newNodes next node, null
			mhead_ptr = newNode;   //Make the head the new node.

			mNodeCount++;		 //Increment NodeCount
			return;				//Exit Function
		}

		/* Null Tail */
		if (mtail_ptr == nullptr) {		    //Check if the tail is null
			newNode->prev = mhead_ptr;	   //Make newNodes previous node, the head
			newNode->next = nullptr;	  //Make newNodes next node, the head
			mtail_ptr = newNode;		 //Make the tail the newNode.
			mhead_ptr->next = mtail_ptr;//Make the head's next node, the tail

			mNodeCount++;		      //Increment NodeCount
			return;					 //Exit Function
		}

		Node* currentNode = mtail_ptr;
		
		currentNode->next = newNode;  //Make currentNodes next node, the newNode
		newNode->prev = currentNode; //Make newNodes previous node, the current Node
		newNode->next = nullptr;    //Make newNodes next node, null
		mtail_ptr = newNode;	   //Make the tail the newNode

		mNodeCount++; //Increment NodeCount
	}

#pragma endregion

#pragma region // Delete Nodes //

	 /// DELETE NODE: Head
	/* Delete the current head node */
	void LinkedList::DeleteHead() {
		if (mhead_ptr == nullptr) { return; }

		Node* currentNode = mhead_ptr;

		if (currentNode->next == nullptr) { //If there is only one node
			mhead_ptr = nullptr;		   //Set mhead_ptr to nullptr
			mtail_ptr = nullptr;		  //Set mtail_ptr to nullptr
			delete currentNode;		     //Delete the Node

			mNodeCount--;		   	   //Decrement NodeCount
			return;					  //Exit Function
		}

		currentNode->next->prev = nullptr;
		mhead_ptr = currentNode->next;
		delete currentNode;

		mNodeCount--; //Decrement NodeCount
	}

	 /// DELETE NODE: Middle
	/* Delete any body node */
	void LinkedList::DeleteNode(int nodeToDelete) {
		if (mhead_ptr == nullptr) { return;	}

		// Selected Node is the head
		if (nodeToDelete <= 0) {
			DeleteHead();
			return;
		}

		// Selected Node is the tail
		if (nodeToDelete >= mNodeCount - 1) {
			DeleteTail();
			return;
		}

		Node* currentNode = Get(nodeToDelete);

		currentNode->prev->next = currentNode->next;  //Set the current nodes previous nodes, next node | to the current nodes next node
		currentNode->next->prev = currentNode->prev; //Set the current nodes next nodes, previous node | to the current nodes previous node
		delete currentNode;							//Delete the current node

		mNodeCount--; //Decrement NodeCount
	}

	 /// DELETE NODE: Tail
	/* Delete the current tail node */
	void LinkedList::DeleteTail() {
		if (mtail_ptr == nullptr) { return; }

		Node* currentNode = mtail_ptr;

		if (currentNode->prev == nullptr) { //If there is only one node
			mhead_ptr = nullptr;		   //Set mhead_ptr to nullptr
			mtail_ptr = nullptr;		  //Set mtail_ptr to nullptr
			delete currentNode;			 //Delete the Node

			mNodeCount--;			   //Decrement NodeCount
			return;					  //Exit Function
		}

		currentNode->prev->next = nullptr;
		mtail_ptr = currentNode->prev;
		delete currentNode;

		mNodeCount--; //Decrement NodeCount
	}

#pragma endregion

#pragma region // Draw List //

	 /// DRAW NODES
	/* Draw the dll nodes */
	void LinkedList::DrawNodes(int selectedNode) {
		if (mNodeCount <= 0) {															 //If the list is empty
			const string txtEmptyList = "[THE DOUBLE LINKED LIST IS EMPTY]";			//The message I want to display (below converted from string to char)
			DrawText(txtEmptyList.c_str(), 450, GetScreenHeight() / 2, 20, LIGHTGRAY); //Display at the screens center
			return;																	  //Exit Function
		}

		/// VARIABLES
		const int outerRadius = 30;
		const int innerRadius = 27;
		int i = 0;

		Node* node = mhead_ptr;

		while (node != nullptr) {
			if (node == nullptr) { return; }

			int posX = ((GetScreenWidth()) / mNodeCount) * i + outerRadius; //Calculate x position
			int posY = (GetScreenHeight() / 2);							   //Calculate y position

			///Convert int to string for raylib use
			static char nodeText[10]; //Create a static char buffer
			sprintf(nodeText, "%d", node->data);

			//Draw HEAD node Red
			if (node == mhead_ptr) {
				DrawCircle(posX, posY, outerRadius, MAROON);
				DrawCircle(posX, posY, innerRadius, RED);
			}

			//Draw TAIL node Orange
			if (node == mtail_ptr) {
				DrawCircle(posX, posY, outerRadius, ORANGE);
				DrawCircle(posX, posY, innerRadius, GOLD);
			}

			//Draw every other Node Brown
			if (node != mhead_ptr && node != mtail_ptr) { 
				DrawCircle(posX, posY, outerRadius, BROWN);
				DrawCircle(posX, posY, innerRadius, BEIGE);
			}

			//Draw selected Node Grey
			if (i == selectedNode) {
				DrawCircle(posX, posY, outerRadius, LIGHTGRAY);
				DrawCircle(posX, posY, innerRadius, GRAY);

				//Make the selected nodes data appear above the list
				DrawText(nodeText, ((GetScreenWidth() / 2) - (sizeof(nodeText))), ((GetScreenHeight() / 3)), 40, MAROON);
			}

			DrawText(nodeText, posX - (sizeof(nodeText) * 2), posY - 10, 20, RAYWHITE); //Draw each nodes data
			
			i++; //Increment
			node = node->next; //Iterate to next node
		}
	}

#pragma endregion

#pragma region [ Sorting Algorithm ]
	 /// SORTING
	/*  sort the Linked List */
	void LinkedList::SortList() {
		if (mhead_ptr == nullptr) { return; }

		Node* currentNode = nullptr;
		Node* index = nullptr;
		int temp;

		for (currentNode = mhead_ptr; currentNode->next != nullptr; currentNode = currentNode->next) {
			for (index = currentNode->next; index != nullptr; index = index->next) {
				if (currentNode->data > index->data) {
					temp = currentNode->data;
					currentNode->data = index->data;
					index->data = temp;
				}
			}
		}
	}

#pragma endregion


	 /// CREATE NODE DATA
	/* Generates a random data value */
	int LinkedList::CreateData() {
		int newData;

		random_device rdm;                              //Obtains a random num from hardware  ||
		mt19937 genData(rdm());                        //Seed the generator                   || mt19937 is a pseudo-random generator of 32-bit numbers with a state size of 19937 bits.
		uniform_int_distribution<> dataRange(0, 999); //Defines the range to generate between ||

		newData = dataRange(genData);

		return newData;
	}

	 /// COUNT NODES
	/* Iterate the nodes and return the count */
	int LinkedList::CountNodes() {
		if (mhead_ptr == nullptr) { return 0; }

		int nodesCount = 0;
		Node* current = mhead_ptr;

		while (current != nullptr) {
			nodesCount++;
			current = current->next;
		}

		return nodesCount;
	}

	 /// DISPLAY DL-LIST
	/* Iterates each node to display the list */
	void LinkedList::DisplayDLList() {
		Node* current = mhead_ptr;

		if (current == nullptr) {
			cout << " [NULL ERROR] " << endl;
			return;
		}

		while (current != nullptr) {
			current = current->next;
		}
	}
}