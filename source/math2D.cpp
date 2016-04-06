#include "help.h"
#include "math2D.h"

Vector2D::Vector2D(double x,double y,double z){
	this->x = x;
	this->y = y;
	this->z = z;
}
Vector2D::Vector2D(){
	x = y = z = 0;
}
Vector2D::Vector2D(int x,int y,int z){
	this->x = x;
	this->y = y;
	this->z = z;
}
//scalar mul
Vector2D Vector2D::operator*(double v){
	return Vector2D(this->x*v,this->y*v,this->z*v);
}
Vector2D Vector2D::operator/(double v){
	return Vector2D(this->x/v,this->y/v,this->z/v);
}
//vector add sub 
Vector2D Vector2D::operator+(Vector2D a){
	return Vector2D(a.x+this->x,a.y+this->y,a.z+this->z);
}
Vector2D Vector2D::operator-(Vector2D a){
	return Vector2D(-a.x+this->x,-a.y+this->y,-a.z+this->z);
}
Vector2D Vector2D::cross(Vector2D a){
	return Vector2D(y*a.z-z*a.y,z*a.x-a.z*x,x*a.y-a.x*y);
}
//dot product
double Vector2D::operator*(Vector2D a){
	return (a.x * this->x + a.y * this->y + a.z * this->z);
}


double Vector2D::norm(){
	return (sqrt(x*x+y*y+z*z));
}
Vector2D Vector2D::unit(){
	return (*this)/norm();
}
int math2D::genRand(int L,int R){
	assert(L<=R);
	return L + rand()%(R-L+1);
}
