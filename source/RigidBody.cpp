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
	if(centre.y + radius >= Height  and velocity.y >= 0){
		velocity.y *= -1;
	}
	if(centre.x <= radius and velocity.x <= 0){
		velocity.x *= -1;
	}
	if(centre.x + radius >= Width  and velocity.x >= 0){
		velocity.x *= -1;
	}
}
void RigidBody::nextSimulation(){
	
	centre = centre + velocity / FrameRate + acceleration / (2 * FrameRate*FrameRate);
	velocity = velocity + acceleration/FrameRate;
	
	BoundaryCollisionCheck();
}
void RigidBody::display(){
	double EPS = 2*PI/20;
	for(double th=0;th<=2*PI;th+=EPS){
	glBegin(GL_LINES);
			glVertex3f(centre.x + radius * cos(th), centre.y + radius * sin(th), 0.0);
			glVertex3f(centre.x + radius * cos(th+EPS), centre.y + radius * sin(th+EPS), 0.0);
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
