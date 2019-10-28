
#include "labsush.h"
#include <math.h>
#include <iostream>
#include <string>
using namespace std;





int main()
{
	int y;
	char er;
	cout << "Hello in my labworks" << endl;
	cout << "Choose the number of a lab: ";
	cin >> y;
	switch(y)
	{
	case 1: cout << "An easy or diffcult one? "; cin >> er; 
		if(er == 'e') laba1();
		if(er == 'd') laba1n();
		break;
	case 2: cout << "An easy or diffcult one? "; cin >> er;
		if(er == 'e') laba2();
		if (er == 'd') laba2n();
		break;
	case 3: cout << "An easy or diffcult one? "; cin >> er;
		if (er == 'e') laba3();
		if (er == 'd') laba3n();
		break;
	}
	
	return 0;
}

