#include "help.h"
#include "Configurations.h"

int HEAVENLY_BODY;
double Gravitational_constant;

int SimulationsPerFrame, deltaT;

int MAX_Y, MAX_X;
int window_breadth, window_height;

void  Configurations::Read_and_Set(string S){
	ConfigFile cf(S);
	//GRAVITY
	HEAVENLY_BODY = (cf.Value("GRAVITY","HEAVENLY_BODY")).equals("ON") ? 1:0;
	Gravitational_constant = double(cf.Value("GRAVITY","GRAVITATIONAL_CONSTANT"));
	
	
	//ACCURACY
	SimulationsPerFrame = double(cf.Value("ACCURACY","SIMULATIONS_PER_FRAME"));
	deltaT = double(cf.Value("ACCURACY","DIVISIONS_OF_1_SECOND"));
	
	//DISPLAY
	MAX_X = double(cf.Value("DISPLAY","MAX_X_COORDINATE"));
	MAX_Y = double(cf.Value("DISPLAY","MAX_Y_COORDINATE"));
	window_breadth = double(cf.Value("DISPLAY","WINDOW_WIDTH"));
	window_height = double(cf.Value("DISPLAY","WINDOW_HEIGHT"));

}
