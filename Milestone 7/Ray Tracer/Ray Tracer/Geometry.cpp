#include "Geometry.h"

Geometry::Geometry(){
	
	numPoints = 24;

	points = new glm::vec4[24];
	normals = new glm::vec4[24];
	colors = new glm::vec3[24];
	shinyness = new float[24];

	for (int i = 0;i<24;i++){
		shinyness[i] = 10.0f;
	}

	//front face
	points[0] = glm::vec4(0.5f, 1.0f, 0.5f, 1.0f);
	points[1] = glm::vec4(-0.5f, 1.0f, 0.5f, 1.0f);
	points[2] = glm::vec4(-0.5f, -0.0f, 0.5f, 1.0f);
	points[3] = glm::vec4(0.5f, -0.0f, 0.5f, 1.0f);

	normals[0] = glm::vec4(0.0f, 0.0f, -1.0f, 0.0f);
	normals[1] = glm::vec4(0.0f, 0.0f, -1.0f, 0.0f);
	normals[2] = glm::vec4(0.0f, 0.0f, -1.0f, 0.0f);
	normals[3] = glm::vec4(0.0f, 0.0f, -1.0f, 0.0f);

	colors[0] = glm::vec3(1.0f, 0.0f, 0.0f);
	colors[1] = glm::vec3(1.0f, 0.0f, 0.0f);
	colors[2] = glm::vec3(1.0f, 0.0f, 0.0f);
	colors[3] = glm::vec3(1.0f, 0.0f, 0.0f);

	//back face
	points[4] = glm::vec4(0.5f, 1.0f, -0.5f, 1.0f);
	points[5] = glm::vec4(0.5f, -0.0f, -0.5f, 1.0f);
	points[6] = glm::vec4(-0.5f, -0.0f, -0.5f, 1.0f);
	points[7] = glm::vec4(-0.5f, 1.0f, -0.5f, 1.0f);
	normals[4] = glm::vec4(0.0f, 0.0f, 1.0f, 0.0f);
	normals[5] = glm::vec4(0.0f, 0.0f, 1.0f, 0.0f);
	normals[6] = glm::vec4(0.0f, 0.0f, 1.0f, 0.0f);
	normals[7] = glm::vec4(0.0f, 0.0f, 1.0f, 0.0f);

	colors[4] = glm::vec3(1.0f, 0.0f, 0.0f);
	colors[5] = glm::vec3(1.0f, 0.0f, 0.0f);
	colors[6] = glm::vec3(1.0f, 0.0f, 0.0f);
	colors[7] = glm::vec3(1.0f, 0.0f, 0.0f);

	//right face
	points[8] = glm::vec4(0.5f, 1.0f, -0.5f, 1.0f);
	points[9] = glm::vec4(0.5f, 1.0f, 0.5f, 1.0f);
	points[10] = glm::vec4(0.5f, -0.0f, 0.5f, 1.0f);
	points[11] = glm::vec4(0.5f, -0.0f, -0.5f, 1.0f);
	normals[8] = glm::vec4(-1.0f, 0.0f, 0.0f, 0.0f);
	normals[9] = glm::vec4(-1.0f, 0.0f, 0.0f, 0.0f);
	normals[10] = glm::vec4(-1.0f, 0.0f, 0.0f, 0.0f);
	normals[11] = glm::vec4(-1.0f, 0.0f, 0.0f, 0.0f);

	colors[8] = glm::vec3(0.0f, 0.8f, 0.0f);
	colors[9] = glm::vec3(0.0f, 0.8f, 0.0f);
	colors[10] = glm::vec3(0.0f, 0.8f, 0.0f);
	colors[11] = glm::vec3(0.0f, 0.8f, 0.0f);

	//left face
	points[12] = glm::vec4(-0.5f, 1.0f, 0.5f, 1.0f);
	points[13] = glm::vec4(-0.5f, 1.0f, -0.5f, 1.0f);
	points[14] = glm::vec4(-0.5f, -0.0f, -0.5f, 1.0f);
	points[15] = glm::vec4(-0.5f, -0.0f, 0.5f, 1.0f);
	normals[12] = glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);
	normals[13] = glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);
	normals[14] = glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);
	normals[15] = glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);

	colors[12] = glm::vec3(0.0f, 0.8f, 0.0f);
	colors[13] = glm::vec3(0.0f, 0.8f, 0.0f);
	colors[14] = glm::vec3(0.0f, 0.8f, 0.0f);
	colors[15] = glm::vec3(0.0f, 0.8f, 0.0f);

	//top face
	points[16] = glm::vec4(0.5f, 1.0f, -0.5f, 1.0f);
	points[17] = glm::vec4(-0.5f, 1.0f, -0.5f, 1.0f);
	points[18] = glm::vec4(-0.5f, 1.0f, 0.5f, 1.0f);
	points[19] = glm::vec4(0.5f, 1.0f, 0.5f, 1.0f);
	normals[16] = glm::vec4(0.0f, -1.0f, 0.0f, 0.0f);
	normals[17] = glm::vec4(0.0f, -1.0f, 0.0f, 0.0f);
	normals[18] = glm::vec4(0.0f, -1.0f, 0.0f, 0.0f);
	normals[19] = glm::vec4(0.0f, -1.0f, 0.0f, 0.0f);

	colors[16] = glm::vec3(0.0f, 0.0f, 1.0f);
	colors[17] = glm::vec3(0.0f, 0.0f, 1.0f);
	colors[18] = glm::vec3(0.0f, 0.0f, 1.0f);
	colors[19] = glm::vec3(0.0f, 0.0f, 1.0f);

	//bottom face
	points[20] = glm::vec4(0.5f, -0.0f, 0.5f, 1.0f);
	points[21] = glm::vec4(-0.5f, -0.0f, 0.5f, 1.0f);
	points[22] = glm::vec4(-0.5f, -0.0f, -0.5f, 1.0f);
	points[23] = glm::vec4(0.5f, -0.0f, -0.5f, 1.0f);
	normals[20] = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
	normals[21] = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
	normals[22] = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
	normals[23] = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);

	colors[20] = glm::vec3(0.0f, 0.0f, 1.0f);
	colors[21] = glm::vec3(0.0f, 0.0f, 1.0f);
	colors[22] = glm::vec3(0.0f, 0.0f, 1.0f);
	colors[23] = glm::vec3(0.0f, 0.0f, 1.0f);

}

void Geometry::draw(glm::mat4 M, unsigned int &vLocation, unsigned int &vNormal, unsigned int &vShiny, unsigned int &cLocation, unsigned int &vbo, unsigned int &vbo2, unsigned int &vbo3, unsigned int &cbo){
	//do drawing n stuff
	initializeOpenGLFunctions();

	std::vector<glm::vec4> vresults;
	std::vector<glm::vec4> nresults;

	glm::vec4 * finalPoints = new glm::vec4[24];
	glm::vec4 * finalNormals = new glm::vec4[24];
	
	for (int i = 0;i<numPoints;i++){
		finalPoints[i] = M*points[i];
		finalNormals[i] = M*normals[i];
	}
	

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(glm::vec4), finalPoints, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vbo2);
	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(glm::vec4), finalNormals, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vbo3);
	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(float), shinyness, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, cbo);
	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(glm::vec3), colors, GL_STATIC_DRAW);

	
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableVertexAttribArray(vLocation);
	glVertexAttribPointer(vLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo2);
	glEnableVertexAttribArray(vNormal);
	glVertexAttribPointer(vNormal, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo3);
	glEnableVertexAttribArray(vShiny);
	glVertexAttribPointer(vShiny, 1,GL_FLOAT, GL_FALSE, 0,0);

	glBindBuffer(GL_ARRAY_BUFFER, cbo);
	glEnableVertexAttribArray(cLocation);
	glVertexAttribPointer(cLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_QUADS, 0, 24);
	glFlush();

}