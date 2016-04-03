#include "Geometry.h"

Geometry::Geometry(){
	points = new glm::vec4[24];

	//front face
	points[0] = vec4(0.5f, 0.5f, 0.5f, 1.0f);
	points[1] = vec4(-0.5f, 0.5f, 0.5f, 1.0f);
	points[2] = vec4(-0.5f, -0.5f, 0.5f, 1.0f);
	points[3] = vec4(0.5f, -0.5f, 0.5f, 1.0f);

	//back face
	points[4] = vec4(0.5f, 0.5f, -0.5f, 1.0f);
	points[5] = vec4(0.5f, -0.5f, -0.5f, 1.0f);
	points[6] = vec4(-0.5f, -0.5f, -0.5f, 1.0f);
	points[7] = vec4(-0.5f, 0.5f, -0.5f, 1.0f);

	//right face
	points[8] = vec4(0.5f, 0.5f, -0.5f, 1.0f);
	points[9] = vec4(0.5f, 0.5f, 0.5f, 1.0f);
	points[10] = vec4(0.5f, -0.5f, 0.5f, 1.0f);
	points[11] = vec4(0.5f, -0.5f, -0.5f, 1.0f);

	//left face
	points[12] = vec4(-0.5f, 0.5f, 0.5f, 1.0f);
	points[13] = vec4(-0.5f, 0.5f, -0.5f, 1.0f);
	points[14] = vec4(-0.5f, -0.5f, -0.5f, 1.0f);
	points[15] = vec4(-0.5f, -0.5f, 0.5f, 1.0f);

	//top face
	points[16] = vec4(0.5f, 0.5f, -0.5f, 1.0f);
	points[17] = vec4(-0.5f, 0.5f, -0.5f, 1.0f);
	points[18] = vec4(-0.5f, 0.5f, 0.5f, 1.0f);
	points[19] = vec4(0.5f, 0.5f, 0.5f, 1.0f);

	//bottom face
	points[20] = vec4(0.5f, -0.5f, 0.5f, 1.0f);
	points[21] = vec4(-0.5f, -0.5f, 0.5f, 1.0f);
	points[22] = vec4(-0.5f, -0.5f, -0.5f, 1.0f);
	points[23] = vec4(0.5f, -0.5f, -0.5f, 1.0f);

}