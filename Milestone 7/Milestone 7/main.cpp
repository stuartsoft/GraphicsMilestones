#include "glm/glm.hpp"
#include "RayTracer.h"
#include "Geometry.h"
#include <stdlib.h>
#include <vector>


int main(){

return 0;
}


void runScenes(){
	std::vector<Geometry*> geos;
	geos.push_back(new Sphere());
	geos.push_back(new Cube());
	geos.push_back(new Triangle());

	std::vector<glm::vec4> camPos;
	camPos.push_back(glm::vec4(0, 0, 3, 0));
	camPos.push_back(glm::vec4(-3, 0, 0, 0));
	camPos.push_back(glm::vec4(1, 1, 1, 0));
	

	for (int i = 0;i<3;i++){//for each type of shape
		for (int j = 0;j<3;j++){//change camera position
			for (int k = 0;k<2;k++){//draw with and without object movement
				float rotY = 0;
				glm::vec3 scale = glm::vec3(1, 1, 1);
				glm::vec3 geopos = glm::vec3(0, 0, 0);
				Geometry * geo = geos[i];
				glm::vec4 camPosition = camPos[j];

				glm::vec4 camDir = -camPosition;
				if (k == 1){
					scale = glm::vec3(1.5f, 1, 1);
					geopos = glm::vec3(0, 1.0f, 0);
					rotY = 45;
				}

				//TODO build raytracer with the above parameters and execute everything else 
			}
		}
	}
	
}