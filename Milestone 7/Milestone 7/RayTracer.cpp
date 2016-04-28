#include "RayTracer.h"

const vec3 BACKGROUND_COLOR = vec3(255, 255, 255);
#define PI 3.14159

void RayTracer::rayGeneration(int wid, int height){
	
	vec3 N = vdir;
	N = normalize(N);

	vec3 up = uvec;
	up = normalize(up);
	vec3 U;

	vec3 m = eyePos + N;

	U = glm::cross(N,up);
	U = normalize(U);

	vec3 V, H;
	float tanFovy = tan(fovy * (PI / 180.0f));
	V = up * tanFovy;

	H = U * tanFovy;

	for (unsigned int x = 0;x<wid;x++){
		for (unsigned int y = 0;y<height;y++){
			glm::vec3 D;
			float xPercent = (2.0f * x/(wid-1)-1);
			float yPercent = (2.0f * y/(height-1)-1);
			D = m + (H * xPercent) + (V * yPercent);
			glm::vec3 R = D - eyePos;
			R = glm::normalize(R);

			//TODO call intersection tests on all objects and call shadow feelers

		}
	}

}