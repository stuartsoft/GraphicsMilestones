#include "RayTracer.h"

//Define the variables for the program up here

int main()
{
	//Generate the scenegraph for the scene
	SceneGraph *graphOne = new SceneGraph;

	vector<Geometry> transGeomList;
	
	//
	rayTracer *tracerOne = new rayTracer(transGeomList, the vector information);
	tracerOne->setData();

	return 0;
}
