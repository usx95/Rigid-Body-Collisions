#pragma once
#include "help.h"
#include "math2D.h"

class RigidBody{
	
public:
	
	Vector2D centre;
	double radius, mass;
	Vector2D velocity;
	Vector2D acceleration;
	
	
	RigidBody(Vector2D c,double r,double m,Vector2D v,Vector2D a);
	void BoundaryCollisionCheck();
	void nextSimulation();
	void display();
	double getEnergy();
	Vector2D getLinearMomentum();
};
