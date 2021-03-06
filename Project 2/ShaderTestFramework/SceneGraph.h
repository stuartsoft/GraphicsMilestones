#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>

#include "glm\gtc\matrix_transform.hpp"

#include "Geometry.h"

using namespace std;

class SceneGraph {
public:
	SceneGraph();
	void Parse(string fname);

	glm::mat4 translation;
	glm::mat4 rotation;
	glm::mat4 scale;
	glm::mat4 M;//the combined recursive values of translation rotation and scale all the way down the graph to this scene graph node

	SceneGraph* rootSG;//pointer back to Scene Graph root node
	SceneGraph* parentSG;//pointer to parent scene graph
	vector<SceneGraph*> decendents; //vector of all children of this scene graph
	vector<Geometry*> geometryObjectRef;//Only filled by root node, contains a list of the actual geometry objects
										//geometry attribute on other nodes should point back to this list

	Geometry* geometry;

	void traverse(glm::mat4 mat);
	void addChild(SceneGraph* child);
	void draw(unsigned int &vLocation, unsigned int &vNormal, unsigned int &vShiny, unsigned int &cLocation, unsigned int &vbo, unsigned int &vbo2, unsigned int &vbo3, unsigned int &cbo);

private:
	int xSize;
	int zSize;
};