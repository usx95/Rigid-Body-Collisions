#include "help.h"
#include "RigidBody.h"
#include "RigidBodySystem.h"
#include "math2D.h"
extern RigidBodySystem System;

class InputHandler{
public: 
	void keyboard(unsigned char key, int x, int y);
	void mouseClick(int button, int state, int x, int y);
	void mousePassiveMotion(int x, int y);
	void mouseActiveMotion(int x, int y);
	Vector2D WindowToOrthogonal(Vector2D a);
};
extern InputHandler handleInput;
