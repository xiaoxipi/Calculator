#pragma once

#include"stack.h"

class Calculator
{
public:
	void Run();
private:
	LinkStack<double> OPND;
	LinkStack<char>  OPTR;
	//int isp(char op);
	//int icp(char op);
	void Internal();
	double DoOperator(double x, char op, double y);
	char GetChar();
	double GetNumber();
	bool IsOperator(char ch);
};

double Calculator::DoOperator(double x, char op, double y)
{
	switch (op)
	{
	case '+':
		return x + y;
	case '-':
		return x - y;
	case '*':
		return x*y;
	case '/':
		if (y == 0)
		{
			cout << "³ýÊýÎªÁã" << endl;
			exit(1);
		}
		else
			return x / y;
	default:
		exit(2);
	}
}

char Calculator::GetChar()
{
	char ch = cin.get();
	return ch;
}

bool Calculator::IsOperator(char ch)
{
	if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' || ch == ')'||ch=='\n')
		return true;
	else
	{
		cin.putback(ch);
		return false;
	}
}

double Calculator::GetNumber()
{
	char ch = cin.get();
	double num = double(ch - 48);
	ch = cin.get();
	bool greatorone = true;
	int decimal_number = 0;
	while ((ch >= '0'&&ch <= '9') || ch == '.')
	{
		if (ch >= '0'&&ch <= '9')
		{
			if (greatorone == true)
			{
				num = num * 10 + double(ch - 48);
			}
			else
			{
				num = num + (ch-48)*pow(10, -(decimal_number));
				decimal_number++;
			}
		}
		else
		{
			if (greatorone == false)
				exit(4);
			greatorone = false;
			decimal_number = 1;
		}
		ch = cin.get();
	}
	cin.putback(ch);
	return num;
}

void Calculator::Internal()
{
	char ch = cin.get();
	while (!(ch=='\n'))
	{
		if (!IsOperator(ch))
		{
			double tmp = GetNumber();
			OPND.Push(tmp);
		}
		else
		{
			if (ch == '+' || ch == '-')
			{
				char  near = cin.get();
				if (near == '+' || near == '-' || near == '*' || near == '/'||near==')')
					exit(8);
				cin.putback(near);
				OPTR.Push(ch);
			}
			else if (ch == '(')
			{
				char  near = cin.get();
				if (near == '+' || near == '-' || near == '*' || near == '/')
					exit(8);
				cin.putback(near);
				OPTR.Push(ch);//
				Internal();
			}
			/*else if (ch == ')' || ch == '\n')
			{
				if (ch == '\n')
				{
					cin.putback(ch);
				}
				do
				{
					char near = OPTR.Pop();
					if (near == NULL || near == '(')
						return;
					else
					{
						double num1, num2;
						num2 = OPND.Pop();
						num1 = OPND.Pop();
						double tmp = DoOperator(num1, near, num2);
						OPND.Push(tmp);
					}
				} while (1);
			}*/
			/*else if (ch == '\n')
			{
				cin.putback(ch);
				do
				{
					char near = OPTR.Pop();
					if (near == NULL)
						return;
					else if (near == '(')
						exit(6);
					else
					{
						double num1, num2;
						num2 = OPND.Pop();
						num1 = OPND.Pop();
						double tmp = DoOperator(num1, near, num2);
						OPND.Push(tmp);
					}
				} while (1);
			}*/
			else if (ch == ')')
			{
				do
				{
					char near = OPTR.Pop();
					if (near == '(')
						return;
					else if (near == NULL)
						exit(7);
					else
					{
						double num1, num2;
						num2 = OPND.Pop();
						num1 = OPND.Pop();
						double tmp = DoOperator(num1, near, num2);
						OPND.Push(tmp);
					}
				} while (1);
			}
			else if (ch == '*' || ch == '/')
			{
				char  near1 = cin.get();
				if (near1 == '+' || near1 == '-' || near1 == '*' || near1 == '/' || near1 == ')')
					exit(9);
				cin.putback(near1);
				char near = cin.get();
				if (near == '(')
				{
					OPTR.Push(near);
					Internal();
					double num1, num2;
					num2 = OPND.Pop();
					num1 = OPND.Pop();
					double tmp = DoOperator(num1, ch, num2);
					OPND.Push(tmp);
				}
				else
				{
					cin.putback(near);
					double num1, num2;
					num1 = OPND.Pop();
					num2 = GetNumber();
					double tmp = DoOperator(num1, ch, num2);
					OPND.Push(tmp);
				}
			}
			else
				exit(3);
		}
		ch = cin.get();
	}
	do
	{
		char near = OPTR.Pop();
		if (near == NULL)
			return;
		else if (near == '(')
			exit(6);
		else
		{
			double num1, num2;
			num2 = OPND.Pop();
			num1 = OPND.Pop();
			double tmp = DoOperator(num1, near, num2);
			OPND.Push(tmp);
		}
	} while (1);
}

void Calculator::Run()
{
	Internal();
	if (OPTR.Empty())
	{
		if (OPND.Length() == 1)
		{
			cout << OPND.Top() << endl;
			return;
		}
	}
	cout << "Wrong!" << endl;
}

