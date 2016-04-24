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

	//Runs the whole operation of the ray tracer
	vec3* runTracer();

	//Function that goes through for each pixel and ray traces it 
	vec3 rayTrace(glm::vec3 pixelColor, const vec4& ray, const double& depth);

	//Run the intersection tests from milestone 6 (Geometry holds a sting telling you what type of geometry it is
	double intersectTest(const vec4& ray, geometry geom);

	//Generate the ray for each position
	vec3 generateRay(int x, int y);

	//Set the rays for the image
	void setData();

	//Check the shadow feeler from the point of intersection
	bool shadowFeeler(vec3 point);

	//Calculate the lighting (Lambertian lighting)
	vec3 calculateLight(bool shadow, vec3 normal);

	//Get the specific point from where on the geometry was hit
	vec3 RPoint(double t);

private:
	vec3 backgroundColor;
	vec3 materialColor;
	vec3 lightColor;
	vector<geometry> geomStack;
	vec4 cameraPosition;
	vec2 imageResolution;
	vec3 nVec;
	vec3 viewDirection;
	vec3 vVec;
	vec3 upVector;
	vec3 mVec;
	vec3 hVec;
	vec3 *colorBuffer;
	float angle;
};
