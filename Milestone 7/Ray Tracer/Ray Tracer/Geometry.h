//Polymorphism used to assign the geometry 
#include "glm\glm.hpp"
#include <string>

class Geometry
{
public:
	Geometry(int type, glm::mat4 m);
	int getType() {return type;};
	glm::mat4 getPoints() {return M;};
private:
	int type;//0 = Sphere, 1 = Triangle, 2 = Cube
	glm::mat4 M;
};