#include "RayTracer.h"

int main()
{
	//Generate the scenegraph for the scene
	SceneGraph *graphOne = new SceneGraph;
	graphOne->Parse("scene6.txt");

	vector<Geometry> transGeomList;
	graphOne->traverse(glm::mat4());
	graphOne->draw(transGeomList);
	
	rayTracer *tracerOne = new rayTracer(transGeomList, "output.bmp");
	tracerOne->runTracer();

	return 0;
}
