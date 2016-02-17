#include "help.h"
#include "RigidBody.h"
#include "math2D.h"

RigidBody::RigidBody(Vector2D c,double r,double m,Vector2D v,Vector2D a){
	centre = c;
	radius = r;
	mass = m;
	velocity = v;
	acceleration = a;
}
void RigidBody::BoundaryCollisionCheck(){
	int collide = 0;
	if(centre.y <= radius and velocity.y <= 0){
		velocity.y *= -1;
	}
	if(centre.y + radius >= MAX_Y  and velocity.y >= 0){
		velocity.y *= -1;
	}
	if(centre.x <= radius and velocity.x <= 0){
		velocity.x *= -1;
	}
	if(centre.x + radius >= MAX_X  and velocity.x >= 0){
		velocity.x *= -1;
	}
}
void RigidBody::nextSimulation(){
	
	centre = centre + velocity / deltaT + acceleration / (2 * deltaT*deltaT);
	velocity = velocity + acceleration/deltaT;
	
	BoundaryCollisionCheck();
}
	double x[30];
	double y[30];

void RigidBody::display(){
	int N  = 20;
	double s = sin(2*PI/N);
	double c = cos(2*PI/N);
	x[0] = radius;
	y[0] = 0;
	for(int i=1;i<N;++i){
		x[i] = x[i-1] * c - y[i-1] * s;
		y[i] = y[i-1] * c + x[i-1] * s;
	}
	for(int i=0;i<N;++i){
		int j = i+1;
		if(j==N)j=0;
	glBegin(GL_LINES);
			glVertex3f(centre.x + x[i],centre.y +  y[i], 0.0);
			glVertex3f(centre.x + x[j],centre.y + y[j], 0.0);
	glEnd();
	}
	//glutSwapBuffers();
}

double RigidBody::getEnergy(){
	return 0.5 * mass * (velocity* velocity) - mass * acceleration.y * centre.y; 
}
Vector2D RigidBody::getLinearMomentum(){
	return velocity * mass;
}
