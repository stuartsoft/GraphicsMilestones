#include "stubs.h"
#include "Geometry.h"
#include "glm\glm.hpp"
#include "Geometry.h"
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
	vec3 shadowFeeler(vec4 intersectPoint, mat4 T);

	//Generate the rays starting from the camera and going to a point on the screen
	void rayGeneration(const mat4& transMatrix);

	//Run the intersection tests
	double intersectionTests(Geometry* geom, vec4 E, vec4 P, mat4 TransMatrix);

private:
	std::vector<Geometry*> sceneGeom;
	glm::vec2 imageSize;
	glm::vec3 eyePos;
	glm::vec3 vdir;
	glm::vec3 uvec;
	glm::vec3 materialColor;
	glm::vec4 lightPosition;
	float fovy;

};