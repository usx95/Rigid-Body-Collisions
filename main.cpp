#include "source/help.h"
#include "source/RigidBody.h"
#include "source/RigidBodySystem.h"
#include "source/math2D.h"

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
	double rad = 25;
	int N = 10;
	for(int j=1;j<=1;++j){
		for(int i=1;i<=N;++i){
			Vector2D c = {rad + 2*rad*i,rad*(2*j-1)};
			double mass = 1;
			Vector2D v = {0,0};
			if(i==N)mass=1000,v={100.0,0.0},rad=3*rad,c={1000.0,rad};
			System.addBody(RigidBody(c,rad,mass,v,{0.0,-90.80}));
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

