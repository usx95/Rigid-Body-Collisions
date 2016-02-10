#pragma once
#include "help.h"

class Vector2D{
	public:
	double x,y;
	Vector2D(double,double);
	Vector2D();
	Vector2D(int,int);
	
	Vector2D operator+(Vector2D);
	Vector2D operator-(Vector2D);
	double operator*(Vector2D);
	
	Vector2D operator*(double);
	Vector2D operator/(double);

	double norm();
	Vector2D unit();
	
};
class math2D{
public:
	int genRand(int L,int R);
};
