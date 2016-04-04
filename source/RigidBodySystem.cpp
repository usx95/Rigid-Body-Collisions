#include "help.h"
#include "RigidBodySystem.h"
#include "math2D.h"


void  RigidBodySystem::addBody(RigidBody b){
	sys.push_back(b);
//	SystemEnergy += b.getEnergy();
} 
pair<Vector2D,Vector2D> RigidBodySystem::resVelocity(RigidBody &A, RigidBody &B){
	Vector2D normal = (A.centre - B.centre).unit();
	Vector2D tangent = Vector2D(-normal.y,normal.x,0.0).unit();
	
	Vector2D v1T = tangent * (A.velocity*tangent);
	Vector2D v2T = tangent * (B.velocity*tangent);
	
	double v1N = A.velocity*normal, v2N = B.velocity*normal;

	Vector2D v1NF = normal * (v1N*A.mass + B.mass*v2N  + Coef_Restitution*B.mass * (v2N - v1N) )/(A.mass + B.mass);
	Vector2D v2NF = normal * (v1N*A.mass + B.mass*v2N  + Coef_Restitution*A.mass * (v1N - v2N) )/(A.mass + B.mass);
	
	return {v1NF + v1T,v2NF + v2T};
}
 
void RigidBodySystem::drawGrid(){
//	glColor3f(.3,.3,.3);
	double N = 5;
	glBegin(GL_LINES);
	/*XZ PLANE*/
	glColor3f(.3,.6,.3);
	glColor3f(.1,.6,.6);
	glColor3f(.6,.3,.3);
	for(int i=0;i<=N;i++) {
	  //  if (i==0) { glColor3f(.6,.3,.3); } else { glColor3f(.25,.25,.25); };
	    
	glColor3f(.1,.6,.6);
		glVertex3f(i*MAX_X/N,0,0);
	    glVertex3f(i*MAX_X/N,0,MAX_Z);
	   // if (i==0) { glColor3f(.3,.3,.6); } else { glColor3f(.25,.25,.25); };
	glColor3f(.3,.6,.3);
	    glVertex3f(0,0,i*MAX_X/N);
	    glVertex3f(MAX_X,0,i*MAX_X/N);
	};
	for(int i=0;i<=N;i++) {
	  //  if (i==0) { glColor3f(.6,.3,.3); } else { glColor3f(.25,.25,.25); };
	
	glColor3f(.1,.6,.6);
	    glVertex3f(i*MAX_X/N,MAX_Y,0);
	    glVertex3f(i*MAX_X/N,MAX_Y,MAX_Z);
	   // if (i==0) { glColor3f(.3,.3,.6); } else { glColor3f(.25,.25,.25); };
	glColor3f(.3,.6,.3);
	    glVertex3f(0,MAX_Y,i*MAX_X/N);
	    glVertex3f(MAX_X,MAX_Y,i*MAX_X/N);
	};
	
	
	/*YZ PLANE*/
	for(int i=0;i<=N;i++) {
	  //  if (i==0) { glColor3f(.6,.3,.3); } else { glColor3f(.25,.25,.25); };
	glColor3f(.6,.3,.3);
	    glVertex3f(0,i*MAX_Y/N,0);
	    glVertex3f(0,i*MAX_Y/N,MAX_Z);
	   // if (i==0) { glColor3f(.3,.3,.6); } else { glColor3f(.25,.25,.25); };
	    
	glColor3f(.3,.6,.3);
		glVertex3f(0,0,i*MAX_Z/N);
	    glVertex3f(0,MAX_Y,i*MAX_Z/N);
	};
	for(int i=0;i<=N;i++) {
	  //  if (i==0) { glColor3f(.6,.3,.3); } else { glColor3f(.25,.25,.25); };
	glColor3f(.6,.3,.3);
	    glVertex3f(MAX_X,i*MAX_Y/N,0);
	    glVertex3f(MAX_X,i*MAX_Y/N,MAX_Z);
	   // if (i==0) { glColor3f(.3,.3,.6); } else { glColor3f(.25,.25,.25); };
	    
	glColor3f(.3,.6,.3);
		glVertex3f(MAX_X,0,i*MAX_Z/N);
	    glVertex3f(MAX_X,MAX_Y,i*MAX_Z/N);
	};
	
	/*XY PLANE*/
	for(int i=0;i<=N;i++) {
	  //  if (i==0) { glColor3f(.6,.3,.3); } else { glColor3f(.25,.25,.25); };
	glColor3f(.1,.6,.6);
	    glVertex3f(i*MAX_X/N,0,0);
	    glVertex3f(i*MAX_X/N,MAX_Y,0);
	   // if (i==0) { glColor3f(.3,.3,.6); } else { glColor3f(.25,.25,.25); };
	glColor3f(.6,.3,.3);
	    glVertex3f(0,i*MAX_Y/N,0);
	    glVertex3f(MAX_X,i*MAX_Y/N,0);
	};
	
	for(int i=0;i<=N;i++) {
	  //  if (i==0) { glColor3f(.6,.3,.3); } else { glColor3f(.25,.25,.25); };
	glColor3f(.1,.6,.6);
	    glVertex3f(i*MAX_X/N,0,MAX_Z);
	    glVertex3f(i*MAX_X/N,MAX_Y,MAX_Z);
	   // if (i==0) { glColor3f(.3,.3,.6); } else { glColor3f(.25,.25,.25); };
	glColor3f(.6,.3,.3);
	    glVertex3f(0,i*MAX_Y/N,MAX_Z);
	    glVertex3f(MAX_X,i*MAX_Y/N,MAX_Z);
	};
	
	glEnd();
}
void RigidBodySystem::display(){
		glColor3f(1,1,1);
		if(pause_and_view==false){
		for(int f=1; f <= SimulationsPerFrame; ++f){
			for(int i=0;i<sys.size();++i){
				sys[i].nextSimulation();
			}
			if(HEAVENLY_BODY){
				GravitationalAcceleration();
			}
			collisionResolution();
		}
	}
	for(int i=0;i<sys.size();++i){
		sys[i].display();
	}
	drawGrid();
	//cout<<"***********************************************\n";
}
bool RigidBodySystem::DetectCollision(RigidBody &A, RigidBody &B){
	Vector2D radial = (A.centre - B.centre);
	if(radial*radial <  (A.radius + B.radius)*(A.radius + B.radius) and (B.velocity - A.velocity)*(B.centre - A.centre) < 0)
		return 1;//only if distance is decreasing... 
	return 0;
}
void RigidBodySystem::ResolveCollison(RigidBody &A, RigidBody &B){
	pair<Vector2D,Vector2D> res = resVelocity(A,B);
	A.velocity = res.first;
	B.velocity = res.second;
}
void RigidBodySystem::GravitationalAcceleration(){
	for(int i=0;i<sys.size();++i){
		sys[i].acceleration = {0,0,0};
		for(int j=0;j<sys.size();++j){
			if(i==j)continue;
			Vector2D radial = sys[i].centre - sys[j].centre;
			sys[i].acceleration = sys[i].acceleration	- radial * (Gravitational_constant * sys[j].mass/pow(radial.norm(),3) )	;
		}
	}
}
void RigidBodySystem::collisionResolution(){
	for(int i=0;i<sys.size();++i){
		for(int j=i+1;j<sys.size();++j){
			if(DetectCollision(sys[i],sys[j])){
				ResolveCollison(sys[i],sys[j]);
			}
		}
	}
}
void RigidBodySystem::conservation(){
	double Energy = 0;
	Vector2D Momentum = Vector2D(0.0,0.0,0.0);
	for(int i=0;i<sys.size();++i){
		Energy += sys[i].getEnergy();
		Momentum = Momentum + sys[i].getLinearMomentum();
	}
	printf("Energy = %0.15f\t\tERROR = %0.15f\n",Energy,abs(SystemEnergy - Energy));
}

