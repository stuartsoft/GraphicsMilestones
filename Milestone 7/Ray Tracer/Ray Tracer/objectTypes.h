//Polymorphism used to assign the geometry 
#include "glm\glm.hpp"
#include <string>

class geometry
{
public:
	std::string getType() {return type;};
	vec3 getCoords() {return coordinates;};
	vec4* getPoints() {return cubePoints;};
private:
	std::string type;
	vec3 coordinates;
	vec4 *cubePoints;
};

class cube: private geometry
{
public:
private:
};

class polygon: public geometry
{
public:
private:
};

class sphere: public geometry
{
public:
private:
};