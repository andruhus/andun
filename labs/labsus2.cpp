#include "labsush.h"
#include <math.h>
#include <iostream>
using namespace std;

void vved(float& x1, float& y1, float& x2, float& y2, float& x3, float& y3, float& ang)
{
	// Three coordinants are being entered
	cout << "Enter point A: ";
	cin >> x1 >> y1;
	cout << "Enter point B: ";
	cin >> x2 >> y2;
	cout << "Enter point C: ";
	cin >> x3 >> y3;
	cout << "Enter the Angle in gradus: ";
	cin >> ang;


	// Now turn the angle into radians and ang º [0, 2*pi]
	float pi = atan(1) * 4.0;
	ang = ang/180.0 * pi;
	while (ang > 2.0 * pi)
		ang -= 2.0 * pi;


}


void turn_right(float x[2], float ang)
{
	// the input is the vector and an angle on which we will turn


	//lets introduce u as a module of the vectors
	float u = sqrt((x[0] * x[0]) + (x[1] * x[1]));

	// we need number pi
	float pi = atan(1) * 4.0;

	// lets introduce the vec_ang - the angle between the vector and OX
	float vec_ang;
	
	// if x[1] -> 0, we will have some problems
	if (abs(x[0]) < 0.1)
	{
		if (x[1] >= 0) vec_ang = pi / 2.0;
		else vec_ang = 3.0 * pi / 2.0;
		cout << vec_ang << endl;
		vec_ang -= ang;
		x[0] = u * cos(vec_ang);
		x[1] = u * sin(vec_ang);
		return;
	}
	
	// if x[1] -/> 0 we will go by the main algorythm
	if (x[0] >= 0) vec_ang = atan(x[1] / x[0]);
	else vec_ang = atan(x[1] / x[0]) + pi;
	cout << vec_ang << endl;
	vec_ang -= ang;
	x[0] = u * cos(vec_ang);
	x[1] = u * sin(vec_ang);

}


float dist(float x1, float x2, float y1, float y2)
{
	// it is distance between 2 ponts
	float g = x2 - x1;
	float z = y2 - y1;
	return sqrt(g * g + z * z);
}


void laba2()
{
	float x1, y1, x2, y2, x3, y3, ang;
	float ab, bc, ac;

	// we will make the user enter the coordinates till he enters the triangle points(triangle inequality)
	do
	{
		vved(x1, y1, x2, y2, x3, y3, ang);
		ab = dist(x1, x2, y1, y2);
		bc = dist(x2, x3, y2, y3);
		ac = dist(x1, x3, y1, y3);
	} while (ab + bc <= ac || ab + ac <= bc || bc + ac <= ab);


	// O is the centroid
	float xo, yo;
	xo = x1 + x2 + x3;
	xo /= 3.0;
	yo = y1 + y2 + y3;
	yo /= 3.0;
	cout << "The centroid is: " << xo << " " << yo << endl;


	// the next objects are the OA, OB, OC vectors
	float vect_ao[2] = { x1 - xo,y1 - yo };
	float vect_bo[2] = { x2 - xo,y2 - yo };
	float vect_co[2] = { x3 - xo,y3 - yo };


	// turn the vectors
	turn_right(vect_ao, ang);

	turn_right(vect_bo, ang);

	turn_right(vect_co, ang);


	// now we output the points
	cout << "A`: x = " << xo + vect_ao[0] << "; y = " << yo + vect_ao[1] << endl;
	cout << "B`: x = " << xo + vect_bo[0] << "; y = " << yo + vect_bo[1] << endl;
	cout << "C`: x = " << xo + vect_co[0] << "; y = " << yo + vect_co[1] << endl;

}







// This function finds the coordinates of two crossing lines 
void crossline_pointfinder(float a1, float b1, float c1, float a2, float b2, float c2,float &t,float& y)
{
	float* op = new float[2];
	if (a1 / a2 == b1 / b2) return;
	if (b1 == 0)
	{
		if (a1 == 0) return;
		op[0] = -1.0 * c1 / a1;
		if (b2 == 0) return;
		op[1] = -1.0 * ((op[0] * a2 + c2) / b2);
	}
	else
	{
		op[0] = (c1 * b2 / b1 - c2) / (a2 - a1 * b2 / b1);
		op[1] = -1.0 * ((op[0] * a1 + c1) / b1);
	}
	t = op[0];
	y = op[1];

}


// This function gives the coordinates of the middle point between two given points
float* mid_point(float p1[2], float p2[2])
{
	float* op = new float[2];
	op[0] = (p1[0] + p2[0]) / 2;
	op[1] = (p1[1] + p2[1]) / 2;
	return op;
}

// This function forms a line which is perpendicular to the two given points and their middle point(which we also give)
float* line_maker(float p1[2], float p2[2], float* pmid)
{
	float* op = new float[3];
	op[0] = p1[0] - p2[0];
	op[1] = p1[1] - p2[1];
	op[2] = (p2[0] - p1[0]) * pmid[0] + (p2[1] - p1[1]) * pmid[1];
	return op;
}


// This function forms a circle from three points 
void circulator(float p1[2],float p2[2], float p3[2], float&a,float& b,float& c)
{
	// the middle points of AB and AC
	float* point_midAB = mid_point(p1, p2);
	float* point_midAC = mid_point(p1, p3);

	// the middle perpendiculars of AB and AC
	float* lineAB = line_maker(p1, p2, point_midAB);
	float* lineAC = line_maker(p1, p3, point_midAC);

	// their crossing is the centre of our circle
	crossline_pointfinder(lineAB[0], lineAB[1], lineAB[2], lineAC[0], lineAC[1], lineAC[2],a,b);
	// and radius
	c = dist(a, p1[0], b, p1[1]);
}


// This function checks wheather the point is inside the circle
bool insidence(float a, float b, float c, float* u)
{
	bool t = pow(u[0] - a,2) + pow(u[1] - b,2) <= c*c;
	return t;
}


// it shows us which point we need to change
void choosing(int a,float p1[2],float p2[2],float p3[2], float pk[2])
{
	if (a == 1)
	{
		p1[0] = pk[0];
		p1[1] = pk[1];
	}
	else if (a == 2)
	{
		p2[0] = pk[0];
		p2[1] = pk[1];
	}
	else
	{
		p3[0] = pk[0];
		p3[1] = pk[1];
	}
}



void laba2n()
{
	// we need to know how many points we have to deal with
	int n;
	cout << "n is ";
	cin >> n;


	// then we introduce the "poligoncin" the 2-column matrix with length of n
	float** poligon = new float* [n];
	for (int i = 0; i < n; i++)
		poligon[i] = new float[2];


	// now we are entering the users` points
	for (int i = 0; i < n; i++)
	{
		cout << i + 1 << ") ";
		for (int j = 0; j < 2; j++)
		{
			cin >> poligon[i][j];
		}
	}


	// the a, b, c are the main characteristics of a circle
	// a is x-coordinate of the centre of the circle
	// b is y-coordinate of the centre of the circle
	// c is the radius of the circle
	float a = 0, b = 0, c = 0;


	// the circle has to pass at least 3 points of the poligon, the rest points have to be inside it
	// so p1, p2, p3 - are the points on which the circle is based on
	float p1[2] = { poligon[0][0], poligon[0][1] };
	float p2[2] = { poligon[1][0], poligon[1][1] };
	float p3[2] = { poligon[2][0], poligon[2][1] };
	

	// we forms the first circle
	circulator(p1, p2, p3, a, b, c);


	// for every point
	for (int i = 3; i < n; i++)
		// we check if it is outside the circle
		if (!insidence(a, b, c, poligon[i]))
		{
			// we introduce:
			// k is indicator which shows us which point we need to change on a new one
			int k = 3;
			// mr is minimal radius (we have to find the minimal radius by the task)
			float mr = -6754.09;
			// t shows us if every other point lies inside the circle
			bool t = 1;
			// a1, b1, c1 - temporary characteristics of the circle
			float a1 = 0, b1 = 0, c1 = 0;


			// we forms the 1-st temporary circle
			circulator(p1, p2, poligon[i], a1, b1, c1);

			// now check if it contains every examined point
			for (int y = 0; y < i; y++)
			{
				if(t) 
					t = insidence(a1,b1,c1,poligon[y]);
			}
			// if yes - we manipulate with mr
			if(t)
				mr = c1;

			t = 1;
			// we forms the 2-nd temporary circle
			circulator(p1, p3, poligon[i], a1, b1, c1);

			// now check if it contains every examined point
			for (int y = 0; y < i; y++)
			{
				if (t)
					t = insidence(a1, b1, c1, poligon[y]);
			}

			// if yes - we manipulate with mr
			if (t)
				if (c1 < mr || mr == -6754.09)
				{
					mr = c1;
					k = 2;
				}


			t = 1;
			// we forms the 3-rd temporary circle
			circulator(p3, p2, poligon[i], a1, b1, c1);

			// now check if it contains every examined point
			for (int y = 0; y < i; y++)
			{
				if (t)
					t = insidence(a1, b1, c1, poligon[y]);
			}

			// if yes - we manipulate with mr
			if (t)
				if (c1 < mr || mr == -6754.09)
				{
					mr = c1;
					k = 1;
				}



			// now we change the point on a new one
			choosing(k,p1,p2,p3,poligon[i]);

			// and get new circle
			circulator(p1, p2, p3, a, b, c);
		}




	// now lets output our result
	if (a >= 0 && b >= 0)
		cout << "Our circle: (x - " << a << ")^2 + (y - " << b << ")^2 = " << c * c << endl;
	else if (a < 0 && b >= 0)
		cout << "Our circle: (x + " << abs(a) << ")^2 + (y - " << b << ")^2 = " << c * c << endl;
	else if (a >= 0 && b < 0)
		cout << "Our circle: (x - " << a << ")^2 + (y + " << abs(b) << ")^2 = " << c * c << endl;
	else
		cout << "Our circle: (x + " << abs(a) << ")^2 + (y + " << abs(b) << ")^2 = " << c * c << endl;
	
}