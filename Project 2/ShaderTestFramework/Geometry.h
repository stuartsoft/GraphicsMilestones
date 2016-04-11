#pragma once
#include "glm\glm.hpp"
#include <qopenglfunctions.h>

//using namespace glm;

class Geometry : public QOpenGLFunctions{
public:
	glm::vec4* points;
	Geometry();
	int numPoints;
	void draw();
};