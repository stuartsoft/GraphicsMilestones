#include "RayTracer.h"

double RayTracer::intersectionTests(Geometry* geom, vec4 E, vec4 P, mat4 TransMatrix){
	double result;

	if(geom->getType() == "cube"){
		result = Test_RayCubeIntersect(E, P, TransMatrix);
	}
	else if(geom->getType() == "triangle")
	{
		result = Test_RayPolyIntersect(E, P, geom->getpoints()[0], geom->getpoints()[1], geom->getpoints[2], TransMatrix);
	}
	else if(geom->getType() == "sphere"){
		result = Test_RaySphereIntersect(E, P, TransMatrix);
	}

	return result;
}

void RayTracer::shadowFeeler(vec4 intersectionPoint){
	bool obstruction = false;
	float ka = 0.1f, kd = 0.5f;
	vec3 ambient, diffuse;
	vec3 colorCalc = materialColor;
	vec3 defaultObjectColor = vec3(materialColor);

	for(int i = 0; i < sceneGeom.size(); i++){
		double result = intersectionTests(sceneGeom[i], intersectionPoint, lightpos - intersectionPoint, T);

		if(result != -1 && result != 0)
			obstruction = true;
	}


	//Blinn-phong code
	//If there is a shadow, then don't calculate the diffuse lighting
	vec4 L = normalize(lightPosition - Rpoint);

	vec4 V = normalize(cameraPosition - Rpoint);

	vec4 H = normalize(L + V);

	ambient = defaultObjectColor;

	if(obstruction)
	{
		diffuse = vec3(0,0,0);
	}
	else
	{
		diffuse = clamp(dot(L, normal), 0.0f, 1.0f) * defaultObjectColor;
	}

	colorCalc = vec3(ka * ambient + kd * diffuse);

	return colorCalc;

}