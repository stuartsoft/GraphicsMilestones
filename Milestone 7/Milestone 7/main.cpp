#include "glm/glm.hpp"
#include "RayTracer.h"
#include <stdlib.h>
#include <vector>

using std::to_string;

void runScenes();

const mat4 IDENTITY_MATRIX = mat4();
const mat4 DOUBLE_MATRIX(vec4(2.0f, 0.0f, 0.0f, 0.0f),
                         vec4(0.0f, 2.0f, 0.0f, 0.0f),
                         vec4(0.0f, 0.0f, 2.0f, 0.0f),
                         vec4(0.0f, 0.0f, 0.0f, 1.0f));
const mat4 TALLANDSKINNY_MATRIX(vec4(0.5f, 0.0f, 0.0f, 0.0f),
								vec4(0.0f, 2.0f, 0.0f, 0.0f),
								vec4(0.0f, 0.0f, 0.5f, 0.0f),
								vec4(0.0f, 0.0f, 0.0f, 1.0f));
const mat4 BACK5_MATRIX(vec4(1.0f, 0.0f, 0.0f, 0.0f),
                        vec4(0.0f, 1.0f, 0.0f, 0.0f),
                        vec4(0.0f, 0.0f, 1.0f, 0.0f),
                        vec4(0.0f, 0.0f, -5.0f, 1.0f));


int main(){

	runScenes();

return 0;
}


void runScenes(){
	std::vector<Geometry*> geos;
	geos.push_back(new Sphere());
	geos.push_back(new Cube());
	geos.push_back(new Triangle());

	std::vector<glm::vec3> camPos;
	camPos.push_back(glm::vec3(0, 0, 3));
	camPos.push_back(glm::vec3(-3, 0, 0));
	camPos.push_back(glm::vec3(1, 1, 1));

	const glm::vec2 imageSize = vec2(640, 420); 
	
	for (int i = 2;i<3;i++){//for each type of shape
		for (int j = 0;j<3;j++){//change camera position
			for (int k = 0;k<2;k++){//draw with and without object movement
				float rotY = 0.0f;
				glm::vec3 scale = glm::vec3(1, 1, 1);
				glm::vec3 geopos = glm::vec3(0, 0, 0);
				std::vector<Geometry*> geoList;
				geoList.push_back(geos[i]);
				glm::vec3 camPosition = camPos[j];
				glm::vec3 upVector = vec3(0, 1, 0);

				glm::vec3 camDir = -camPosition;
				if (k == 1){
					scale = glm::vec3(1.5f, 1, 1);
					geopos = glm::vec3(0, 1.0f, 0);
					rotY = 45.0f;
				}

				std::cout<<"geoType:\t"<<geoList[0]->getType()<<std::endl;
				std::cout<<"Scale:\t\t"<<scale.x<<", "<<scale.y<<", "<<scale.z<<", "<<std::endl;
				std::cout<<"geopos:\t\t"<<geopos.x<<", "<<geopos.y<<", "<<geopos.z<<", "<<std::endl;
				std::cout<<"camPosition:\t"<<camPosition.x<<", "<<camPosition.y<<", "<<camPosition.z<<", "<<std::endl;
				std::cout<<"camDir:\t\t"<<camDir.x<<", "<<camDir.y<<", "<<camDir.z<<std::endl;
				std::cout<<"upVector:\t"<<upVector.x<<", "<<upVector.y<<", "<<upVector.z<<", "<<std::endl;
				std::cout<<"rotY:\t\t"<<rotY<<std::endl;
				std::cout<<"-------------------------"<<std::endl;

				//TODO build raytracer with the above parameters and execute everything else 
				RayTracer * sceneOne = new RayTracer(camPosition, camDir, upVector, 60.0f, imageSize, geoList, geoList[0]->getType() + to_string(i) + to_string(j) + to_string(k) + ".bmp");

				sceneOne->rayGeneration(IDENTITY_MATRIX);

				delete sceneOne;
			}
		}
	}
	system("pause");
}