#include "help.h"
#include "RigidBody.h"
#include "RigidBodySystem.h"
#include "math2D.h"
#include "Configurations.h"
RigidBodySystem System;
math2D math;

int frames = 0;
double start = clock();
void Draw() {
	++frames;
	
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);

	System.display();
	
	if(SimulationsPerFrame * frames >= 100){
		double sps = SimulationsPerFrame * frames  * CLOCKS_PER_SEC /(clock() - start) ;
		printf("simulations per second = %f\n",sps);
		frames = 0;
		start = clock();
	}
	
	glFlush();
	glutPostRedisplay();
	
}


void setGrid(){
	double rad = 50;
	int M = 10;
	for(int j=1;j<=M;++j){
		for(int i=1;i<=j;++i){
			Vector2D c = {10.1 + 3*rad*i,rad*(3*j-1)};
			double mass = 5;
			Vector2D v = {0,0};
			System.addBody(RigidBody(c,rad,mass,v,{0.1,0.2}));
		}
	}
	//System.addBody(RigidBody({80+500,70+500},20,10,{-5,1},{0,0}));
	//System.addBody(RigidBody({140+500,60+500},20,10,{5,1},{0,0}));
	//System.addBody(RigidBody({30+500,70+500},20,10,{5,-1},{0,0}));
	
}
void Initialize() {
	setGrid();
	
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, MAX_X, 0.0, MAX_Y, -1.0, 1.0);
}

int main(int iArgc, char** cppArgv) {
	
	Configurations cf;
	cf.Read_and_Set("config.txt");
			
	glutInit(&iArgc, cppArgv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(window_breadth, window_height);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Rigid Body Simulations (@usaxena95)");
	Initialize();
	glutDisplayFunc(Draw);
	glutMainLoop();
	return 0;
}

