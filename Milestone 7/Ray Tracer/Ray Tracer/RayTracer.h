#include "stubs.h"
#include "objectTypes.h"
#include <iostream>
#include <fstream>
#include <vector>
#include "SceneGraph.h"

using std::vector;
using std::cout;
using std::cin;

class rayTracer
{
public:
	//Default constructor for the ray tracer 
	rayTracer();

	//Destructor for ray tracer 
	~rayTracer();

	//Function that goes through for each pixel and ray traces it 
	vec3 rayTrace(glm::vec3 pixelColor, const vec3& ray, const double& depth);

	//Run the intersection tests from milestone 6 (Geometry holds a sting telling you what type of geometry it is
	double intersectTest(const vec3& ray, geometry geom);

	//Generate the ray for each position
	vec3 generateRay(int x, int y);

	//Set the rays for the image
	void setData();

	//Check the shadow feeler
	void shadowFeeler();

private:
	vec3 backgroundColor;
	vector<geometry> geomStack;
	vec3 cameraPosition;
	vec2 imageResolution;
	vec3 nVec;
	vec3 viewDirection;
	vec3 vVec;
	vec3 upVector;
	vec3 mVec;
	vec3 hVec;
	float angle;
};
