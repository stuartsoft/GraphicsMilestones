#include "stubs.h"
#include "Geometry.h"
#include "glm\glm.hpp"

class RayTracer
{
public:
	RayTracer(vec3 EyePos, vec3 Vdir, vec3 Uvec, float Fovy){
		eyePos = EyePos;
		vdir = Vdir;
		uvec = Uvec;
		fovy = Fovy;
	}

	//Calculate all lighting along with the shadow feelers affecting that lighting
	void shadowFeeler(vec4);

	//Generate the rays starting from the camera and going to a point on the screen
	void RayTracer::rayGeneration(int wid, int height);

	double intersectionTests(Geometry* geom, vec4 E, vec4 P, mat4 TransMatrix);

private:
	std::vector<Geometry*> sceneGeom;
	glm::vec3 eyePos;
	glm::vec3 vdir;
	glm::vec3 uvec;
	float fovy;
};