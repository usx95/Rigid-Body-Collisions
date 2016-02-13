#include "help.h"
#include "RigidBody.h"
#include "RigidBodySystem.h"
#include "math2D.h"
#include "Extras/ConfigFile.h"
#include "Extras/Chameleon.h"
RigidBodySystem System;
math2D math;

int HEAVENLY_BODY;

void Draw() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);

	System.display();
	
	glFlush();
	glutPostRedisplay();
}


void setGrid(){
	double rad = 35;
	int N = 10,M = 3;
	for(int j=1;j<=M;++j){
		for(int i=1;i<=N;++i){
			Vector2D c = {0.1 + 2*rad*i,rad*(3*j-1)};
			double mass = 1;
			Vector2D v = {0,0};
			if(i==N and j==M)mass*=30,v={500.0,0.0},c={rad*3 + 2*rad*N,rad},rad=0.3*rad;
			System.addBody(RigidBody(c,rad,mass,v,{0.0,0.0}));
		}
	}
//	System.addBody(RigidBody({800,700},20,10,{0,0},{0,0}));
//	System.addBody(RigidBody({800,800},20,10,Vector2D(1,0),{0,0}));
	
}
void Initialize() {
	setGrid();
	
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, Width, 0.0, Height, -1.0, 1.0);
}
void stub(){
	ConfigFile cf("config.txt");
	HEAVENLY_BODY = (cf.Value("section_1","HEAVENLY_BODY")).equals("ON") ? 1:0;
}

int main(int iArgc, char** cppArgv) {
	
	stub();
			
	glutInit(&iArgc, cppArgv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Rigid Body Simulations (@usaxena95)");
	Initialize();
	glutDisplayFunc(Draw);
	glutMainLoop();
	return 0;
}

