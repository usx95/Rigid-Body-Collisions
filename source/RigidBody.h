#pragma once
#include "help.h"
#include "math2D.h"

class RigidBody{
	
public:
	
	Vector2D centre;
	double radius, mass;
	Vector2D velocity;
	Vector2D acceleration;
	deque<Vector2D>pathTrace;
	
	RigidBody(Vector2D c,double r,double m,Vector2D v);
	void BoundaryCollisionCheck();
	void nextSimulation();
	void display();
	double getEnergy();
	void printPathTrace();
	Vector2D getLinearMomentum();
};
