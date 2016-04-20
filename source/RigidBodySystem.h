#pragma once

#include "help.h"
#include "RigidBody.h"

class RigidBodySystem{
public:
	double SystemEnergy;
	vector<RigidBody>sys;
	void addBody(RigidBody);
	void display();
	void drawGrid();
	void drawFaces();
	pair<Vector2D,Vector2D>  resVelocity(RigidBody&, RigidBody&);
	void collisionResolution();
	void GravitationalAcceleration();
	bool DetectCollision(RigidBody &, RigidBody &);
	void ResolveCollison(RigidBody &, RigidBody &);
	
	void BuildBuilding(int N,int M,int O);
	void BuildPyramid();
	void BuildTiltedSheet();
	void CircularStarSystem(int N);
	void BinaryStar();
	void conservation();
};
