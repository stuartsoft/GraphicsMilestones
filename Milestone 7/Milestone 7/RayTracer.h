#include "stubs.h"
#include "Geometry.h"
#include "glm\glm.hpp"
#include <iostream>
#include "EasyBMP.h"

class RayTracer
{
public:
	RayTracer(vec3 EyePos, vec3 Vdir, vec3 Uvec, float Fovy, vec2 picSize, std::vector<Geometry*> list){
		eyePos = EyePos;
		vdir = Vdir;
		uvec = Uvec;
		fovy = Fovy;
		imageSize = picSize;
		sceneGeom = list;
	}

	//Calculate all lighting along with the shadow feelers affecting that lighting
	vec3 shadowFeeler(vec4, mat4 T, vec4 normal);

	//Generate the rays starting from the camera and going to a point on the screen
	void rayGeneration(const mat4& transMatrix);

	//Run the intersection tests
	double intersectionTests(Geometry* geom, vec4 E, vec4 P, mat4 TransMatrix);

	vec4 getNormal(vec4 point, Geometry *geom, mat4 T);

private:
	std::vector<Geometry*> sceneGeom;
	glm::vec2 imageSize;
	glm::vec3 eyePos;
	glm::vec3 vdir;
	glm::vec3 uvec;
	glm::vec4 lightPos;
	float fovy;

};