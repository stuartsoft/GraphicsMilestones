#include <string>
#include "glm\glm.hpp"
#include <vector>

using namespace glm;

class Geometry{
protected:
	std::string type;
	std::vector<vec4> points;

public:
	virtual std::string getType() {return type;};
	virtual std::vector<vec4> getpoints() {return points;};
};

class Cube : protected Geometry{
private:

public:
	Cube(){
		type = "cube";
		//front bottom left
		points.push_back(vec4(-0.5f, -0.5f, 0.5f, 0.0f));
		//front top left
		points.push_back(vec4(-0.5f, 0.5f, 0.5f, 0.0f));
		//front top right
		points.push_back(vec4(0.5f, 0.5f, 0.5f, 0.0f));
		//front bottom right
		points.push_back(vec4(0.5f, -0.5f, 0.5f, 0.0f));
		//back bottom left
		points.push_back(vec4(-0.5f, -0.5f, -0.5f, 0.0f));
		//back top left
		points.push_back(vec4(-0.5f, 0.5f, -0.5f, 0.0f));
		//back top right
		points.push_back(vec4(0.5f, 0.5f, -0.5f, 0.0f));
		//back bottom left
		points.push_back(vec4(0.5f, -0.5f, -0.5f, 0.0f));
	};
};

class Triangle : protected Geometry{
private:

public:
	Triangle(){
		type = "triangle";

		points.push_back(vec4(-0.5f, -0.5f, 0.0f, 0.0f));
		points.push_back(vec4(0.5f, -0.5f, 0.0f, 0.0f));
		points.push_back(vec4(0.0f, 0.5f, 0.0f, 0.0f));
	};
};

class Sphere : protected Geometry{
public:
	Sphere(){
		type = "sphere";
	};
};