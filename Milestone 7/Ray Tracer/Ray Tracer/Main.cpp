#include "RayTracer.h"

//Define the variables for the program up here

int main()
{
	//Generate the scenegraph for the scene
	SceneGraph *graphOne = new SceneGraph;
	graphOne->Parse("scene1.txt");

	vector<Geometry> transGeomList;
	graphOne->traverse(glm::mat4());
	graphOne->draw(transGeomList);
	
	rayTracer *tracerOne = new rayTracer(transGeomList, "output.bmp");
	tracerOne->setData();

	return 0;
}
