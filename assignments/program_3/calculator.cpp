/**
* @ProgramName: Program-3
* @Author: Sierra Richards
* @Description:
*     This program implements a simple postfix calculator.
* @Course: 1063 Data Structures
* @Semester: Spring 2017
* @Date: 20 03 2017
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Queue {
private:
	//////////////////////////////////////////////////////

	int ArraySize;
	char *Q;
	int Front;
	int Rear;
	int NumItems;

public:
	//////////////////////////////////////////////////////

	/**
	* @FunctionName: Queue
	* @Description:
	*     Class constructor
	* @Params:
	*    int insize - initial queue size
	* @Returns:
	*    void
	*/
	Queue(int insize) {
		ArraySize = insize;
		Q = new char[ArraySize];
		Front = Rear = NumItems = 0;
	}

	/**
	* @FunctionName: push
	* @Description:
	*     Adds a character to the queue
	* @Params:
	*    char c - character to add
	* @Returns:
	*    void
	*/
	void Push(char c) {
		if (Full()) {
			cout << "Queue Full!" << endl;
			return;
		}
		Q[Rear] = c;
		Rear = (Rear + 1) % ArraySize;
		NumItems++;
		return;
	}

	/**
	* @FunctionName: pop
	* @Description:
	*     Returns a character from the top of the queue
	* @Params:
	*    None
	* @Returns:
	*    void
	*/
	char Pop() {
		if (Empty()) {
			cout << "Queue Empty!" << endl;
			return false;
		}
		int Temp = Q[Front];
		Front = (Front + 1) % ArraySize;
		NumItems--;
		return Temp;
	}

	/**
	* @FunctionName: printQueue
	* @Description:
	*     Prints queue to stdout for debugging purposes
	* @Params:
	*    None
	* @Returns:
	*    void
	*/
	void PrintQueue() {
		for (int i = Front, j = 0; j<NumItems; j++, i = (i + 1) % ArraySize) {
			cout << Q[i] << " ";
		}
		cout << endl;
	}

	/**
	* @FunctionName: empty
	* @Description:
	*     Checks to see if queue is empty.
	* @Params:
	*    None
	* @Returns:
	*    bool - true if empty / false otherwise
	*/
	bool Empty() {
		return (NumItems == 0);
	}

	/**
	* @FunctionName: full
	* @Description:
	*     Checks if queue is full
	* @Params:
	*    None
	* @Returns:
	*    bool - true if full / false otherwise
	*/
	bool Full() {
		return (NumItems == ArraySize);
	}
};
class Stack {
private:
	//////////////////////////////////////////////////////

	char *S;
	int top;
	int size;

public:
	//////////////////////////////////////////////////////

	/**
	* @FunctionName: Stack
	* @Description:
	*     Class constructor
	* @Params:
	*    int insize - initial stack size
	* @Returns:
	*    void
	*/
	Stack(int insize) {
		size = insize;
		top = -1;
		S = new char[size];
	}

	/**
	* @FunctionName: push
	* @Description:
	*     Adds a character to the stack
	* @Params:
	*    char c - character to add
	* @Returns:
	*    void
	*/
	void push(char c) {
		if (!full()) {
			S[++top] = c;
		}
		else {
			cout << "Stack Overflow!" << endl;
		}
	}

	/**
	* @FunctionName: pop
	* @Description:
	*     Returns a character from the top of the stack
	* @Params:
	*    None
	* @Returns:
	*    void
	*/
	char pop() {
		if (!empty())
			return S[top--];
		else
			return -1;
	}

	/**
	* @FunctionName: printStack
	* @Description:
	*     Prints stack to stdout for debugging purposes
	* @Params:
	*    None
	* @Returns:
	*    void
	*/
	void printStack() {
		for (int i = top; i >= 0; i--) {
			cout << S[i] << " ";
		}
		cout << endl;
	}

	/**
	* @FunctionName: empty
	* @Description:
	*     Checks to see if stack is empty.
	* @Params:
	*    None
	* @Returns:
	*    bool - true if empty / false otherwise
	*/
	bool empty() {
		return top == -1;
	}

	/**
	* @FunctionName: full
	* @Description:
	*     Checks if stack is full
	* @Params:
	*    None
	* @Returns:
	*    bool - true if full / false otherwise
	*/
	bool full() {
		return top == size - 1;
	}
};

int main()
{
	//Initialize input file stream
	ifstream infile;
	infile.open("exp.txt"); 


	//Initialize output file stream
	ofstream outfile;
	outfile.open("out.txt", ofstream::app); //Appends results to the end of file

	//Read in the number of expressions to evaluate
	int num;
	infile >> num;

	//While we still have expressions to evaluate
	while (num != 0)
	{
		//Read in the infix expression
		string infix;
		infile >> infix;

		//Initialize Q and Stack
		Queue Q(infix.length() + 5);
		Stack S(infix.length() + 5);
		Queue P(infix.length());



		//Push a left parenthesis onto stack
		S.push('(');

		//Add to the end of infix a right parenthesis
		for (int i = 0; i < infix.length(); i++)
		{
			Q.Push(infix[i]);
		}
		Q.Push(')');

		//While loop to read infix characters (c) while stack S is not empty
		while (!S.empty())
		{
			char c = Q.Pop();


			if (c == ' ')
			{
				//Do Nothing
			}
			else if (c >= '0' && c <= '9')
			{
				P.Push(c); //Digit copied to next element of postfix
			}
			else if (c == '(')
			{
				S.push(c); //Left parenthesis pushed onto stack
			}
			else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '%')
			{
				//Switch statement to evauluate precedence of operators in infix queue
				int val1;
				switch (c) {
				case '+':
				case '-':
					val1 = 2;
					break;

				case '*':
				case '/':
				case '%':
				case '^':
					val1 = 1;
					break;
				default:
					val1 = 3;
				}


				char ch = S.pop();
				S.push(ch);

				//Switch statement to compare precedence of operators in the stack
				int val2;
				switch (ch) {
				case '+':
				case '-':
					val2 = 2;
					break;
				case '*':
				case '/':
				case '%':
				case '^':
					val2 = 1;
					break;
				default:
					val2 = 3;
				}

				while (val1 >= val2)
				{
					S.pop();
					P.Push(ch); //Inserts popped operators in postfix

					ch = S.pop();
					S.push(ch);

					val2;
					switch (ch) {
					case '+':
					case '-':
						val2 = 2;
						break;
					case '*':
					case '/':
					case '%':
					case '^':
						val2 = 1;
						break;
					default:
						val2 = 3;
					}
				}

				S.push(c);  //Pushes the current character of infix onto the stack
			}
			else if (c == ')')
			{
				//Pops operators from the top of the stack while the current character at the top of the stack is not a right parenthesis
				char ch = S.pop();
				while (ch != '(')
				{
					//Pops and discards of the left parenthesis from the stack
					P.Push(ch);
					ch = S.pop(); 
				}
			}
		}


		//Decrement the expression counter
		num--;


		//Make a Queue that will be used to calculate the answer
		Queue AnsQ(infix.length());

		//Make a string that will be used to hold the postfix expression
		string postfix;

		//Put the value of the postfix expression into the answer queue and postfix string
		for (int i = 0; i < infix.length(); i++)
		{
			char c = P.Pop();
			postfix += c;
			AnsQ.Push(c);
		}


		//While the answer queue is not empty
		while (!AnsQ.Empty())
		{
			char c = AnsQ.Pop(); //Pops a character from the Queue


			//Pushes the integer value of the digit onto the stack
			if (c >= '0' && c <= '9')
			{
				int a = c - 48;
				S.push(a);
			}

			//If we get to '\0' then we got to the end of the postfix expression
			else if (c == '\0')
			{
				break;
			}

			//If the character is an operator
			else
			{
				//Two top elements popped off the stack and labelled variables x and y, repectively.
				int x, y;
				x = S.pop();
				y = S.pop();

				//Calculates y operator x and pushes result onto the stack

				if (c == '+')
				{
					y = y + x;
					S.push(y);
				}
				if (c == '-')
				{
					y = y - x;
					S.push(y);
				}
				if (c == '*')
				{
					y = y * x;
					S.push(y);
				}
				if (c == '/')
				{
					y = y / x;
					S.push(y);
				}
				if (c == '^')
				{
					for (int j = 0; j < x; j++)
					{
						y = y * y;
					}
					S.push(y);
				}
				if (c == '%')
				{
					y = y % x;
					S.push(y);
				}
			}

		}


		//The last value in the stack is the answer
		int answer = S.pop();

		//output to file
		outfile << infix << " | ";
		outfile << postfix << " | ";
		outfile << answer << endl;
	}

	infile.close();
	outfile.close();
	return 0;
}
