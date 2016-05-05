#include "glm/glm.hpp"
#include "RayTracer.h"
#include <stdlib.h>
#include <vector>

using std::to_string;

void runScenes();

const mat4 IDENTITY_MATRIX = mat4();
const mat4 UPPER_LEFT(vec4(1.0f, 0.0f, 0.0f, 0.0f),
                         vec4(0.0f, 1.0f, 0.0f, 0.0f),
                         vec4(0.0f, 0.0f, 1.0f, 0.0f),
                         vec4(2.0f, 0.0f, 0.0f, 1.0f));

const mat4 UPPER_RIGHT(vec4(1.0f, 0.0f, 0.0f, 0.0f),
                         vec4(0.0f, 1.0f, 0.0f, 0.0f),
                         vec4(0.0f, 0.0f, 1.0f, 0.0f),
                         vec4(-2.0f, 1.0f, 0.0f, 1.0f));

const mat4 BOTTOM_MIDDLE(vec4(1.0f, 0.0f, 0.0f, 0.0f),
                         vec4(0.0f, 1.0f, 0.0f, 0.0f),
                         vec4(0.0f, 0.0f, 1.0f, 0.0f),
                         vec4(-1.0f, -1.0f, -1.0f, 1.0f));

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

const vec3 RED_COLOR(200, 20, 20);
const vec3 BLUE_COLOR(90, 20, 150);
const vec3 GREEN_COLOR(20, 200, 20);

int main(){

	runScenes();

return 0;
}


void runScenes(){
	std::vector<Geometry*> geos;

	//First Set 

	//Set reflection between 0 and 1
	geos.push_back(new Sphere());
	geos[0]->setReflectivity(0.3);
	geos.push_back(new Sphere());
	geos[1]->setReflectivity(0.6);
	geos.push_back(new Sphere());
	geos[2]->setReflectivity(0.3);

	std::vector<glm::vec3> camPos;
	camPos.push_back(glm::vec3(0, 0, 3));
	camPos.push_back(glm::vec3(-3, 0, 0));
	camPos.push_back(glm::vec3(1, 1, 1));

	const glm::vec2 imageSize = vec2(860, 640);
	glm::vec3 upVector = vec3(0, 1, 0);
	glm::vec4 lightPos = vec4(0, 0, 3, 0);	

	std::vector<vec3>objectColor;
	objectColor.push_back(RED_COLOR);
	objectColor.push_back(GREEN_COLOR);
	objectColor.push_back(BLUE_COLOR);
	
	for (int i = 0;i<1;i++){//for each type of shape
		for (int j = 0;j<camPos.size();j++){//change camera position
			for (int k = 0;k<1;k++){//draw with and without object movement
				float rotY = (0.0f);
				float fovY = (45.0f);
				glm::vec3 scale = glm::vec3(1, 1, 1);
				glm::vec3 geopos = glm::vec3(0, 0, 0);
				std::vector<Geometry*> geoList;
				geoList.push_back(geos[i]);
				glm::vec3 camPosition = camPos[j];

				std::vector<mat4>objectMovement;
				objectMovement.push_back(UPPER_RIGHT);
				objectMovement.push_back(BOTTOM_MIDDLE);
				objectMovement.push_back(UPPER_LEFT);

				glm::vec3 camDir = -camPosition;
				if (k == 1){
					scale = glm::vec3(1.0f, 1.5f, 1.0f);
					geopos = glm::vec3(0, 0.0f, 0);
					rotY = (45.0f);
				}

				mat4 trans = glm::translate(IDENTITY_MATRIX, geopos);
				mat4 rot = glm::rotate(IDENTITY_MATRIX, rotY, vec3(0,1,0));
				mat4 scaS = glm::scale(IDENTITY_MATRIX, scale);
				mat4 M = mat4() * trans * rot * scaS;

				objectMovement[0] = objectMovement[0] * trans * rot * scaS;
				objectMovement[1] = objectMovement[1] * trans * rot * scaS;
				objectMovement[2] = objectMovement[2] * trans * rot * scaS;
				
				RayTracer * sceneOne = new RayTracer(camPosition, camDir, upVector, fovY, imageSize, lightPos, objectMovement, objectColor, geos, geoList[0]->getType() + " S" + to_string(i) + " C" + to_string(j) + " M" +to_string(k) + ".bmp");

				sceneOne->rayGeneration(M, 0);

				delete sceneOne;
			}
		}
	}

	//Second Set 
	geos[0] = (new Cube());
	geos[0]->setReflectivity(0.0);
	geos[1] = (new Triangle());
	geos[1]->setReflectivity(0.0);
	geos[2] = (new Sphere());
	geos[2]->setReflectivity(0.3);

	for (int i = 0;i<1;i++){//for each type of shape
		for (int j = 0;j<camPos.size();j++){//change camera position
			for (int k = 0;k<1;k++){//draw with and without object movement
				float rotY = (0.0f);
				float fovY = (45.0f);
				glm::vec3 scale = glm::vec3(1, 1, 1);
				glm::vec3 geopos = glm::vec3(0, 0, 0);
				std::vector<Geometry*> geoList;
				geoList.push_back(geos[i]);
				glm::vec3 camPosition = camPos[j];

				std::vector<mat4>objectMovement;
				objectMovement.push_back(UPPER_RIGHT);
				objectMovement.push_back(BOTTOM_MIDDLE);
				objectMovement.push_back(UPPER_LEFT);

				glm::vec3 camDir = -camPosition;
				if (k == 1){
					scale = glm::vec3(1.0f, 1.5f, 1.0f);
					geopos = glm::vec3(0, 0.0f, 0);
					rotY = (45.0f);
				}

				mat4 trans = glm::translate(IDENTITY_MATRIX, geopos);
				mat4 rot = glm::rotate(IDENTITY_MATRIX, rotY, vec3(0,1,0));
				mat4 scaS = glm::scale(IDENTITY_MATRIX, scale);
				mat4 M = mat4() * trans * rot * scaS;

				objectMovement[0] = objectMovement[0] * trans * rot * scaS;
				objectMovement[1] = objectMovement[1] * trans * rot * scaS;
				objectMovement[2] = objectMovement[2] * trans * rot * scaS;
				
				RayTracer * sceneOne = new RayTracer(camPosition, camDir, upVector, fovY, imageSize, lightPos, objectMovement, objectColor, geos, geoList[0]->getType() + " S" + to_string(i) + " C" + to_string(j) + " M" +to_string(k) + ".bmp");

				sceneOne->rayGeneration(M, 0);

				delete sceneOne;
			}
		}
	}
}