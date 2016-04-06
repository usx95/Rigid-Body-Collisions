#pragma once

#include <GL/glut.h>
#include<bits/stdc++.h>
using namespace std;


#define PI 3.14159
extern GLuint EarthTexture; //The id of the textur
extern GLUquadric *quad;

extern int MAX_Y, MAX_X,MIN_X,MIN_Y,MAX_Z,MIN_Z;
extern int window_breadth, window_height, infinteSpace;

extern int HEAVENLY_BODY, EarthGravity, BOUNDARY;
extern double Gravitational_constant, accGravity;

extern int SimulationsPerFrame, deltaT;

extern int PATH_TRACE, PATH_TRACE_LENGTH;

extern double Coef_Restitution;

extern bool pause_and_view;

extern int SphereAccuracy;
