#include "RayTracer.h"

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
	tracerOne->runTracer();

	return 0;
}
