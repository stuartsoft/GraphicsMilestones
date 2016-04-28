#include "RayTracer.h"

const vec3 BACKGROUND_COLOR = vec3(0, 0, 0);
const vec3 MATERIAL_COLOR = vec3(85,45,125);
#define PI 3.14159f

double RayTracer::intersectionTests(Geometry* geom, vec4 E, vec4 P, mat4 TransMatrix){
	double result;

	if(geom->getType() == "cube"){
		result = Test_RayCubeIntersect(E, P, TransMatrix);
	}
	else if(geom->getType() == "triangle")
	{
		result = Test_RayPolyIntersect(E, P, geom->getpoints()[0], geom->getpoints()[1], geom->getpoints()[2], TransMatrix);
	}
	else if(geom->getType() == "sphere"){
		result = Test_RaySphereIntersect(E, P, TransMatrix);
	}

	return result;
}

vec4 RayTracer::getNormal(vec4 point, Geometry *geom, mat4 T){
	vec4 normal;

	if(geom->getType() == "triangle")
	{
		//bott left point
		vec3 point1 = vec3(-0.5, 0, 0);
		//bott right point
		vec3 point2 = vec3(0.5, 0, 0);
		//top point
		vec3 point3 = vec3(0, 1, 0);

		normal = T * vec4(cross(point2 - point1, point3 - point1), 1);
	}
	else if(geom->getType() == "sphere")
	{
		normal = point;
		normal.w = 1;
		normal = T * normal;
	}
	else if(geom->getType() == "Cube")
	{
		//front face
		vec4 norm1 = vec4(0,0,1,1);
		//back face
		vec4 norm2 = vec4(0,0,-1,1);
		//left face
		vec4 norm3 = vec4(-1,0,0,1);
		//right face
		vec4 norm4 = vec4(1,0,0,1);
		//top face
		vec4 norm5 = vec4(0,1,0,1);
		//bottom face
		vec4 norm6 = vec4(0,-1,0,1);

		if(abs(point.x - 0.5f) < 0.001)
			normal = T * norm4;
		if(abs(point.x + 0.5f) < 0.001)
			normal = T * norm3;
		if(abs(point.y - 0.5f) < 0.001)
			normal = T * norm4;
		if(abs(point.y + 0.5f) < 0.001)
			normal = T * norm6;
		if(abs(point.z - 0.5f) < 0.001)
			normal = T * norm1;
		if(abs(point.z + 0.5f) < 0.001)
			normal = T * norm2;
	}
	else 
	{
		//Misspelled the shape type
		std::cout << "ERROR: Incorrect geometry type\n";
		system("PAUSE");
		exit(0);
	}


	return normal;
}

vec3 RayTracer::shadowFeeler(vec4 intersectionPoint, mat4 T, vec4 normal){
	bool obstruction = false;
	float ka = 0.1f, kd = 0.5f;
	vec3 ambient, diffuse;
	vec3 colorCalc;
	Geometry *geom;

	for(unsigned i = 0; i < sceneGeom.size(); i++){
		double result = intersectionTests(sceneGeom[i], intersectionPoint, lightPos - intersectionPoint, T);

		if(result != -1 && result != 0){
			obstruction = true;
			geom = sceneGeom[i];
		}
	}

	//Blinn-phong code
	vec4 L = normalize(lightPos - intersectionPoint);

	vec4 V = normalize(vec4(eyePos, 0.0f) - intersectionPoint);

	vec4 H = normalize(L + V);

	ambient = MATERIAL_COLOR;

	if(obstruction)
	{
		diffuse = vec3(0,0,0);
	}
	else
	{
		diffuse = clamp(dot(L, normal), 0.0f, 1.0f) * MATERIAL_COLOR;
	}

	colorCalc = vec3(ka * ambient + kd * diffuse);

	return colorCalc;
}

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

	float tanFovy = tanf(fovy * (PI / 180.0f));

	V = up * tanFovy;

	H = U * tanFovy;

	BMP output;
	output.SetSize((int)imageSize.x, (int)imageSize.y);
	output.SetBitDepth(24);

	for (unsigned int x = 0;x<imageSize.x;x++){
		for (unsigned int y = 0;y<imageSize.y;y++){
			glm::vec3 D;
			float xPercent = (2.0f * x/(imageSize.x-1)-1);
			float yPercent = (2.0f * y/(imageSize.y-1)-1);
			D = m + (H * xPercent) + (V * yPercent);
			glm::vec3 R = D - eyePos;
			R = glm::normalize(R);

			//Initialize the t value to "infinity" and the intersection geometry to no geometry (NULL)
			double t = 1e26;
			Geometry * intersectGeometry = NULL;
			for(unsigned num=0; num < sceneGeom.size(); ++num)
			{
				double tOne = intersectionTests(sceneGeom[num], vec4(eyePos, 0), vec4(R, 0), transMatrix);

				//Find the closest intersection point
				if(tOne < t && tOne != -1)
				{
					t = tOne;
					intersectGeometry = sceneGeom[num];
				}
			}

			//Initialize the color to the background color
			vec3 color = BACKGROUND_COLOR;
			if(t != -1 && t != 1e26)
			{
				//vec4 iPoint = intersectionPoint(transMatrix, intersectGeometry, t);
				//color = shadowFeeler(iPoint, transMatrix, getNormal(iPoint, intersectGeometry, transMatrix));

				color = MATERIAL_COLOR;
			}

			//Put a cap on the color
			if(color.x > 255)
				color.x = 255;
			if(color.y > 255)
				color.y = 255;
			if(color.z > 255)
				color.z = 255;

			output(x, y)->Red = (ebmpBYTE)abs(color.x);
			output(x, y)->Green = (ebmpBYTE)abs(color.y);
			output(x, y)->Blue = (ebmpBYTE)abs(color.z);
		}
	}
	output.WriteToFile(outputName.c_str());
}

//The intersection point will have to be calculated differently for each geometry 
vec4 RayTracer::intersectionPoint(const mat4& transMatrix, Geometry * geom, double t)
{
	vec4 iPoint;

	if(geom->getType() == "Sphere")
	{

	}
	else if(geom->getType() == "Triangle")
	{

	}
	else if(geom->getType() == "Cube")
	{

	}

	return iPoint;
}

