/// 
cpp

/**
* @ProgramName: FrontSert and EndSert Methods
* @Author: Sierra Richards 
* @Description: 
*     This program uses the FrontSert and EndSert methods which use a head pointer and a tail pointer, respectively, 
	to insert a node in a list.
* @Course: 1063 Data Structures
* @Semester: Spring 2017
* @Date: 10 02 2017
*/


#include <iostream>

struct Node {
	int Data;
	Node *Next;
};

using namespace std;

class List {
private:
	Node *Head;
	Node *Tail;
public:
	List() {
		Head = NULL;
	}

	void FrontSert(int x) {
		Node *Temp = new Node;
		Temp->Data = x;
		Temp->Next = NULL;

		if (Head) {
			Temp->Next = Head;
		}

		if (!Head)
		{
			Tail = Temp;
		}

		Head = Temp;
	}

/**
* @FunctionName: EndSert
* @Description: 
*     Uses the tail pointer to insert a node at the tail end of the list.
* @Params:
*    int x - data in the list
* @Returns:
*    void
*/
	void EndSert(int x)
	{
		Node *Temp = new Node;
		Temp->Data = x;
		Temp->Next = NULL;

		if (!Head)
		{
			Head = Temp;
			Tail = Head;
		}
		else
		{
			Tail->Next = Temp;
			Tail = Temp;
		}
	}

	void PrintList() {
		if (!Head) {
			cout << "Empty" << endl;
			return;
		}
		else {
			Node *Temp = Head;
			while (Temp != NULL) {
				cout << Temp->Data << "->";
				Temp = Temp->Next;
			}
		}
	}

};


int main() {
	srand(97097807);
	List L;
	for (int i = 0; i<10; i++) {
		L.FrontSert(rand() % 100);
	}
	L.EndSert(rand() % 100);
	L.PrintList();


	return 0;
}

///
