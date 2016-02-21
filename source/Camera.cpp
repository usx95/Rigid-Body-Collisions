#include "camera.h"
#include "math.h"
#include <iostream>
#include "windows.h"

CCamera::CCamera()
{
	//Init with standard OGL values:
	Position = Vector2D (	0.0, 
							0.0,
							0.0);
	ViewDir = Vector2D(	0.0,
							0.0,
							-1.0);
	ViewDirChanged = false;
	//Only to be sure:
	RotatedX = RotatedY = RotatedZ = 0.0;
	
	CameraT.Move( Vector2D(0.0, 0.0, 3.0 ));
	CameraT.MoveForwards( 1.0 );
	
}
Vector2D CCamera::getPosition(){
	return Position;
}
Vector2D CCamera::GetViewDir( void ){
	if (ViewDirChanged) CalcViewDir();
	return ViewDir;
}
void CCamera::CalcViewDir( void )
{
	Vector2D Step1, Step2;
	//Rotate around Y-axis:
	Step1.x = cos( (RotatedY + 90.0) * PIdiv180);
	Step1.z = -sin( (RotatedY + 90.0) * PIdiv180);
	//Rotate around X-axis:
	double cosX = cos (RotatedX * PIdiv180);
	Step2.x = Step1.x * cosX;
	Step2.z = Step1.z * cosX;
	Step2.y = sin(RotatedX * PIdiv180);
	//Rotation around Z-axis not yet implemented, so:
	ViewDir = Step2.unit();
	ViewDirChanged = false;
}
void CCamera::Move (Vector2D Direction)
{
	Position = Position + Direction;
}

void CCamera::RotateY (GLfloat Angle)
{
	RotatedY += Angle;
	ViewDirChanged = true;
}

void CCamera::RotateX (GLfloat Angle)
{
	RotatedX += Angle;
	ViewDirChanged = true;
}

void CCamera::Render( void )
{
	glRotatef(-RotatedX , 1.0, 0.0, 0.0);
	glRotatef(-RotatedY , 0.0, 1.0, 0.0);
	glRotatef(-RotatedZ , 0.0, 0.0, 1.0);
	glTranslatef( -Position.x, -Position.y, -Position.z );
}

void CCamera::MoveForwards( GLfloat Distance )
{
	if (ViewDirChanged) CalcViewDir();
	Vector2D MoveVector;
	MoveVector.x = ViewDir.x * -Distance;
	MoveVector.y = ViewDir.y * -Distance;
	MoveVector.z = ViewDir.z * -Distance;
	Position = Position + MoveVector;
}

void CCamera::StrafeRight ( GLfloat Distance )
{
	if (ViewDirChanged) CalcViewDir();
	Vector2D MoveVector;
	MoveVector.z = -ViewDir.x * -Distance;
	MoveVector.y = 0.0;
	MoveVector.x = ViewDir.z * -Distance;
	Position = Position + MoveVector;
}
