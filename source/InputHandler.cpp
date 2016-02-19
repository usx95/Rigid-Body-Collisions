#include "help.h"
#include "math2D.h"
#include "InputHandler.h"
#include "windows.h"
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
    			System.sys[i].acceleration = {0,0};
    		}
    		break;
    	case 'g':
    		accGravity = 0;
    		for(int i=0;i<System.sys.size();++i){//something better
    			System.sys[i].acceleration = {0,0};
    		}
			break;
    	case 'p':
    		PATH_TRACE = 1 - PATH_TRACE;
    		for(int i=0;i<System.sys.size();++i){
    			System.sys[i].pathTrace.clear();
			}
			break;
   }
}
void InputHandler::mouseClick(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) { 
		Vector2D b = WindowToOrthogonal({x,y});
		System.addBody(RigidBody(b,50,10,{1,1}));
		cout<<b.x<<' '<<b.y<<endl;
	}

}
void InputHandler::mouseMotion(int x, int y) {
	Vector2D dir = Vector2D(x,y) - Vector2D(window_breadth/2,window_height/2);
if(dir.x!=0 or dir.y!=0)
printf("motion direction = (%0.2f,%0.2f)\n",dir.x,dir.y);
	glutPostRedisplay();
	glutWarpPointer(window_breadth/2,window_height/2);
}
Vector2D InputHandler::WindowToOrthogonal(Vector2D a){
	double x = a.x * (MAX_X/window_breadth);
	double y = (window_height - a.y) * (MAX_Y/window_height);
	return {x,y};
}

