#include "help.h"
#include "math2D.h"
#include "InputHandler.h"
#include "windows.h"
#include "Camera.h"
InputHandler handleInput;
void InputHandler::keyboard(unsigned char key, int x, int y) {
	switch (key) {
    	case 27:     // ESC key
        	exit(0);
         	break;
    	case ' ':
    		pause_and_view = !pause_and_view;
    		break;
    	case 'h':
			HEAVENLY_BODY = 1 - HEAVENLY_BODY;
    		for(int i=0;HEAVENLY_BODY==0 and i<System.sys.size();++i){
    			System.sys[i].acceleration = {0,0,0};
    		}
    		break;
    	case 'g':
    		accGravity = 0;
    		for(int i=0;i<System.sys.size();++i){//something better
    			System.sys[i].acceleration = {0,0,0};
    		}
			break;
    	case 'p':
    		PATH_TRACE = 1 - PATH_TRACE;
    		for(int i=0;i<System.sys.size();++i){
    			System.sys[i].pathTrace.clear();
			}
			break;
		case 'w':;
		case 'a':;
		case 's':;
		case 'd':
			camera.movePosition(key);
			break;
   }
   glutPostRedisplay();
}
void InputHandler::mouseClick(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) { 
		Vector2D b = WindowToOrthogonal({x,y,0});
		System.addBody(RigidBody(b,50,10,{rand()%10*1.0,rand()%10 * 1.0,rand()%100 * 1.0}));
		cout<<b.x<<' '<<b.y<<'\n';
	}
	glutPostRedisplay();
}
void InputHandler::mouseActiveMotion(int x, int y) {
	Vector2D dir = Vector2D(x,y,0) - Vector2D(window_breadth/2,window_height/2,0);
//	camera.changeLookAt(x-window_breadth/2,y-window_height/2);
	//glutWarpPointer(window_breadth/2,window_height/2);
	glutPostRedisplay();
}
void InputHandler::mousePassiveMotion(int x, int y) {
}
Vector2D InputHandler::WindowToOrthogonal(Vector2D w){
	double x = w.x * (MAX_X*1.0/window_breadth);
	double y = (window_height - w.y) * (MAX_Y*1.0/window_height);
	return Vector2D(x,y,0.0);
}

