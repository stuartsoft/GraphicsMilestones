#include "RayTracer.h"

//Define the variables for the program up here

int main()
{
	//Generate the scenegraph for the scene
	SceneGraph *graphOne = new SceneGraph;
	
	//
	rayTracer *tracerOne = new rayTracer(graphOne, the vector information);
	tracerOne->setData();

	return 0;
}
