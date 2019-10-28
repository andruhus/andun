
#include "laba3h.h"
#include <math.h>
#include <iostream>
using namespace std;

float linear(float x)
{
	return 35 * x + 5;
}

float sinus(float x)
{
	return sin(x);
}

float cosinus(float x)
{
	return cos(x);
}

float fract(float x)
{
	return x - (int)x;
}

float power4(float x)
{
	return pow(x, 4);
}

