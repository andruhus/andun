#include <iostream>
#include <math.h>
#include "labsush.h"
using namespace std;



void laba1()
{
	// n,k - input
	int n, k;
	cin >> n >> k;

	// n and k must be more or equal than zero
	if (k < 0 || n < 0)
	{
		k = abs(k);
		n = abs(n);
	}

	// and n must be more than k
	if (n - k < 0)
	{
		int v = n;
		n = k;
		k = v;
	}

	// c is our result
	long long int c = 1;

	// lets return our c into the output
	for (long long int i = 1; i <= n - k; i++)
	{
		c *= (k + i);
		c /= i;
	}
	cout << c << endl;

}

bool Ost_po_Ferma(int i, long long a)
{
	// the function is based on the Small Theorem of Ferma
	int o = i;
	for (int j = 1; j < a-1; j++)
	{
		o *= i;
		o = o % a;
	}
	return o % a == 1;
}

void laba1n()
{
	// the input a is the applicant of carlmichael number
	long long int a;
	cout << "Enter yuor number: ";
	cin >> a;


	// if a is even it wont be the carlmichael number
	if (a % 2 == 0) cout << 0;

	// Neprost will show us that a is not a prime
	// Karlm will show us that a follows the pattern
	// res (result) is intersection of Neprost and Karlm
	bool Neprost = 0;
	bool Karlm = 0;
	bool res = 0;
	

	// lets start our cycle
	for (int i = 3; i < sqrt(a); i += 2)
	{
		// if we found the devisor of a, it wont be a prime
		if (a % i == 0)
			Neprost = 1;


		// then if you want to check if the a^i - a === 0(mod i) 
		if (!Karlm && ((a % i) != 0))
			Karlm = Ost_po_Ferma(i, a);
	}


	// now look at the res
	res = Karlm && Neprost;

	// the output
	if (res)
		cout << "It is the Karlmichael number" << endl;
	else
		cout << "It is not the Karlmichael number" << endl;

}


