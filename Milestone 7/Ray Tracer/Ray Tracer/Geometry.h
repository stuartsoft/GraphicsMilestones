//Polymorphism used to assign the geometry 
#include "glm\glm.hpp"
#include <string>

class Geometry
{
public:
	Geometry(std::string t, glm::mat4 m);
	std::string getType() {return type;};
	glm::mat4 getPoints() {return M;};

	glm::vec3 getCoords() {return coordinates;};
private:
	std::string type;	
	glm::mat4 M;
	glm::vec3 coordinates;

};