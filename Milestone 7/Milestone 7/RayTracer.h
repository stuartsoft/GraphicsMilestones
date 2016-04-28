#include "stubs.h"
#include "glm\glm.hpp"
//#include "Geometry.h"

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
	void shadowFeeler();

	//Generate the rays starting from the camera and going to a point on the screen
	void RayTracer::rayGeneration(int wid, int height);


private:

	glm::vec3 eyePos;
	glm::vec3 vdir;
	glm::vec3 uvec;
	float fovy;

};