/**
  This testing framework has been developed/overhauled over time, primarily by:
  Chris Czyzewicz
  Ben Sunshine-Hill
  Cory Boatright 
  
  While the three were PhD students at UPenn (through 2013).  This particular version has some
  modifications by Cory since joining the faculty of Grove City College.
  
  Last revised 4/15/2015
*/

#include "stubs.h"

using namespace glm;

double** tCalc(const vec4& P0, const vec4& V0, const vec4& TR, const vec4& BL);

double Test_RaySphereIntersect(const vec4& P0, const vec4& V0, const mat4& T) {
	// TODO fill this in.
	// See the documentation of this function in stubs.h.

	//perform quadratic solution for x, y, z components individually.
	//return the smallest t value if there is a valid intersection

	vec4 C = vec4(0.0f,0.0f,0.0f,1.0f);//center of the sphere

	vec4 O = glm::inverse(T) * P0;//origin of the ray
	vec4 V = glm::inverse(T) * V0;

	float rad = 1.0f;//radius

	float solution;

	float a = glm::dot(V,V);
	float b = 0.0f;
	float c = 0.0f;
	//begin solving X comp

	vec4 originCenterDiff = vec4(O.x - C.x, O.y - C.y, O.z - C.z, O.w - C.w);
	//vec4 originCenterDiff = vec4(C.x - O.x, C.y - O.y, C.z - O.z, C.w - O.w);

	b = 2*glm::dot(V,originCenterDiff);
	c = glm::dot(originCenterDiff, originCenterDiff) - rad*rad;
	//check discriminant
	float disc = b*b - 4*a*c;
	if (disc < 0)// no solution
		return -1;
	else if (disc == 0){// one solution
		float sol1 = -b/(2*a);
		solution = sol1;
	}
	else{
		float sol1 = (-b + sqrt(disc))/(2*a);
		float sol2 = (-b - sqrt(disc))/(2*a);
		if (sol1 < sol2)
			solution = sol1;
		else
			solution = sol2;
	}

	if (solution < 0)//if solution is negative then it's not actually a solution
		return -1;
	return solution;
}

double Test_RayPolyIntersect(const vec4& P0, const vec4& V0, const vec4& p1, const vec4& p2, const vec4& p3, const mat4& T) {
	vec4 normal;
	double tCheck;

	vec4 planeVec1 = p2 - p1;
	vec4 planeVec2 = p3 - p1;

	normal = vec4(cross(vec3(planeVec2), vec3(planeVec1)), 0);

	vec4 objectSpace_PmE = inverse(T) * V0;
	vec4 objectSpace_E = inverse(T) * P0;

	float denom = dot(normal, objectSpace_PmE);

	if(denom != 0)
		tCheck = dot(normal, p3 - objectSpace_E) / denom;

	if(tCheck >= 0){
		vec4 Rpoint = objectSpace_E + vec4(vec3(tCheck), 1) * objectSpace_PmE;


		float S = sqrt((p1.y * p2.z + p1.z * p3.y + p2.y * p3.z - p3.y * p2.z - p3.z * p1.y - p2.y * p1.z) * (p1.y * p2.z + p1.z * p3.y + p2.y * p3.z - p3.y * p2.z - p3.z * p1.y - p2.y * p1.z) + 
				  (p1.z * p2.x + p1.x * p3.z + p2.z * p3.x - p3.z * p2.x - p3.x * p1.z - p2.z * p1.x) * (p1.z * p2.x + p1.x * p3.z + p2.z * p3.x - p3.z * p2.x - p3.x * p1.z - p2.z * p1.x) + 
				  (p1.x * p2.y + p1.y * p3.x + p2.x * p3.y - p3.x * p2.y - p3.y * p1.x - p2.x * p1.y) * (p1.x * p2.y + p1.y * p3.x + p2.x * p3.y - p3.x * p2.y - p3.y * p1.x - p2.x * p1.y)) / 2;

		float S1 = sqrt((Rpoint.y * p2.z + Rpoint.z * p3.y + p2.y * p3.z - p3.y * p2.z - p3.z * Rpoint.y - p2.y * Rpoint.z) * (Rpoint.y * p2.z + Rpoint.z * p3.y + p2.y * p3.z - p3.y * p2.z - p3.z * Rpoint.y - p2.y * Rpoint.z) + 
				  (Rpoint.z * p2.x + Rpoint.x * p3.z + p2.z * p3.x - p3.z * p2.x - p3.x * Rpoint.z - p2.z * Rpoint.x) * (Rpoint.z * p2.x + Rpoint.x * p3.z + p2.z * p3.x - p3.z * p2.x - p3.x * Rpoint.z - p2.z * Rpoint.x) + 
				  (Rpoint.x * p2.y + Rpoint.y * p3.x + p2.x * p3.y - p3.x * p2.y - p3.y * Rpoint.x - p2.x * Rpoint.y) * (Rpoint.x * p2.y + Rpoint.y * p3.x + p2.x * p3.y - p3.x * p2.y - p3.y * Rpoint.x - p2.x * Rpoint.y)) / (S*2);

		float S2 = sqrt((p1.y * Rpoint.z + p1.z * p3.y + Rpoint.y * p3.z - p3.y * Rpoint.z - p3.z * p1.y - Rpoint.y * p1.z) * (p1.y * Rpoint.z + p1.z * p3.y + Rpoint.y * p3.z - p3.y * Rpoint.z - p3.z * p1.y - Rpoint.y * p1.z) + 
				  (p1.z * Rpoint.x + p1.x * p3.z + Rpoint.z * p3.x - p3.z * Rpoint.x - p3.x * p1.z - Rpoint.z * p1.x) * (p1.z * Rpoint.x + p1.x * p3.z + Rpoint.z * p3.x - p3.z * Rpoint.x - p3.x * p1.z - Rpoint.z * p1.x) + 
				  (p1.x * Rpoint.y + p1.y * p3.x + Rpoint.x * p3.y - p3.x * Rpoint.y - p3.y * p1.x - Rpoint.x * p1.y) * (p1.x * Rpoint.y + p1.y * p3.x + Rpoint.x * p3.y - p3.x * Rpoint.y - p3.y * p1.x - Rpoint.x * p1.y)) / (S*2);

		float S3 = sqrt((p1.y * p2.z + p1.z * Rpoint.y + p2.y * Rpoint.z - Rpoint.y * p2.z - Rpoint.z * p1.y - p2.y * p1.z) * (p1.y * p2.z + p1.z * Rpoint.y + p2.y * Rpoint.z - Rpoint.y * p2.z - Rpoint.z * p1.y - p2.y * p1.z) + 
				  (p1.z * p2.x + p1.x * Rpoint.z + p2.z * Rpoint.x - Rpoint.z * p2.x - Rpoint.x * p1.z - p2.z * p1.x) * (p1.z * p2.x + p1.x * Rpoint.z + p2.z * Rpoint.x - Rpoint.z * p2.x - Rpoint.x * p1.z - p2.z * p1.x) + 
				  (p1.x * p2.y + p1.y * Rpoint.x + p2.x * Rpoint.y - Rpoint.x * p2.y - Rpoint.y * p1.x - p2.x * p1.y) * (p1.x * p2.y + p1.y * Rpoint.x + p2.x * Rpoint.y - Rpoint.x * p2.y - Rpoint.y * p1.x - p2.x * p1.y)) / (S*2);

		if(std::abs(S3 + S2 + S1 - 1) < 1e-3)
			return tCheck;
	}

	return -1;
}

// This function should return the smallest positive t-value of the intersection
// (a point such that P0+t*V0 intersects the cube), or -1 if there is no
// intersection.
// P0 is the position from which the ray emanates; V0 is the
// direction of the ray.
// matrix is the transformation matrix of the cube
// A unit cube extends from -0.5 to 0.5 in all axes.
double Test_RayCubeIntersect(const vec4& P0, const vec4& V0, const mat4& T) {
	//double xSides[6][2];
	//double ySides[6][2];
	//double zSides[6][2];

	//double tNear = -1e26, tFar = 1e26;
	double tMin = -1e26, tMax = 1e26;
	double xtMin = -1e26, xtMax = 1e26, ytMin = -1e26, ytMax = 1e26, ztMin = -1e26, ztMax = 1e26;

	//Set points for the cube
	vec4 pData[8];

	pData[0] = vec4(0.5f, -0.5f, -0.5f, 1.0f);		//front bottom right
	pData[1] = vec4(-0.5f, -0.5f, -0.5f, 1.0f);		//front bottom left
	pData[2] = vec4(0.5f, 0.5f, -0.5f, 1.0f);		//front top right
	pData[3] = vec4(-0.5f, 0.5f, -0.5f, 1.0f);		//front top left
	pData[4] = vec4(0.5f, 0.5f, 0.5f, 1.0f);		//back top right
	pData[5] = vec4(-0.5f, 0.5f, 0.5f, 1.0f);		//back top left
	pData[6] = vec4(0.5f, -0.5f, 0.5f, 1.0f);		//back bottom right
	pData[7] = vec4(-0.5f, -0.5f, 0.5f, 1.0f);		//back bottom left

	//Translate the cube
	for(unsigned i=0; i < 8; i++)
	{
		pData[i] = pData[i];
	}

	vec4 tP0 = inverse(T) * P0;
	vec4 tV0 = inverse(T) * V0;

	double invX = 1/(tV0.x - tP0.x);
	double invY = 1/(tV0.y - tP0.y);
	double invZ = 1/(tV0.z - tP0.z);

	int missCount = 0;
	if((tP0.x + tV0.x < pData[4].x || tP0.x + tV0.x > pData[0].x))
		if((tP0.x + tV0.x < pData[1].x || tP0.x + tV0.x > pData[5].x))
			if((tP0.x + tV0.x < pData[3].x || tP0.x + tV0.x > pData[4].x))
				if((tP0.x + tV0.x < pData[1].x || tP0.x + tV0.x > pData[6].x))
					if((tP0.x + tV0.x < pData[1].x || tP0.x + tV0.x > pData[2].x))
						if((tP0.x + tV0.x < pData[7].x || tP0.x + tV0.x > pData[4].x))
							missCount++;
	if((tP0.y + tV0.y < pData[4].y || tP0.y + tV0.y  > pData[0].y))
		if((tP0.y + tV0.y  < pData[1].y || tP0.y + tV0.y  > pData[5].y))
			if((tP0.y + tV0.y  < pData[3].y || tP0.y + tV0.y  > pData[4].y))
				if((tP0.y + tV0.y  < pData[1].y || tP0.y + tV0.y  > pData[6].y))
					if((tP0.y + tV0.y  < pData[1].y || tP0.y + tV0.y  > pData[2].y))
						if((tP0.y + tV0.y  < pData[7].y || tP0.y + tV0.y  > pData[4].y))
							missCount++;
	if((tP0.z + tV0.z < pData[4].z || tP0.z + tV0.z  > pData[0].z))
		if((tP0.z + tV0.z  < pData[1].z || tP0.z + tV0.z  > pData[5].z))
			if((tP0.z + tV0.z  < pData[3].z || tP0.z + tV0.z  > pData[4].z))
				if((tP0.z + tV0.z  < pData[1].z || tP0.z + tV0.z  > pData[6].z))
					if((tP0.z + tV0.z  < pData[1].z || tP0.z + tV0.z  > pData[2].z))
						if((tP0.z + tV0.z  < pData[7].z || tP0.z + tV0.z  > pData[4].z))
							missCount++;
			
	if(missCount >= 2)
		return -1;

	//Right side tCalc
	//pData[4];	//Top right corner
	//pData[0];	//Bottom left Corner
	
	if(tV0.x - tP0.x > 0)
	{
		xtMin = (pData[4].x - tP0.x)*invX;
		xtMax = (pData[0].x - tP0.x)*invX;
	}
	else if(tV0.x - tP0.x < 0)
	{
		xtMin = (pData[4].x - tP0.x)*invX;
		xtMax = (pData[0].x - tP0.x)*invX;
	}
	if(tV0.y - tP0.y > 0)
	{
		ytMin = (pData[0].y - tP0.y)*invY;
		ytMax = (pData[4].y - tP0.y)*invY;
	}
	else if(tV0.y - tP0.y < 0)
	{
		ytMin = (pData[4].y - tP0.y)*invY;
		ytMax = (pData[0].y - tP0.y)*invY;
	}
	if(!((xtMin > ytMax) || (ytMin < xtMax)))
	{
		if(ytMin > xtMin)
			xtMin = ytMin;
		if(ytMax < xtMax)
			xtMax = ytMax;
	}
	if(tV0.z - tP0.z > 0)
	{
		ztMin = (pData[0].z - tP0.z)*invZ;
		ztMax = (pData[4].z - tP0.z)*invZ;
	}
	else if(tV0.z - tP0.z < 0)
	{
		ztMin = (pData[4].z - tP0.z)*invZ;
		ztMax = (pData[0].z - tP0.z)*invZ;
	}
	if(!((xtMin > ztMax) || (ztMin > xtMax))) 
	{
		if(ztMin > xtMin)
			xtMin = ztMin;
		if(ztMax < tMax)
			xtMax = ztMax;
	}
	if(xtMin != xtMax)
	{
		if(xtMin > tMin && xtMin > 0)
			tMin = xtMin;
		if(xtMax < tMax && xtMax > 0)
			tMax = xtMax;
	}
	
	//Left side tCalc
	//pData[3];	//Top right corner 
	//pData[7];	//Bottom left corner 
	if(tV0.x - tP0.x > 0)
	{
		xtMin = (pData[3].x - tP0.x)*invX;
		xtMax = (pData[7].x - tP0.x)*invX;
	}
	else if(tV0.x - tP0.x < 0)
	{
		xtMin = (pData[7].x - tP0.x)*invX;
		xtMax = (pData[3].x - tP0.x)*invX;
	}
	if(tV0.y - tP0.y > 0)
	{
		ytMin = (pData[3].y - tP0.y)*invY;
		ytMax = (pData[7].y - tP0.y)*invY;
	}
	else if(tV0.y - tP0.y < 0)
	{
		ytMin = (pData[7].y - tP0.y)*invY;
		ytMax = (pData[3].y - tP0.y)*invY;
	}
	if(!((xtMin > ytMax) || (ytMin < xtMax)))
	{
		if(ytMin > xtMin)
			xtMin = ytMin;
		if(ytMax < xtMax)
			xtMax = ytMax;
	}
	if(tV0.z - tP0.z > 0)
	{
		ztMin = (pData[3].z - tP0.z)*invZ;
		ztMax = (pData[7].z - tP0.z)*invZ;
	}
	else if(tV0.z - tP0.z < 0)
	{
		ztMin = (pData[7].z - tP0.z)*invZ;
		ztMax = (pData[3].z - tP0.z)*invZ;
	}
	if(!((xtMin > ztMax) || (ztMin > xtMax))) 
	{
		if(ztMin > xtMin)
			xtMin = ztMin;
		if(ztMax < tMax)
			xtMax = ztMax;
	}

	if(xtMin != xtMax)
	{
		if(xtMin > tMin && xtMin > 0)
			tMin = xtMin;
		if(xtMax < tMax && xtMax > 0)
			tMax = xtMax;
	}


	//Top side tCalc
	//pData[4];	//Top right corner 
	//pData[3];	//Bottom left corner
	if(tV0.x - tP0.x > 0)
	{
		xtMin = (pData[3].x - tP0.x)*invX;
		xtMax = (pData[4].x - tP0.x)*invX;
	}
	else if(tV0.x - tP0.x < 0)
	{
		xtMin = (pData[4].x - tP0.x)*invX;
		xtMax = (pData[3].x - tP0.x)*invX;
	}
	if(tV0.y - tP0.y > 0)
	{
		ytMin = (pData[3].y - tP0.y)*invY;
		ytMax = (pData[4].y - tP0.y)*invY;
	}
	else if(tV0.y - tP0.y < 0)
	{
		ytMin = (pData[4].y - tP0.y)*invY;
		ytMax = (pData[3].y - tP0.y)*invY;
	}
	if(!((xtMin > ytMax) || (ytMin < xtMax)))
	{
		if(ytMin > xtMin)
			xtMin = ytMin;
		if(ytMax < xtMax)
			xtMax = ytMax;
	}
	if(tV0.z - tP0.z > 0)
	{
		ztMin = (pData[3].z - tP0.z)*invZ;
		ztMax = (pData[4].z - tP0.z)*invZ;
	}
	else if(tV0.z - tP0.z < 0)
	{
		ztMin = (pData[4].z - tP0.z)*invZ;
		ztMax = (pData[3].z - tP0.z)*invZ;
	}
	if(!((xtMin > ztMax) || (ztMin > xtMax))) 
	{
		if(ztMin > xtMin)
			xtMin = ztMin;
		if(ztMax < tMax)
			xtMax = ztMax;
	}

	if(xtMin != xtMax)
	{
		if(xtMin > tMin && xtMin > 0)
			tMin = xtMin;
		if(xtMax < tMax && xtMax > 0)
			tMax = xtMax;
	}

	//Bottom side tCalc
	//pData[6];	//Top right corner 
	//pData[1];	//Bottom left corner
	if(tV0.x - tP0.x > 0)
	{
		xtMin = (pData[1].x - tP0.x)*invX;
		xtMax = (pData[6].x - tP0.x)*invX;
	}
	else if(tV0.x - tP0.x < 0)
	{
		xtMin = (pData[6].x - tP0.x)*invX;
		xtMax = (pData[1].x - tP0.x)*invX;
	}
	if(tV0.y - tP0.y > 0)
	{
		ytMin = (pData[1].y - tP0.y)*invY;
		ytMax = (pData[6].y - tP0.y)*invY;
	}
	else if(tV0.y - tP0.y < 0)
	{
		ytMin = (pData[6].y - tP0.y)*invY;
		ytMax = (pData[1].y - tP0.y)*invY;
	}
	if(!((xtMin > ytMax) || (ytMin < xtMax)))
	{
		if(xtMin > tMin && xtMin > 0)
			tMin = xtMin;
		if(xtMax < tMax && xtMax > 0)
			tMax = xtMax;
	}
	if(tV0.z - tP0.z > 0)
	{
		ztMin = (pData[1].z - tP0.z)*invZ;
		ztMax = (pData[6].z - tP0.z)*invZ;
	}
	else if(tV0.z - tP0.z < 0)
	{
		ztMin = (pData[6].z - tP0.z)*invZ;
		ztMax = (pData[1].z - tP0.z)*invZ;
	}
	if(!((xtMin > ztMax) || (ztMin > xtMax))) 
	{
		if(ztMin > xtMin)
			xtMin = ztMin;
		if(ztMax < tMax)
			xtMax = ztMax;
	}
	if(xtMin != xtMax)
	{
		if(xtMin > tMin && xtMin > 0)
			tMin = xtMin;
		if(xtMax < tMax && xtMax > 0)
			tMax = xtMax;
	}

	//Front side tCalc
	//pData[2];	//Top right corner
	//pData[1];	//Bottom left corner 
	if(tV0.x - tP0.x > 0)
	{
		xtMin = (pData[1].x - tP0.x)*invX;
		xtMax = (pData[2].x - tP0.x)*invX;
	}
	else if(tV0.x - tP0.x < 0)
	{
		xtMin = (pData[2].x - tP0.x)*invX;
		xtMax = (pData[1].x - tP0.x)*invX;
	}
	if(tV0.y - tP0.y > 0)
	{
		ytMin = (pData[1].y - tP0.y)*invY;
		ytMax = (pData[2].y - tP0.y)*invY;
	}
	else if(tV0.y - tP0.y < 0)
	{
		ytMin = (pData[2].y - tP0.y)*invY;
		ytMax = (pData[1].y - tP0.y)*invY;
	}
	if(!((xtMin > ytMax) || (ytMin < xtMax)))
	{
		if(ytMin > xtMin)
			xtMin = ytMin;
		if(ytMax < xtMax)
			xtMax = ytMax;
	}
	if(tV0.z - tP0.z > 0)
	{
		ztMin = (pData[1].z - tP0.z)*invZ;
		ztMax = (pData[2].z - tP0.z)*invZ;
	}
	else if(tV0.z - tP0.z < 0)
	{
		ztMin = (pData[2].z - tP0.z)*invZ;
		ztMax = (pData[1].z - tP0.z)*invZ;
	}
	if(!((xtMin > ztMax) || (ztMin > xtMax))) 
	{
		if(ztMin > xtMin)
			xtMin = ztMin;
		if(ztMax < tMax)
			xtMax = ztMax;
	}
	if(xtMin != xtMax)
	{
		if(xtMin > tMin && xtMin > 0)
			tMin = xtMin;
		if(xtMax < tMax && xtMax > 0)
			tMax = xtMax;
	}

	//Back side tCalc
	//pData[4];	//Top right corner 
	//pData[7];	//Bottom left corner
	if(tV0.x - tP0.x > 0)
	{
		xtMin = (pData[7].x - tP0.x)*invX;
		xtMax = (pData[4].x - tP0.x)*invX;
	}
	else if(tV0.x - tP0.x < 0)
	{
		xtMin = (pData[4].x - tP0.x)*invX;
		xtMax = (pData[7].x - tP0.x)*invX;
	}
	if(tV0.y - tP0.y > 0)
	{
		ytMin = (pData[7].y - tP0.y)*invY;
		ytMax = (pData[4].y - tP0.y)*invY;
	}
	else if(tV0.y - tP0.y < 0)
	{
		ytMin = (pData[4].y - tP0.y)*invY;
		ytMax = (pData[7].y - tP0.y)*invY;
	}
	if(!((xtMin > ytMax) || (ytMin < xtMax)))
	{
		if(ytMin > xtMin)
			xtMin = ytMin;
		if(ytMax < xtMax)
			xtMax = ytMax;
	}
	if(tV0.z - tP0.z > 0)
	{
		ztMin = (pData[7].z - tP0.z)*invZ;
		ztMax = (pData[4].z - tP0.z)*invZ;
	}
	else if(tV0.z - tP0.z < 0)
	{
		ztMin = (pData[4].z - tP0.z)*invZ;
		ztMax = (pData[7].z - tP0.z)*invZ;
	}
	if(!((xtMin > ztMax) || (ztMin > xtMax))) 
	{
		if(ztMin > xtMin)
			xtMin = ztMin;
		if(ztMax < tMax)
			xtMax = ztMax;
	}
	if(xtMin != xtMax)
	{
		if(xtMin > tMin && xtMin > 0)
			tMin = xtMin;
		if(xtMax < tMax && xtMax > 0)
			tMax = xtMax;
	}

	if(tMin >= tMax)
		return -1;

	return tMin;
}