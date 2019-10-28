
#include "labsush.h"
#include "laba3h.h"
#include <math.h>
#include <iostream>
#include <string>
using namespace std;


void laba3()
{
	// we introduce n - the power and e - the input number
	int n;
	float e;
	cout << "Enter the power: ";
	cin >> n;
	cout << "Enter the number: ";
	cin >> e;
	
	// res is our result
	float res = 0;
	// l is the accuracy
	int l = log(e) - 1;
	
	
	while (13 > l)
	{

		int y = 1;
		while (e >= pow(res + y/pow(10,l), n))
		{
			y++;
		}
		res += (float)(y - 1) / pow(10, l);
		l++;
	}
	cout << res << endl;
}


bool AreClose(float x, float y)
{
	return abs(x - y) < 0.1;
}


// this function takes the function, staring point x0, ending point xend, and a step(or accuracy)
bool IsPeriodic(float(*func)(float), float x0,float xend, float step)
{
	// xcurr - the first element when func(xcurr) == func(x0)
	
	float xcurr = x0 + step;
	while (xcurr < xend && !AreClose(func(xcurr),func(x0)))
	{
		xcurr += step;
	}
	// it means that we did not find any element when func(xcurr) == func(x0)
	if (xcurr >= xend)
	{ 
		return false;
	}
	else
		for (float c = xcurr + step; c < xend; c += step)
			if (!AreClose(func(c) , func(c - xcurr + x0)))
				return false;
	return true;
}


void laba3n()
{
	// a 
	string a;
	cin >> a;
	float x0, xend, step;
	cin >> x0 >> xend;
	step = 0.1;
	bool t = true;
	if (a == "sin")
		t = IsPeriodic(sinus, x0, xend, step);
	else if (a == "cos")
		t = IsPeriodic(cosinus, x0, xend, step);
	else if (a == "lin")
		t = IsPeriodic(linear, x0, xend, step);
	else if (a == "fra")
		t = IsPeriodic(fract, x0, xend, step);
	else if (a == "pow4")
		t = IsPeriodic(power4, x0, xend, step);
	else
		cout << "as we do not know this very function, ";

	if (t)
		cout << "it is maybe a periodic function" << endl;
	else
		cout << "it is defintely not a periodic function or it has a large period" << endl;
	
}
