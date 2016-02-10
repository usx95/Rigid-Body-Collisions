#include "help.h"
#include "RigidBodySystem.h"
#include "math2D.h"


void  RigidBodySystem::addBody(RigidBody b){
	sys.push_back(b);
	SystemEnergy += b.getEnergy();
} 
pair<Vector2D,Vector2D> RigidBodySystem::resVelocity(RigidBody &A, RigidBody &B){
	Vector2D normal = (A.centre - B.centre).unit();
	Vector2D tangent = Vector2D(-normal.y,normal.x).unit();
	
	Vector2D v1T = tangent * (A.velocity*tangent);
	Vector2D v2T = tangent * (B.velocity*tangent);
	
	double v1N = A.velocity*normal, v2N = B.velocity*normal;
	Vector2D v1NF = normal * ((v1N*(A.mass - B.mass) + 2*B.mass*v2N)/(A.mass + B.mass));
	Vector2D v2NF = normal * ((v2N*(B.mass - A.mass) + 2*A.mass*v1N)/(A.mass + B.mass));
	
	return {v1NF + v1T,v2NF + v2T};
}
 

void RigidBodySystem::display(){
	for(int i=0;i<sys.size();++i){
		sys[i].nextSimulation();
		sys[i].display();
	}
	collisionResolution();
	conservation();//debug mode must be encorporated
}
bool RigidBodySystem::DetectCollision(RigidBody &A, RigidBody &B){
	//if((A.centre - B.centre).norm() <  A.radius + B.radius)
	//	return 1;
	if((A.centre - B.centre).norm() <  A.radius + B.radius and (B.velocity - A.velocity)*(B.centre - A.centre) < 0)
		return 1;//only if distance is decreasing... 
	return 0;
}
void RigidBodySystem::ResolveCollison(RigidBody &A, RigidBody &B){
	pair<Vector2D,Vector2D> res = resVelocity(A,B);
	A.velocity = res.first;
	B.velocity = res.second;
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
	Vector2D Momentum = Vector2D(0.0,0.0);
	for(int i=0;i<sys.size();++i){
		Energy += sys[i].getEnergy();
		Momentum = Momentum + sys[i].getLinearMomentum();
	}
	printf("Energy = %0.15f\t\tERROR = %0.15f\n",Energy,abs(SystemEnergy - Energy));
}

