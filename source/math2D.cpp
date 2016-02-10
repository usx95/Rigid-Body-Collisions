#include "help.h"
#include "math2D.h"

Vector2D::Vector2D(double x,double y){
	this->x = x;
	this->y = y;
}
Vector2D::Vector2D(){}
Vector2D::Vector2D(int x,int y){
	this->x = x;
	this->y = y;
}
//scalar mul
Vector2D Vector2D::operator*(double v){
	return Vector2D(this->x*v,this->y*v);
}
Vector2D Vector2D::operator/(double v){
	return Vector2D(this->x/v,this->y/v);
}


//vector add sub 
Vector2D Vector2D::operator+(Vector2D a){
	return Vector2D(a.x+this->x,a.y+this->y);
}
Vector2D Vector2D::operator-(Vector2D a){
	return Vector2D(-a.x+this->x,-a.y+this->y);
}
//dot product
double Vector2D::operator*(Vector2D a){
	return (a.x * this->x + a.y * this->y);
}


double Vector2D::norm(){
	return (sqrt(x*x+y*y));
}
Vector2D Vector2D::unit(){
	return (*this)/norm();
}
int math2D::genRand(int L,int R){
	assert(L<=R);
	return L + rand()%(R-L+1);
}

