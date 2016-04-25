#pragma once
#include "glm\glm.hpp"
#include <vector>
#include <string>

//using namespace glm;

class GeometryNode{
public:

	GeometryNode(std::string type){geoType = type;};
	int numPoints;
	//void draw(glm::mat4 M, unsigned int &vLocation, unsigned int &vNormal, unsigned int &vShiny, unsigned int &cLocation, unsigned int &vbo, unsigned int &vbo2, unsigned int &vbo3, unsigned int &cbo);

	glm::vec4* points;
	glm::vec4* normals;
	float * shinyness;
	glm::vec3* colors;
	std::string geoType;
};