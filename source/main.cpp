#include "help.h"
#include "RigidBody.h"
#include "RigidBodySystem.h"
#include "math2D.h"
#include "Configurations.h"
#include "InputHandler.h"
#include "Extras/imageloader.h"
#include "Camera.h"


RigidBodySystem System;
math2D math;
bool pause_and_view = false;

int frames = 0;
double start = clock();
GLuint EarthTexture; //The id of the textur
GLUquadric *quad;


void Draw() {
	++frames;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	System.display();
	
	if((clock() - start)/CLOCKS_PER_SEC >= 3){
		double sps = SimulationsPerFrame * frames  * CLOCKS_PER_SEC /(clock() - start) ;
		printf("simulations per second = %f\n",sps);
		frames = 0;
		start = clock();
	}
	glFlush();
	//glutPostRedisplay();
}


void setGrid(){
	double rad = 100;
	int M = 0;
	for(int j=1;j<=M;++j){
		for(int i=1;i<=M;++i){
			Vector2D c = Vector2D(1000+3*rad*i,rad*(2*j-1),0.0);
			double mass = 400;
			Vector2D v = Vector2D(0,0,0);
			System.addBody(RigidBody(c,rad,mass,v));
		}
	}
	if(1){
		System.addBody(RigidBody({MAX_X/2,MAX_Y/2,0},rad,10,{0,0,0}));
	}//System.addBody(RigidBody({30+500,70+500},20,10,{5,-1},{0,0}));
	
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
void reshape(GLsizei width, GLsizei height) {
	if (height == 0) height = 1;             
	GLfloat aspect = (GLfloat)width / (GLfloat)height;
	
	glViewport(0, 0, width, height);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();  
	
	if (width >= height) {
			glOrtho(0.0, MAX_X * aspect, 0.0, MAX_Y, -1.0, 1.0);
	} else {
			glOrtho(0.0, MAX_X, 0.0, MAX_Y * aspect, -1.0, 1.0);
	}
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
	setGrid();
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	quad = gluNewQuadric();

	Image* image = loadBMP("earth.bmp");
	EarthTexture = loadTexture(image);
	delete image;
}

void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, MAX_X, 0, MAX_Y, -1000, 1000.0);
}

int main(int iArgc, char** cppArgv) {
	camera.init();
	Configurations cf;
	cf.Read_and_Set("config.txt");
			
	glutInit(&iArgc, cppArgv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(window_breadth, window_height);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Rigid Body Simulations (@usaxena95)");
	Initialize();
	
	glViewport(0, 0, window_breadth, window_height);
	glutDisplayFunc(Draw);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouseClick);
	glutMotionFunc(mouseActiveMotion);
	glutReshapeFunc(handleResize);
	
	glutIdleFunc(Draw);
	
	//	glutPassiveMotionFunc (mousePassiveMotion);//No click required
	//	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}
