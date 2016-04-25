#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>

#include "glm\gtc\matrix_transform.hpp"

#include "GeometryNode.h"
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
	vector<GeometryNode*> geometryObjectRef;//Only filled by root node, contains a list of the actual geometry objects
										//geometry attribute on other nodes should point back to this list

	GeometryNode* geometry;

	void traverse(glm::mat4 mat);
	void addChild(SceneGraph* child);
	void draw(std::vector<Geometry> &geometryList);

private:
	int xSize;
	int zSize;
};