#include "help.h"
#include "InputHandler.h"

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
    		break;
    	case 'g':
    		for(int i=0;i<System.sys.size();++i){
    			System.sys[i].acceleration = {0,0};
    		}
			break;
    	default:
    		System.addBody(RigidBody({x,y},50,10,{100,1}));
   }
}
void InputHandler::mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) { 
		cout<<x<<' '<<y<<endl;
	}
}
