#include "stubs.h"
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
		geomList = list;
	}

	//Calculate all lighting along with the shadow feelers affecting that lighting
	double shadowFeeler(vec4 intersectPoint);

	//Generate the rays starting from the camera and going to a point on the screen
	void rayGeneration(const mat4& transMatrix);

	//Calculate the lighting for the pixel
	vec3 calculateLighting(double shadowFeeler);

private:
	std::vector<Geometry*> geomList;
	glm::vec2 imageSize;
	glm::vec3 eyePos;
	glm::vec3 vdir;
	glm::vec3 uvec;
	float fovy;

};