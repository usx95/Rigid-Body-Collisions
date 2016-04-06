#include "windows.h"
#include "help.h"
#include "RigidBody.h"
#include "RigidBodySystem.h"
#include "math2D.h"
#include "Configurations.h"
#include "InputHandler.h"
#include "Extras/imageloader.h"
#include "Camera.h"

CCamera CameraT;
int SphereAccuracy = 10;
RigidBodySystem System;
math2D math;
bool pause_and_view = false;

int frames = 0;
double start = clock();
GLuint EarthTexture; //The id of the textur
GLUquadric *quad;

void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	CameraT.Render();
	
	System.display();	

	++frames;
	if((clock() - start)>= 3 * CLOCKS_PER_SEC ){
		double sps = SimulationsPerFrame * frames  * CLOCKS_PER_SEC /(clock() - start) ;
		printf("simulations per second = %f\n",sps);
		frames = 0;
		start = clock();
	}                             
	glFlush();  
}

void keyboard(unsigned char key, int x, int y){
	handleInput.keyboard(key,x,y);
}
void mouseClick(int button, int state, int x, int y){
	handleInput.mouseClick(button,state,x,y);
}
void mousePassiveMotion(int x, int y){
	handleInput.mousePassiveMotion(x,y);
}
void mouseActiveMotion(int x, int y){
	handleInput.mouseActiveMotion(x,y);
}
 	
 GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
				 0,                            //0 for now
				 GL_RGB,                       //Format OpenGL uses for image
				 image->width, image->height,  //Width and height
				 0,                            //The border of the image
				 GL_RGB, //GL_RGB, because pixels are stored in RGB format
				 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
				                   //as unsigned numbers
				 image->pixels);               //The actual pixel data
	return textureId; //Returns the id of the texture
}
void Initialize() {
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	quad = gluNewQuadric();

	Image* image = loadBMP("earth.bmp");
	EarthTexture = loadTexture(image);
	delete image;
}
void handleResize(int x, int y){
	if (y == 0 || x == 0) return;  //Nothing is visible then, so return
	glMatrixMode(GL_PROJECTION);  
	glLoadIdentity();
	gluPerspective(40.0,(GLdouble)x/(GLdouble)y,0.1,30);
	glMatrixMode(GL_MODELVIEW);
	glViewport(0,0,x,y);
}

void menu(int op) {
 	if(op==-1)
 		return;
	switch(op) {
	case 0:
		exit(0);
	case 5:
		pause_and_view = 1;
		System.BuildBuilding(1,6,6);
		break;
	case 6:
		pause_and_view = 1;
		System.BuildBuilding(2,3,2);
		break;
	case 7:
		pause_and_view = 1;
		System.BuildBuilding(4,4,4);
		break;
	case 2:
		pause_and_view = 1;
		System.BinaryStar();
		break;
	case 8:
		pause_and_view = 1;
		System.CircularStarSystem(0);
		break;
	}
}
void addMenu(){
	// create a sub menu 
	int BuildingOptions = glutCreateMenu(menu);
	glutAddMenuEntry("Thin", 5);
	glutAddMenuEntry("Large", 7);
	glutAddMenuEntry("Small", 6);
	
	int stackMenu = glutCreateMenu(menu);
	glutAddSubMenu("Building", BuildingOptions);
	glutAddMenuEntry("Pyramid", 1);
	
	int starMenu = glutCreateMenu(menu);
	glutAddMenuEntry("Binary Star", 2);
	glutAddMenuEntry("Circular Planetary System", 8);
	
	glutCreateMenu(menu);
	glutAddSubMenu("Stack", stackMenu);
	glutAddSubMenu("Star System", starMenu);
	
	glutAddMenuEntry("PathTrace", 3);
	glutAddMenuEntry("Exit", 0);
	glutAddMenuEntry("Cancel", -1);
	
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}
int main(int iArgc, char** cppArgv) {
	Configurations cf;
	cf.Read_and_Set("config.txt");
			
	CameraT = CCamera();
	glutInit(&iArgc, cppArgv);
	//ShowCursor(false);
	
	
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(window_breadth, window_height);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Rigid Body Simulations (@usaxena95)");
	glutSetCursor(GLUT_CURSOR_FULL_CROSSHAIR);
	Initialize();
	
	glutIdleFunc(Display);
	glutDisplayFunc(Display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouseClick);
	//	glutMotionFunc(mouseActiveMotion);
	glutPassiveMotionFunc (mousePassiveMotion);//No click required
	glutReshapeFunc(handleResize);
	
	addMenu();
	glutMainLoop();
	return 0;  
}
