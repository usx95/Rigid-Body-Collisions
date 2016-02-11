#include "help.h"
#include "RigidBody.h"
#include "RigidBodySystem.h"
#include "math2D.h"

RigidBodySystem System;
math2D math;

void Draw() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);

	System.display();
	
	glFlush();
	glutPostRedisplay();
}


void setGrid(){
	double rad = 35;
	int N = 16,M = 15;
	for(int j=1;j<=M;++j){
		for(int i=1;i<=N;++i){
			Vector2D c = {0.1 + 2*rad*i,rad*(2*j-1)};
			double mass = 1;
			Vector2D v = {0,0};
			if(i==N and j==M)mass=0.010,v={500.0,0.0},c={rad*3 + 2*rad*N,rad},rad=0.3*rad;
			System.addBody(RigidBody(c,rad,mass,v,{0.0,-9.80}));
		}
	}
	//System.addBody(RigidBody(Vector2D(300,300),70,10,Vector2D(-20,-20),Vector2D(0.0,-500.0)));
	
}
void Initialize() {
	//System.addBody(RigidBody(Vector2D(400,400),75,2,Vector2D(-100,-50),Vector2D(0.0,0.0)));
	setGrid();
	
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, Width, 0.0, Height, -1.0, 1.0);
}

int main(int iArgc, char** cppArgv) {
	glutInit(&iArgc, cppArgv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("Rigid Body Simulations (@usaxena95)");
	Initialize();
	glutDisplayFunc(Draw);
	glutMainLoop();
	return 0;
}

