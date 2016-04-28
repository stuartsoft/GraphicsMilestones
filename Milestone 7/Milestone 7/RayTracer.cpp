#include "RayTracer.h"

const vec3 BACKGROUND_COLOR = vec3(255, 255, 255);
#define PI 3.14159

void RayTracer::rayGeneration(const mat4& transMatrix){
	
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

	BMP output;
	output.SetSize(imageSize.x, imageSize.y);
	output.SetBitDepth(24);

	for (unsigned int x = 0;x<imageSize.x;x++){
		for (unsigned int y = 0;y<imageSize.y;y++){
			glm::vec3 D;
			float xPercent = (2.0f * x/(imageSize.x-1)-1);
			float yPercent = (2.0f * y/(imageSize.y-1)-1);
			D = m + (H * xPercent) + (V * yPercent);
			glm::vec3 R = D - eyePos;
			R = glm::normalize(R);

			//TODO call intersection tests on all objects and call shadow feelers
			double t = 1e26;
			for(unsigned num=0; num < geomList.size(); ++num)
			{
				double tOne = intersectionTests(geomList[num], eyePos, R, transMatrix);

				if(tOne < t)
					t = tOne;
			}
			vec3 color = BACKGROUND_COLOR;
			if(t != -1)
			{
				double sFeeler = shadowFeeler(t);
				color = calculateLighting(sFeeler);
			}

			output(x, y)->Red = abs(R.x) * 255;
			output(x, y)->Green = abs(R.y) * 255;
			output(x, y)->Blue = abs(R.z) * 255;
		}
	}

	output.WriteToFile("Output.bmp");
}

vec3 RayTracer::calculateLighting(double sFeeler)
{

}
