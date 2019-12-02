#include <iostream>
using namespace std;

static char* enterchar(char* a, int& n)
{
	n++;
	char* b = new char[n];
	for (int i = 0; i < n - 1; i++)
	{
		b[i] = a[i];
	}
	cin >> b[n - 1];
	if (b[n - 1] == 'e')
		return b;
	else
		delete[] a;
	return enterchar(b, n);
}


int mult(int x, int y)
{
	return x * y;
}
int rest(int x, int y)
{
	return x % y;
}
int divs(int x, int y)
{
	return x / y;
}
int powr(int x, int y)
{
	int k = 1;
	for (int i = 0; i < y; i++)
		k *= x;
	return k;
}



void laba5()
{
	// entering part
	cout << "Enter the string which can be translated(end by 'e', separate by ',' , enter only positive numbers)" << endl;
	char* a = new char[0];
	int n = 0;
	a = enterchar(a, n);


	// x[2] - is an array where x[0] is the future result of the executing x[1] is a number which changes the result
	int x[2] = {-987,-987};
	// temporary will form the x[1]
	int temporary = 0;
	int (*f) (int,int) = nullptr;

	// lets read char by char
	for (int i = 0; i < n; i++)
	{
		// if the char is unknown the expression is incorrect
		if (a[i] != ',' && a[i] != '*' && a[i] != 'e' && a[i] != '/' && a[i] != '%' && a[i] != '^' && a[i] != '-' && a[i] != '+' && !isdigit(a[i]))
		{
			cout << "The expression is incorrect" << endl;
			return;
		}

		// if it is digit it will change the temporary
		if (isdigit(a[i]))
		{
			temporary *= 10;
			temporary += (int)a[i] - 48;
		}


		// if it is a separchar we will do the next block of code
		if (a[i] == ',')
		{
			// if the srearchar will be first the expression is invalid
			if (i == 0 || (i>1 && a[i - 2] != ','))
			{
				cout << "The expression is incorrect" << endl;
				return;
			}

			


			// if the previous char was digit we will form the x[1] (or x[0] if it is undefined)
			if (isdigit(a[i - 1]))
			{
				if (x[0] == -987)
				{
					x[0] = temporary;
				}
				else
					x[1] = temporary;
				temporary = 0;

			}


			// if the previous char was an operator we will execute the x[0]
			else
			{
				switch (a[i-1])
				{
				case '*': f = mult; break;
				case '%': f = rest; break;
				case '/': f = divs; break;
				case '^': f = powr; break;
				case '+': break;
				case '-': x[1] *= -1; break;
				default: cout << "The expression is incorrect" << endl; return;
				}
				if(a[i-1] != '-' && a[i-1] != '+')
					x[0] = f(x[0], x[1]);
			}
		}


		// if it is the end we will look into the previous operator
		if (a[i] == 'e')
		{


			// if the expression is empty it wont be valid
			if (i == 0 || (i > 1 && a[i - 2] != ','))
			{
				cout << "The expression is incorrect" << endl;
				return;
			}
			// the previous operator will finish our execution 
			if (isdigit(a[i - 1]))
			{
				if (x[0] == -987)
				{
					x[0] = temporary;
				}
				else
					x[1] = temporary;
				temporary = 0;

			}
			else
			{
				switch (a[i - 1])
				{
				case '*': f = mult; break;
				case '%': f = rest; break;
				case '/': f = divs; break;
				case '^': f = powr; break;
				case '+': break;
				case '-': x[1] *= -1; break;
				default: cout << "The expression is incorrect" << endl; return;
				}
				if (a[i - 1] != '-')
					x[0] = f(x[0], x[1]);
			}
		}
	}


	// output part
	cout << x[0] << endl;

	
}