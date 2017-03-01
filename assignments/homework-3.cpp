/**
* @Homework: Homework-3
* @Author: Sierra Richards
* @Description:
*     This program implements a circular queue.
* @Course: 1063 Data Structures
* @Semester: Spring 2017
* @Date: 01 03 2017
*/

#include <iostream>
#include <random>

using namespace std;

class ArrQueue {
private:
	int ArraySize;
	int *Q;
	int Front;
	int Rear;
	int NumItems;
public:
	ArrQueue(int size = 10) {
		ArraySize = size;
		Q = new int[ArraySize];
		Front = Rear = NumItems = 0;
	}

	bool Push(int value) {
		if (Full()) {
			cout << "Queue Full!" << endl;
			return false;
		}
		Q[Rear] = value;
		Rear = (Rear + 1) % ArraySize;
		NumItems++;
		return true;
	}

	int Pop() {
		if (Empty()) {
			cout << "Queue Empty!" << endl;
			return false;
		}
		int Temp = Q[Front];
		Front = (Front + 1) % ArraySize;
		NumItems--;
		return Temp;
	}

	bool Empty() {
		return (NumItems == 0);
	}

	bool Full() {
		return (NumItems == ArraySize);
	}

	void PrintFR() {
		cout << "Front: " << Front << "Rear: " << Rear << endl;
	}

	/**
	* @FunctionName: Print
	* @Description:
	*     An If statement was inserted. If the queue is full, the first 
	*	  value is printed and Index takes on the position of the next value.
	*	  While that value is not equal to Rear, it is printed and Index
	*	  is incremented again. This is repreated until Index takes on 
	*	  the position of rear. 
	* @Params:
	*    NONE
	* @Returns:
	*    NONE
	*/

	void Print() {
		//FIX ME!
		int Index = Front;

		if (Full())
		{
			cout << Q[Index] << " ";
			Index = ((Index + 1) % (ArraySize));
		}
		while (Index != Rear) {
			cout << Q[Index] << " ";
			Index = ((Index + 1) % (ArraySize));
		}
		cout << endl;
	}


};

int main() {
	srand(983475);
	ArrQueue Q;
	int r = 0;
	bool result;

	for (int i = 0; i<12; i++) {
		r = rand() % 100;
		result = Q.Push(r);
		if (result)
			cout << r << endl;
	}
	Q.PrintFR();
	Q.Print();
	cout << Q.Pop() << endl;
	cout << Q.Pop() << endl;
	cout << Q.Pop() << endl;
	cout << Q.Pop() << endl;
	cout << Q.Pop() << endl;

	Q.Print();
	cout << Q.Pop() << endl;
	cout << Q.Pop() << endl;
	cout << Q.Pop() << endl;
	for (int i = 0; i<3; i++) {
		r = rand() % 100;
		result = Q.Push(r);
		if (result)
			cout << r << endl;
	}
	return 0;
}

