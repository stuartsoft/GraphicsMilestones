#include "stubs.h"
#include "Geometry.h"
//#include "Geometry.h"

class RayTracer
{
public:


	//Calculate all lighting along with the shadow feelers affecting that lighting
	void shadowFeeler(vec4);

	//Generate the rays starting from the camera and going to a point on the screen
	void rayGeneration();

	double intersectionTests(Geometry* geom, vec4 E, vec4 P, mat4 TransMatrix);

private:
	std::vector<Geometry*> sceneGeom;
};