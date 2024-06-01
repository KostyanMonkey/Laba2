#include <iostream>
#include <string>

using namespace std;

class Binary
{
private:
	int* binArr;
	long long int number, exeption;
	int size = 8;
	long long power(int base, int exp)
	{
		long long result(1);
		for (int i = 0; i < exp; i++)
			result = result * base;
		return result;
	}
public:
	Binary()
	{
		number = 0;
	}
	Binary(long long int n)
	{
		binArr = new int[size];
		exeption = n;
		if (exeption == 0) number = 0;
		else {
			do
			{
				if ((exeption <= (-1 * power(2, size - 1) - 1)) || (exeption >= power(2, size - 1))) {
					cout << "\n Variable " << exeption << " is out of bounds. Try to imput correct value again." << endl;
					cin >> exeption;
					continue;
				}
				break;
			} while (true);

			if (exeption < 0) number = power(2, size) + exeption;
			else {
				number = exeption;
			}

		}
		long long int count = number;

		long long int iterator = 0;
		while (count > 0) {
			binArr[iterator] = count % 2;
			count = count / 2;
			iterator++;
		}
		for (int i = 1; i <= size - iterator; i++)	binArr[size - i] = 0;
	}
	void print()
	{
		int printer = 0;
		
		for (int i = size - 1; i >= 0; i--) {
			
			cout << binArr[i];
			
		}
		cout << endl;
	}

	int convertToDecimal()
	{

		int dec_value = 0;

		for (int i = size - 1; i >= 0; i--) {
			if (binArr[i] == 1)
				dec_value = dec_value + power(2, i);
		}
		if (binArr[size - 1] == 1) dec_value = dec_value - power(2, size);
		return dec_value;
	}
	int* sumForMult(int* temporary, int* obj, int multSize)
	{
		int* result = new int[multSize];

		int carry = 0;

		for (int i = 0; i < multSize; i++) {
			int x1 = temporary[i];
			int x2 = obj[i];
			int sum = x1 + x2 + carry;
			if (sum == 0)
				result[i] = 0;
			else if (sum == 1) {
				result[i] = 1;
				carry = 0;
			}
			else if (sum == 2) {
				result[i] = 0;
				carry = 1;
			}
			else if (sum == 3) {
				result[i] = 1;
				carry = 1;
			}
		}
		return result;
	}
	Binary operator+(Binary obj)
	{
		Binary temporary(*this);

		if ((obj.exeption + temporary.exeption > (power(2, size - 1) - 1)) || (obj.exeption + temporary.exeption < (-1 * power(2, size - 1))))
		{
			cout << "\nCalculation contains variable out of bounds." << endl;
			exit(0);
		}
		Binary result(0);

		int carry = 0;

		for (int i = 0; i < obj.size; i++) {
			int x1 = temporary.binArr[i];
			int x2 = obj.binArr[i];
			int sum = x1 + x2 + carry;
			if (sum == 0)
				result.binArr[i] = 0;
			else if (sum == 1) {
				result.binArr[i] = 1;
				carry = 0;
			}
			else if (sum == 2) {
				result.binArr[i] = 0;
				carry = 1;
			}
			else if (sum == 3) {
				result.binArr[i] = 1;
				carry = 1;
			}
		}
		result.exeption = result.convertToDecimal();
		result.number = result.convertToDecimal();
		return result;
	}
	Binary operator-(Binary obj)
	{
		Binary temporary(*this);
		Binary result(0);
		Binary minus(-obj.exeption);

		result = temporary + minus;
		result.exeption = result.convertToDecimal();
		result.number = result.convertToDecimal();
		return result;
	}
	Binary operator*(Binary obj)
	{
		Binary temporary(*this);
		if ((temporary.exeption * obj.exeption > (power(2, size - 1) - 1)) || (temporary.exeption * obj.exeption < (-1 * power(2, size - 1))))
		{
			cout << "\nCalculation contains variable out of bounds." << endl;
			exit(0);
		}
		Binary result(0);

		int* firstElOfSum = new int[2 * size - 1];
		int* secondElOfSum = new int[2 * size - 1];

		for (int i = 0; i < obj.size; i++)
		{
			if ((obj.binArr[i] == 1) && (i == 0))
			{
				for (int t1 = i; t1 < obj.size + i; t1++) firstElOfSum[t1] = temporary.binArr[t1 - i];
				for (int t2 = 0; t2 < i; t2++) firstElOfSum[t2] = 0;
				for (int t3 = obj.size + i; t3 < 2 * size - 1; t3++) firstElOfSum[t3] = 0;
				i++;
			}
			if ((obj.binArr[i] == 0) && (i == 0))
			{
				for (int t1 = 0; t1 < 2 * size - 1; t1++) firstElOfSum[t1] = 0;
				i++;
			}

			if ((obj.binArr[i] == 1) && (i != 0))
			{
				for (int t1 = i; t1 < obj.size + i; t1++) secondElOfSum[t1] = temporary.binArr[t1 - i];
				for (int t2 = 0; t2 < i; t2++) secondElOfSum[t2] = 0;
				for (int t3 = obj.size + i; t3 < 2 * size - 1; t3++) secondElOfSum[t3] = 0;
			}
			if ((obj.binArr[i] == 0) && (i != 0))
			{
				for (int t1 = 0; t1 < 2 * size - 1; t1++) secondElOfSum[t1] = 0;
			}
			firstElOfSum = sumForMult(firstElOfSum, secondElOfSum, 2 * size - 1);
		}
		for (int i = 0; i < obj.size; i++) result.binArr[i] = firstElOfSum[i];

		result.exeption = result.convertToDecimal();
		result.number = result.convertToDecimal();
		return result;
	}
};

class BinaryStackList 
{
private:
	class Node 
	{
	public:
		Node* pNext; 
		Binary data;

		Node(Binary data, Node* pNext = nullptr) 
		{
			this->data = data;  // стрелочка это доступ к элементу по указателю
			this->pNext = pNext; 

		}
	};
	int Size; 
	Node* head; 
	
public:
	BinaryStackList() 
	{
		Size = 0;
		head = nullptr;
	}
	// цьцьць
	~BinaryStackList()  // деструктор
	{
		clear();
	}
	void push(Binary data) 
	{
		head = new Node(data, head);
		Size++;
	}

	int GetSize() { return Size; } 

	void pop() 
	{
		Node* temp = head;

		head = head->pNext;

		delete temp;

		Size--;
	}
	void clear() 
	{
		while (Size)
		{
			pop();
		}
	}
	Binary GetLast() 
	{
		Node* current = this->head;
		return current->data;
	}
};

class SignStackList {
private:
	class Node
	{
	public:
		Node* pNext;
		string data;

		Node(string data, Node* pNext = nullptr)
		{
			this->data = data;
			this->pNext = pNext;

		}
	};
	int Size;
	Node* head;

public:
	SignStackList()
	{
		Size = 0;
		head = nullptr;
	}

	~SignStackList()
	{
		clear();
	}
	void push(string data)
	{
		head = new Node(data, head);
		Size++;
	}

	int GetSize() { return Size; }

	void pop()
	{
		Node* temp = head;

		head = head->pNext;

		delete temp;

		Size--;
	}
	void clear()
	{
		while (Size)
		{
			pop();
		}
	}

	string GetLast()
	{
		Node* current = this->head;
		return current->data;
	}
};

class Calculator 
{
private:
	string expression; 
public:
	Calculator(string expr)
	{
		expression = checkInput(expr); 
	}
	string checkInput(string expr)
	{
		string result;

		for (int i = 0; i < expr.length(); i++) {
			if ((isdigit(expr[i]) == false) && (expr[i] != '+') && (expr[i] != '-') && (expr[i] != '*') && (expr[i] != ' ')) 
			{
				cout << "Incorrect input.Try again:" << endl;
				getline(cin, expr);
				continue;
			}
		}

		if (expr[0] == ' ') expr.erase(0, 1); 
		if (expr[expr.length() - 1] == ' ') expr.erase(expr.length() - 1, 1); 


		string str_in = expr;
		string str_out = "";
		bool b = false;
		for (int i = 0; i < str_in.length(); i++) { 
			if (str_in[i] == ' ') {
				if (b)  continue;
				b = true;
			}
			else
				b = false;
			str_out += str_in[i];
		}
		return str_out;
	}

	Binary calculateRPN() 
	{
		BinaryStackList binLst; 
		SignStackList signLst; 
		

		cout << "expression >> " << expression << endl;
		
		string num = "";
		for (int i = 0; i < expression.length(); i++) 
		{
			string temp = "";
			if (expression[i] != '+' && expression[i] != '-' && expression[i] != '*' && expression[i] != ' ') 
			{
				num += expression[i]; 
			}
			if (expression[i] == ' ') 
			{
				if (num != "") 
				{
					Binary b(stoi(num)); 
					binLst.push(b);

				}
				num = "";
			}
			if (expression[i] == '-') 
			{
				if (i + 1 <= expression.length() - 1)
				{
					if (expression[i + 1] != ' ')
					{
						num += "-";
						continue; 
					}
				}
			}
			if (expression[i] != '+' || expression[i] != '-' || expression[i] != '*') 
			{
				temp = expression[i];
				if (temp == "+" || temp == "-" || temp == "*") 
				{
					signLst.push(temp); 

					if (signLst.GetSize() == 1 && binLst.GetSize() > 1)
					{
						string current = "";
						current = signLst.GetLast();

						if (current == "-") 
						{
							Binary a = binLst.GetLast(); 
							binLst.pop(); 
							Binary b = binLst.GetLast();
							binLst.pop();
							binLst.push(b - a);
							signLst.pop();
							current = "";
							cout << b.convertToDecimal() << " " << temp << " " <<  a.convertToDecimal() << " = ";
							cout << binLst.GetLast().convertToDecimal() << "; number in binar: ";
							binLst.GetLast().print();

							

						}
						if (current == "+")
						{
							Binary a = binLst.GetLast();
							binLst.pop();
							Binary b = binLst.GetLast();
							binLst.pop();

							binLst.push(a + b);
							signLst.pop();

							current = "";

							cout << a.convertToDecimal() << " " << temp << " " << b.convertToDecimal() << " = ";
							cout << binLst.GetLast().convertToDecimal() << "; number in binar: ";
							binLst.GetLast().print();
						}
						if (current == "*")
						{

							Binary a = binLst.GetLast();
							binLst.pop();

							Binary b = binLst.GetLast();
							binLst.pop();

							Binary result = a * b;


							binLst.push(result);
							signLst.pop();

							current = "";

							cout << a.convertToDecimal() << " " << temp << " " << b.convertToDecimal() << " = ";
							cout << binLst.GetLast().convertToDecimal() << "; number in binar: ";
							binLst.GetLast().print();
						}
					}

				}

			}
		}
		if ((binLst.GetSize() == 1) && (signLst.GetSize() == 0))
		{
			return binLst.GetLast();
		}
		else {
			cout << "\nIncorrect expression !!!" << endl;
		}
	}
};

int main() {
	string input;
	getline(cin, input);
	Calculator value(input);
	Binary result = value.calculateRPN();
	cout << "\nFinal answer: " << result.convertToDecimal() << endl;
	result.print();
	return 0;
}
