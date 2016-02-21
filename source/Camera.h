#include <gl\glut.h>
#include "math2D.h"
#define PIdiv180 3.1415265359/180.0

class CCamera
{
private:
	Vector2D Position;
	Vector2D ViewDir;		/*Not used for rendering the camera, but for "moveforwards"
							So it is not necessary to "actualize" it always. It is only
							actualized when ViewDirChanged is true and moveforwards is called*/
	bool ViewDirChanged;
	GLfloat RotatedX, RotatedY, RotatedZ;
public:
	CCamera();				//inits the values (Position: (0|0|0) Target: (0|0|-1) )
	void Render ( void );	//executes some glRotates and a glTranslate command
							//Note: You should call glLoadIdentity before using Render
	void Move ( Vector2D Direction );
	void RotateX ( GLfloat Angle );
	void RotateY ( GLfloat Angle );
	void RotateZ ( GLfloat Angle );
	void RotateXYZ ( Vector2D Angles );
	void MoveForwards ( GLfloat Distance );
	void StrafeRight ( GLfloat Distance );
	Vector2D getPosition();	
	Vector2D GetViewDir ( void );
	void CalcViewDir ( void );
};

extern CCamera CameraT;
