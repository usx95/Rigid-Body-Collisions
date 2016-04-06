#pragma once
#include "help.h"

class Vector2D{
	public:
	double x,y,z;
	Vector2D(double,double,double);
	Vector2D();
	Vector2D(int,int,int);
	
	Vector2D operator+(Vector2D);
	Vector2D operator-(Vector2D);
	double operator*(Vector2D);
	
	Vector2D operator*(double);
	Vector2D operator/(double);
	Vector2D cross(Vector2D a);
	double norm();
	Vector2D unit();
};

class math2D{
public:
	int genRand(int L,int R);
};
