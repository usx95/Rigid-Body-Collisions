#include "help.h"
#include "RigidBodySystem.h"
#include "math2D.h"

math2D mathObj;
void  RigidBodySystem::addBody(RigidBody b){
	sys.push_back(b);
	SystemEnergy += b.getEnergy();
} 
pair<Vector2D,Vector2D> RigidBodySystem::resVelocity(RigidBody &A, RigidBody &B){
	Vector2D normal = (A.centre - B.centre).unit();
	
	double v1N = A.velocity*normal, v2N = B.velocity*normal;

	Vector2D v1NF = normal * (v1N*A.mass + B.mass*v2N  + Coef_Restitution*B.mass * (v2N - v1N) )/(A.mass + B.mass);
	Vector2D v2NF = normal * (v1N*A.mass + B.mass*v2N  + Coef_Restitution*A.mass * (v1N - v2N) )/(A.mass + B.mass);
	
	return {A.velocity - normal*v1N + v1NF,B.velocity - normal*v2N + v2NF};
}
 
void RigidBodySystem::drawGrid(){
//	glColor3f(.3,.3,.3);
	double N = 8;
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
	    glVertex3f(0,0,i*MAX_Z/N);
	    glVertex3f(MAX_X,0,i*MAX_Z/N);
	};
	for(int i=0;i<=N;i++) {
	  //  if (i==0) { glColor3f(.6,.3,.3); } else { glColor3f(.25,.25,.25); };
	
	glColor3f(.1,.6,.6);
	    glVertex3f(i*MAX_X/N,MAX_Y,0);
	    glVertex3f(i*MAX_X/N,MAX_Y,MAX_Z);
	   // if (i==0) { glColor3f(.3,.3,.6); } else { glColor3f(.25,.25,.25); };
	glColor3f(.3,.6,.3);
	    glVertex3f(0,MAX_Y,i*MAX_Z/N);
	    glVertex3f(MAX_X,MAX_Y,i*MAX_Z/N);
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
void RigidBodySystem::drawFaces(){
	
	glColor3f(0/256.0,0/256.0,235/256.0);
	glBegin(GL_POLYGON);
		glVertex3f(0,0,0);
		glVertex3f(0,MAX_Y,0);
		glVertex3f(0,MAX_Y,MAX_Z);
		glVertex3f(0,0,MAX_Z);
	glEnd();
	
	glColor3f(0/256.0,0/256.0,235/256.0);
	glBegin(GL_POLYGON);
		glVertex3f(MAX_X,0,0);
		glVertex3f(MAX_X,MAX_Y,0);
		glVertex3f(MAX_X,MAX_Y,MAX_Z);
		glVertex3f(MAX_X,0,MAX_Z);
	glEnd();
	
	glColor3f(255/256.0,127/256.0,235/256.0);
	glBegin(GL_POLYGON);
		glVertex3f(0,0,0);
		glVertex3f(MAX_X,0,0);
		glVertex3f(MAX_X,MAX_Y,0);
		glVertex3f(0,MAX_Y,0);
	glEnd();
	glBegin(GL_POLYGON);
		glVertex3f(0,0,MAX_Z);
		glVertex3f(MAX_X,0,MAX_Z);
		glVertex3f(MAX_X,MAX_Y,MAX_Z);
		glVertex3f(0,MAX_Y,MAX_Z);
	glEnd();


	glColor3f(205/256.0,51/256.0,51/256.0);
	glBegin(GL_POLYGON);
		glVertex3f(0,0,0);
		glVertex3f(MAX_X,0,0);
		glVertex3f(MAX_X,0,MAX_Z);
		glVertex3f(0,0,MAX_Z);
	glEnd();	
	glBegin(GL_POLYGON);
		glVertex3f(0,MAX_Y,0);
		glVertex3f(MAX_X,MAX_Y,0);
		glVertex3f(MAX_X,MAX_Y,MAX_Z);
		glVertex3f(0,MAX_Y,MAX_Z);
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
	//drawFaces();
	drawGrid();
	//conservation();
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

void RigidBodySystem::CircularStarSystem(int N){
	sys.clear();
	BOUNDARY = 0;
	EarthGravity = 0;
	HEAVENLY_BODY = 1;
	
	double sunMass = 40000;
	double rad = 0.07;
	
	Vector2D v,planetCentre,cross,sunCentre = Vector2D(MAX_X,MAX_Y,MAX_Z)/2;
	addBody(RigidBody(sunCentre,rad*1.5,sunMass,{0.0,0.0,0.0}));
	
	for(int i=1;i<=N;++i){
		double R = min(MAX_X,min(MAX_Y,MAX_Z))/2.5;
		planetCentre = sunCentre + Vector2D(R/20 * (mathObj.genRand(1,20)>=10?1:-1) * mathObj.genRand(1,20),
											R/20 * (mathObj.genRand(1,20)>=10?1:-1) * mathObj.genRand(1,20),
											R/20 * (mathObj.genRand(1,20)>=10?1:-1) * mathObj.genRand(1,20));
		cross = sunCentre.cross(planetCentre);
		v =  cross.unit() * sqrt(Gravitational_constant * sunMass/(sunCentre-planetCentre).norm());
		addBody(RigidBody(planetCentre,rad,sunMass/2000,v));
	}
}
void RigidBodySystem::BuildBuilding(int x,int y,int z){
	sys.clear();
	EarthGravity = 1;
	BOUNDARY = 1;
	HEAVENLY_BODY = 0;
	
	double rad = 0.1;
	for(int k=1;k<=x;++k){
		for(int j=1;j<=y;++j){
			for(int i=1;i<=z;++i){
				Vector2D c = Vector2D(2*rad*i,rad*(2*j-1),rad*(2*k-1));
				double mass = 400;
				Vector2D v = Vector2D(0.0,0.0,0.0);
				addBody(RigidBody(c,rad,mass,v));
			}
		}
	}
}

void RigidBodySystem::BinaryStar(){
	sys.clear();
	BOUNDARY = 0;
	EarthGravity = 0;
	HEAVENLY_BODY = 1;

	Vector2D centre,c1,c2,v1,v2;
	centre = Vector2D(MAX_X,MAX_Y,MAX_Z)/2;
	c1 = centre - Vector2D(MAX_X/4,0,0);
	c2 = centre + Vector2D(MAX_X/4,0,0);
	double cr = (c1-c2).norm()/2;
	
	
	double mass = 40000;
	double rad = 0.07;
	
	v1 =  Vector2D(0,0,1) * sqrt(Gravitational_constant * mass/cr)/2;
	v2 =  Vector2D(0,0,-1) * sqrt(Gravitational_constant * mass/cr)/2;

	addBody(RigidBody(c1,rad,mass,v1));
	addBody(RigidBody(c2,rad,mass,v2));	
}
