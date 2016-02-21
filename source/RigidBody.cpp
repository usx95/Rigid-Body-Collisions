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
	
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	//gluLookAt(Camera.x,Camera.y,Camera.z,LookAt.x,LookAt.y,LookAt.z,0,1,0);
	camera.alignObject();
	
	glTranslatef(centre.x, centre.y,0);
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, EarthTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	glRotatef(90,1.0f,0.0f,0.0f);
	//glRotatef(ROTATE,0.0f,0.0f,1.0f);
	gluQuadricTexture(quad,1);
	//gluSphere(quad,10000*radius / (centre- camera.CameraPosition).norm(),10,10);
	gluSphere(quad,radius,10,10);
	
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
