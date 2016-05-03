#include "stubs.h"
#include "Geometry.h"
#include "glm\glm.hpp"
#include <iostream>
#include "EasyBMP.h"

class RayTracer
{
public:
	RayTracer(vec3 EyePos, vec3 Vdir, vec3 Uvec, float Fovy, vec2 picSize, vec4 lPos, std::vector<mat4> objMov, std::vector<vec3> objColor,  std::vector<Geometry*> list, std::string fName){
		eyePos = EyePos;
		vdir = Vdir;
		uvec = Uvec;
		fovy = Fovy;
		imageSize = picSize;
		sceneGeom = list;
		outputName = fName;
		lightPos = lPos;
		objectMovement = objMov;
		objectColor = objColor;
	}
	~RayTracer()
	{
		sceneGeom.clear();
	}


	//Calculate all lighting along with the shadow feelers affecting that lighting
	vec3 shadowFeeler(vec4, mat4 T, vec4 normal, unsigned self);

	//Generate the rays starting from the camera and going to a point on the screen
	void rayGeneration(const mat4& transMatrix, unsigned depth);

	//Run the intersection tests
	double intersectionTests(Geometry* geom, vec4 E, vec4 P, mat4 TransMatrix);

	vec4 getNormal(vec4 point, Geometry *geom, mat4 T);

	//Get the intersection point x,y,z
	vec4 intersectionPoint(const mat4& transMatrix, vec4 ray, double t);

	//Goes through the motions of reflection to give back the correct reflected color
	vec3 reflection(unsigned depth, vec3 currentColor, const mat4& transMatrix, vec4 R, unsigned reflectedObject);

private:
	std::vector<Geometry*> sceneGeom;
	std::vector<mat4> objectMovement;
	std::vector<vec3> objectColor;
	glm::vec2 imageSize;
	glm::vec3 eyePos;
	glm::vec3 vdir;
	glm::vec3 uvec;
	glm::vec4 lightPos;
	std::string outputName;
	float fovy;

};