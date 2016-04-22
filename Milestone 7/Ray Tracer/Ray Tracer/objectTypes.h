//Polymorphism used to assign the geometry 
#include "glm\glm.hpp"
#include <string>

class geometry
{
public:
	std::string getType() {return type;};
private:
	std::string type;
	vec3 coordinates;
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