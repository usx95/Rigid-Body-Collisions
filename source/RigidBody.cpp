#include "help.h"
#include "RigidBody.h"
#include "math2D.h"
#include "Camera.h"

RigidBody::RigidBody(Vector2D c,double r,double m,Vector2D v){
	centre = c;
	radius = r;
	mass = m;
	velocity = v;
	acceleration = Vector2D(0.0,-accGravity,0.0);
}
void RigidBody::BoundaryCollisionCheck(){
	if(centre.z <= radius and velocity.z <= 0){
		velocity.z *= -1;
	}
	if(centre.z + radius >= MAX_Z  and velocity.z >= 0){
		velocity.z *= -1;
	}
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
//	glPushMatrix();
		
	glBegin(GL_LINES);
		for(auto it=pathTrace.begin();it+1!=pathTrace.end();++it){
			auto next = it+1;
			
			glVertex3f((*it).x,(*it).y, (*it).z);
			glVertex3f((*next).x,(*next).y, (*next).z);
		
		}
	glEnd();
//	glPopMatrix();

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
	
glPushMatrix();
	glTranslatef(centre.x,centre.y,centre.z);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, EarthTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	glRotatef(90,1.0f,0.0f,0.0f);
	gluQuadricTexture(quad,1);
	gluSphere(quad,radius,SphereAccuracy,SphereAccuracy);
	
	
	
	//glutWireSphere(radius,10,10);
glPopMatrix();
	
	if(PATH_TRACE){
		printPathTrace();	
	}
//	printf("velocity = (%f,%f,%f)\n",velocity.x,velocity.y,velocity.z);
}

double RigidBody::getEnergy(){
	return 0.5 * mass * (velocity* velocity) - mass * acceleration.y * centre.y; 
}
Vector2D RigidBody::getLinearMomentum(){
	return velocity * mass;
}
