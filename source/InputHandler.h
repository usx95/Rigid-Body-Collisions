#include "help.h"
#include "RigidBody.h"
#include "RigidBodySystem.h"

extern RigidBodySystem System;

class InputHandler{
public: 
	void keyboard(unsigned char key, int x, int y);
	void mouse(int button, int state, int x, int y);
	Vector2D WindowToOrthogonal(Vector2D a);
};

