#include "help.h"
#include "RigidBody.h"
#include "math2D.h"

RigidBody::RigidBody(Vector2D c,double r,double m,Vector2D v){
	centre = c;
	radius = r;
	mass = m;
	velocity = v;
	acceleration = Vector2D(0.0,-accGravity);
}
void RigidBody::BoundaryCollisionCheck(){
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
void RigidBody::printPathTrace(){
	if(pathTrace.size()==0)//added body in a paused system
		return;
	for(auto it=pathTrace.begin();it+1!=pathTrace.end();++it){
		auto next = it+1;
		
		glBegin(GL_LINES);
			glVertex3f((*it).x,(*it).y, 0.0);
			glVertex3f((*next).x,(*next).y, 0.0);
		glEnd();
	
	}
}
void RigidBody::nextSimulation(){
	
	centre = centre + velocity / deltaT + acceleration / (2 * deltaT*deltaT);
	velocity = velocity + acceleration/deltaT;
	
	if(PATH_TRACE){
		pathTrace.push_back(centre);
		if(pathTrace.size() == PATH_TRACE_LENGTH)
			pathTrace.pop_front();
	}
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
	if(PATH_TRACE){
		printPathTrace();	
	}
}

double RigidBody::getEnergy(){
	return 0.5 * mass * (velocity* velocity) - mass * acceleration.y * centre.y; 
}
Vector2D RigidBody::getLinearMomentum(){
	return velocity * mass;
}
