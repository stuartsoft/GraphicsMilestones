#include "Geometry.h"

Geometry::Geometry(){
	
	numPoints = 24;
	points = new glm::vec4[8];

	//front face
	points[0] = glm::vec4(-0.5f, 0.0f, 0.5f, 1.0f);
	points[1] = glm::vec4(0.5f, 0.0f, 0.5f, 1.0f);
	points[2] = glm::vec4(0.5f, 1.0f, 0.5f, 1.0f);
	points[3] = glm::vec4(-0.5f, 1.0f, 0.5f, 1.0f);

	//back face
	points[4] = glm::vec4(-0.5f, 0.0f, -0.5f, 1.0f);
	points[5] = glm::vec4(-0.5f, 1.0f, -0.5f, 1.0f);
	points[6] = glm::vec4(0.5f, 1.0f, -0.5f, 1.0f);
	points[7] = glm::vec4(0.5f, 0.0f, -0.5f, 1.0f);

	
	//right face
	points[8] = glm::vec4(0.5f, 1.0f, -0.5f, 1.0f);
	points[9] = glm::vec4(0.5f, 1.0f, 0.5f, 1.0f);
	points[10] = glm::vec4(0.5f, -1.0f, 0.5f, 1.0f);
	points[11] = glm::vec4(0.5f, -1.0f, -0.5f, 1.0f);

	//left face
	points[12] = glm::vec4(-0.5f, 1.0f, 0.5f, 1.0f);
	points[13] = glm::vec4(-0.5f, 1.0f, -0.5f, 1.0f);
	points[14] = glm::vec4(-0.5f, -1.0f, -0.5f, 1.0f);
	points[15] = glm::vec4(-0.5f, -1.0f, 0.5f, 1.0f);

	//top face
	points[16] = glm::vec4(0.5f, 1.0f, -0.5f, 1.0f);
	points[17] = glm::vec4(-0.5f, 1.0f, -0.5f, 1.0f);
	points[18] = glm::vec4(-0.5f, 1.0f, 0.5f, 1.0f);
	points[19] = glm::vec4(0.5f, 1.0f, 0.5f, 1.0f);

	//bottom face
	points[20] = glm::vec4(0.5f, -0.5f, 0.5f, 1.0f);
	points[21] = glm::vec4(-0.5f, -0.5f, 0.5f, 1.0f);
	points[22] = glm::vec4(-0.5f, -0.5f, -0.5f, 1.0f);
	points[23] = glm::vec4(0.5f, -0.5f, -0.5f, 1.0f);
	

}

void Geometry::draw(){
	//do drawing n stuff
	initializeOpenGLFunctions();
}