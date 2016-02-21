#include "help.h"
#include "math2D.h"

class Camera{
public:
	Vector2D CameraPosition, LookingAt, LineOfSight;

	void init();
	void alignObject();
	void movePosition(unsigned char &c);
	void changeLookAt(int,int);
};
extern Camera camera;
