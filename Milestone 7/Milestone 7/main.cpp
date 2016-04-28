#include "glm/glm.hpp"
#include "RayTracer.h"
#include "Geometry.h"
#include <stdlib.h>
#include <vector>


int main(){

return 0;
}


void runScenes(){
	float rotY = 0;
	glm::vec3 scale = glm::vec3(1.5, 1, 1);
	glm::vec3 pos = glm::vec3(1, 0, 0);//used for x,z position

	std::vector<Geometry *> geos;
	geos.push_back(new Sphere());
	geos.push_back(new Cube());
	geos.push_back(new Triangle());
		
	for (int i = 0;i<3;i++){//for each type of shape
		//create Ray Tracer
		
	}
	
}