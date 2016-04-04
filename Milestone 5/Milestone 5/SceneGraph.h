#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"

#include "Geometry.h"

using namespace std;

class SceneGraph {
public:
	SceneGraph(){};
	void Parse(string fname);
	SceneGraph* checkIfObjectExistsHere(glm::vec3 pos);

	glm::mat4 translation;
	glm::mat4 rotation;
	glm::mat4 scale;

	SceneGraph* rootSG;//pointer back to Scene Graph root node
	SceneGraph* parentSG;//pointer to parent scene graph
	vector<SceneGraph> decendents; //vector of all children of this scene graph

	Geometry* geometry;

	void traverse(glm::mat4 mat);
	void addChild(SceneGraph child);

private:
	int xSize;
	int zSize;
};