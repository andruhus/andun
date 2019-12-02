#include <iostream>
using namespace std;

// this function enter int the array of chars char by char
char* enterchar(char* a, int& n)
{
	n++;
	char* b = new char[n];
	for (int i = 0; i < n - 1; i++)
	{
		b[i] = a[i];
	}
	cin >> b[n - 1];
	if ((int)b[n - 1] == 48 )
		return a;
	else
		delete[] a;
	return enterchar(b,n);
}





// this function helps me to compare substrings
bool substr_compare(char* a, char* b, int n,int step)
{
	bool t = true;
	for (int i = 0; i < n && t; i++)
	{
		if (a[i] != b[i+step])
			t = false;
	}
	return t;
}

void laba4()
{
	
	
	// we are entering the string a (n - its length)
	cout << "Enter the a-string" << endl;
	char* a = new char[0];
	int n = 0;
	cout << "The character '0' means the end of the string" << endl;
	a = enterchar(a, n);
	cout << endl;

	// we are entering the string b (m - its length)
	cout << "Enter the b-string" << endl;
	char* b = new char[0];
	int m = 0;
	cout << "The character '0' means the end of the string" << endl;
	b = enterchar(b, m);
	
	
	cout << endl;
	

	// we want string a to be not longer than string b
	if (n > m)
	{
		char* t = a;
		a = b;
		b = t;
		int z = n;
		n = m;
		m = z;
	}


	
	bool Exists = 0;
	// we verify the length of substring
	for (int i = n - 1; i > 0; i--)
	{
		
		char* substr = new char[i];
		// we verify the start of substring
		for (int j = 0; j < n - i; j++)
		{
			
			// we created a substring from a
			for (int k = j; k < j + i; k++)
			{
				substr[k-j] = a[k];
			}

			// now we check whether this substring exists in b
			for (int jb = 0; jb < m - i + 1; jb++)
			{
				if (substr_compare(substr, b, i, jb))
				{
					Exists = 1;
					break;
				}
			}

			// if it exists we output this substring
			if (Exists)
			{
				cout << "The mutual string is: ";
				for (int q = 0; q < i; q++)
					cout << substr[q];
				return;
			}
		}
	}
	cout << "There is no mutual substring";
}





// this function reads the matrix by spirale
void gity(char** a, int n, int q)
{
	for (int i = q; i < n - q; i++)
		cout << a[q][i] << " ";

	for (int i = q + 1; i < n - q; i++)
		cout << a[i][n - 1 - q] << " ";

	for (int i = n - 2 - q; i >= q; i--)
		cout << a[n - 1 - q][i] << " ";

	for (int i = n - 2 - q; i >= q + 1; i--)
		cout << a[i][q] << " ";
	q++;
	if (q < n / 2)
		gity(a, n, q);
	else
		return;
}


void laba4n()
{
	// entering part
	cout << "Enter the string, which will be converted in the table (it will end with entering char '0')" << endl;
	char* a = new char[0];
	int n = 0;
	a = enterchar(a, n);


	// enter size of the square matrix
	char g;
	int z;
	cout << "Now enter the side of the square: ";
	cin >> g;
	if (!isdigit(g))
		z = (int)g;
	else
		z = (int)g - 48;
	cout << "If we don`t have enough elements it will be filled by zeros" << endl;

	// now we fill the matrix
	char** b = new char* [z];
	for (int i = 0; i < z; i++)
	{
		b[i] = new char[z];
	}

	for (int i = 0; i < z; i++)
	{
		for (int j = 0; j < z; j++)
		{
			if (n > 1)
			{
				n--;
				b[i][j] = *a;
				a++;
			}
			else
			{
				b[i][j] = '0';
			}
		}
	}

	for (int i = 0; i < z; i++)
	{
		for (int j = 0; j < z; j++)
			cout << b[i][j] << " ";
		cout << endl;
	}


	cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
	// getting the result
	gity(b, z, 0);
	if (z % 2 == 1)
	{
		cout << b[z / 2][z / 2];
	}




}