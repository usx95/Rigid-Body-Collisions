#include "Camera.h"
Camera camera;
void Camera::init(){
	CameraPosition = {MAX_X/2,MAX_Y/2,1000};
	LookingAt = {MAX_X/2,MAX_Y/2,0};
	LineOfSight = (LookingAt - CameraPosition).unit();
}
void Camera::alignObject(){
	gluLookAt(CameraPosition.x,CameraPosition.y,CameraPosition.z,
				LookingAt.x,LookingAt.y,LookingAt.z,
				0,1,0);
}
void Camera::movePosition(unsigned char &c){
	switch(c){
		case 'w':
			CameraPosition = CameraPosition + LineOfSight.unit() * 10;
			break;
		case 's':
			CameraPosition = CameraPosition - LineOfSight.unit() * 10;
			break;
	}
	printf("Camera = (%0.2f,%0.2f,%0.2f)\n",CameraPosition.x,CameraPosition.y,CameraPosition.z);
}
void Camera::changeLookAt(int x,int y){
	LookingAt = LookingAt + Vector2D(x,y,0);//wrong
	LineOfSight = (LookingAt - CameraPosition).unit();
}
