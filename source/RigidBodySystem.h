#pragma once

#include "help.h"
#include "RigidBody.h"

class RigidBodySystem{
public:
	double SystemEnergy;
	vector<RigidBody>sys;
	void addBody(RigidBody);
	void display();
	pair<Vector2D,Vector2D>  resVelocity(RigidBody&, RigidBody&);
	void collisionResolution();
	bool DetectCollision(RigidBody &, RigidBody &);
	void ResolveCollison(RigidBody &, RigidBody &);
	
	void conservation();
};
