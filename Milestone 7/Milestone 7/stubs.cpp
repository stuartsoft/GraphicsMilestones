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

	vec4 sphereCenter = vec4(0.0f,0.0f,0.0f,1.0f);//center of the sphere

	vec4 rayOrigin = glm::inverse(T) * P0;//origin of the ray
	vec4 vectorDirection = glm::inverse(T) * V0;

	float rad = 1.0f;//radius

	float solution;

	float a = glm::dot(vectorDirection,vectorDirection);
	float b = 0.0f;
	float c = 0.0f;
	//begin solving X comp

	vec4 originCenterDiff = vec4(rayOrigin.x - sphereCenter.x, rayOrigin.y - sphereCenter.y, rayOrigin.z - sphereCenter.z, rayOrigin.w - sphereCenter.w);
	//vec4 originCenterDiff = vec4(C.x - O.x, C.y - O.y, C.z - O.z, C.w - O.w);

	b = 2*glm::dot(vectorDirection,originCenterDiff);
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
	//double tNear = -1e26, tFar = 1e26;
	double tMin = -1e26, tMax = 1e26;
	double xtMin = 1e26, xtMax = -1e26, ytMin = 1e26, ytMax = -1e26, ztMin = 1e26, ztMax = -1e26;

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
		pData[i] = T * pData[i];
	}

	vec4 tP0 = P0;
	vec4 tV0 = V0;

	double invX = 1/(tV0.x);
	double invY = 1/(tV0.y);
	double invZ = 1/(tV0.z);

	//tP0 = P0 + (T * V0);

	//Right side tCalc
	//pData[4];	//Top right corner
	//pData[0];	//Bottom left Corner
	double temp;
	double tempXmin = -1e26, tempXmax = 1e26, tempYmin = -1e26, tempYmax = 1e26, tempZmin = -1e26, tempZmax = 1e26;
	if(tV0.x - tP0.x != 0)
	{
		tempXmin = (pData[4].x - tP0.x)*invX;
		tempXmax = (pData[0].x - tP0.x)*invX;
		if(tempXmin > tempXmax)
		{
			temp = tempXmax;
			tempXmax = tempXmin;
			tempXmin = temp;
		}
	}
	if(tV0.y - tP0.y != 0)
	{
		tempYmin = (pData[4].y - tP0.y)*invY;
		tempYmax = (pData[0].y - tP0.y)*invY;
		if(tempYmin > tempYmax)
		{
			temp = tempYmax;
			tempYmax = tempYmin;
			tempYmin = temp;
		}
	}
	if(tV0.z - tP0.z != 0)
	{
		tempZmin = (pData[4].z - tP0.z)*invZ;
		tempZmax = (pData[0].z - tP0.z)*invZ;
		if(tempZmin > tempZmax)
		{
			temp = tempZmax;
			tempZmax = tempZmin;
			tempZmin = temp;
		}
	}
	if(tempXmax != tempXmin)
	{
		if(tempXmin < xtMin) xtMin = tempXmin;
		if(tempXmax > xtMax) xtMax = tempXmax;
	}
	if(tempYmax != tempYmin)
	{
		if(tempYmin < ytMin) ytMin = tempYmin;
		if(tempYmax > ytMax) ytMax = tempYmax;
	}
	if(tempZmax != tempZmin)
	{
		if(tempZmin < ztMin) ztMin = tempZmin;
		if(tempZmax > ztMax) ztMax = tempZmax;
	}
	
	//Left side tCalc
	//pData[3];	//Top right corner 
	//pData[7];	//Bottom left corner
	tempXmin = -1e26, tempXmax = 1e26, tempYmin = -1e26, tempYmax = 1e26, tempZmin = -1e26, tempZmax = 1e26;
	if(tV0.x - tP0.x != 0)
	{
		tempXmin = (pData[3].x - tP0.x)*invX;
		tempXmax = (pData[7].x - tP0.x)*invX;
		if(tempXmin > tempXmax)
		{
			temp = tempXmax;
			tempXmax = tempXmin;
			tempXmin = temp;
		}
	}
	if(tV0.y - tP0.y != 0)
	{
		tempYmin = (pData[3].y - tP0.y)*invY;
		tempYmax = (pData[7].y - tP0.y)*invY;
		if(tempYmin > tempYmax)
		{
			temp = tempYmax;
			tempYmax = tempYmin;
			tempYmin = temp;
		}
	}
	if(tV0.z - tP0.z != 0)
	{
		tempZmin = (pData[3].z - tP0.z)*invZ;
		tempZmax = (pData[7].z - tP0.z)*invZ;
		if(tempZmin > tempZmax)
		{
			temp = tempZmax;
			tempZmax = tempZmin;
			tempZmin = temp;
		}
	}
	if(tempXmax != tempXmin)
	{
		if(tempXmin < xtMin) xtMin = tempXmin;
		if(tempXmax > xtMax) xtMax = tempXmax;
	}
	if(tempYmax != tempYmin)
	{
		if(tempYmin < ytMin) ytMin = tempYmin;
		if(tempYmax > ytMax) ytMax = tempYmax;
	}
	if(tempZmax != tempZmin)
	{
		if(tempZmin < ztMin) ztMin = tempZmin;
		if(tempZmax > ztMax) ztMax = tempZmax;
	}

	//Top side tCalc
	//pData[4];	//Top right corner 
	//pData[3];	//Bottom left corner
	tempXmin = -1e26, tempXmax = 1e26, tempYmin = -1e26, tempYmax = 1e26, tempZmin = -1e26, tempZmax = 1e26;
	if(tV0.x - tP0.x != 0)
	{
		tempXmin = (pData[4].x - tP0.x)*invX;
		tempXmax = (pData[3].x - tP0.x)*invX;
		if(tempXmin > tempXmax)
		{
			temp = tempXmax;
			tempXmax = tempXmin;
			tempXmin = temp;
		}
	}
	if(tV0.y - tP0.y != 0)
	{
		tempYmin = (pData[4].y - tP0.y)*invY;
		tempYmax = (pData[3].y - tP0.y)*invY;
		if(tempYmin > tempYmax)
		{
			temp = tempYmax;
			tempYmax = tempYmin;
			tempYmin = temp;
		}
	}
	if(tV0.z - tP0.z != 0)
	{
		tempZmin = (pData[4].z - tP0.z)*invZ;
		tempZmax = (pData[3].z - tP0.z)*invZ;
		if(tempZmin > tempZmax)
		{
			temp = tempZmax;
			tempZmax = tempZmin;
			tempZmin = temp;
		}
	}
	if(tempXmax != tempXmin)
	{
		if(tempXmin < xtMin) xtMin = tempXmin;
		if(tempXmax > xtMax) xtMax = tempXmax;
	}
	if(tempYmax != tempYmin)
	{
		if(tempYmin < ytMin) ytMin = tempYmin;
		if(tempYmax > ytMax) ytMax = tempYmax;
	}
	if(tempZmax != tempZmin)
	{
		if(tempZmin < ztMin) ztMin = tempZmin;
		if(tempZmax > ztMax) ztMax = tempZmax;
	}

	//Bottom side tCalc
	//pData[6];	//Top right corner 
	//pData[1];	//Bottom left corner
	tempXmin = -1e26, tempXmax = 1e26, tempYmin = -1e26, tempYmax = 1e26, tempZmin = -1e26, tempZmax = 1e26;
	if(tV0.x - tP0.x != 0)
	{
		tempXmin = (pData[6].x - tP0.x)*invX;
		tempXmax = (pData[1].x - tP0.x)*invX;
		if(tempXmin > tempXmax)
		{
			temp = tempXmax;
			tempXmax = tempXmin;
			tempXmin = temp;
		}
	}
	if(tV0.y - tP0.y != 0)
	{
		tempYmin = (pData[6].y - tP0.y)*invY;
		tempYmax = (pData[1].y - tP0.y)*invY;
		if(tempYmin > tempYmax)
		{
			temp = tempYmax;
			tempYmax = tempYmin;
			tempYmin = temp;
		}
	}
	if(tV0.z - tP0.z != 0)
	{
		tempZmin = (pData[6].z - tP0.z)*invZ;
		tempZmax = (pData[1].z - tP0.z)*invZ;
		if(tempZmin > tempZmax)
		{
			temp = tempZmax;
			tempZmax = tempZmin;
			tempZmin = temp;
		}
	}
	if(tempXmax != tempXmin)
	{
		if(tempXmin < xtMin) xtMin = tempXmin;
		if(tempXmax > xtMax) xtMax = tempXmax;
	}
	if(tempYmax != tempYmin)
	{
		if(tempYmin < ytMin) ytMin = tempYmin;
		if(tempYmax > ytMax) ytMax = tempYmax;
	}
	if(tempZmax != tempZmin)
	{
		if(tempZmin < ztMin) ztMin = tempZmin;
		if(tempZmax > ztMax) ztMax = tempZmax;
	}

	//Front side tCalc
	//pData[2];	//Top right corner
	//pData[1];	//Bottom left corner 
	tempXmin = -1e26, tempXmax = 1e26, tempYmin = -1e26, tempYmax = 1e26, tempZmin = -1e26, tempZmax = 1e26;
	if(tV0.x - tP0.x != 0)
	{
		tempXmin = (pData[2].x - tP0.x)*invX;
		tempXmax = (pData[1].x - tP0.x)*invX;
		if(tempXmin > tempXmax)
		{
			temp = tempXmax;
			tempXmax = tempXmin;
			tempXmin = temp;
		}
	}
	if(tV0.y - tP0.y != 0)
	{
		tempYmin = (pData[2].y - tP0.y)*invY;
		tempYmax = (pData[1].y - tP0.y)*invY;
		if(tempYmin > tempYmax)
		{
			temp = tempYmax;
			tempYmax = tempYmin;
			tempYmin = temp;
		}
	}
	if(tV0.z - tP0.z != 0)
	{
		tempZmin = (pData[2].z - tP0.z)*invZ;
		tempZmax = (pData[1].z - tP0.z)*invZ;
		if(tempZmin > tempZmax)
		{
			temp = tempZmax;
			tempZmax = tempZmin;
			tempZmin = temp;
		}
	}
	if(tempXmax != tempXmin)
	{
		if(tempXmin < xtMin) xtMin = tempXmin;
		if(tempXmax > xtMax) xtMax = tempXmax;
	}
	if(tempYmax != tempYmin)
	{
		if(tempYmin < ytMin) ytMin = tempYmin;
		if(tempYmax > ytMax) ytMax = tempYmax;
	}
	if(tempZmax != tempZmin)
	{
		if(tempZmin < ztMin) ztMin = tempZmin;
		if(tempZmax > ztMax) ztMax = tempZmax;
	}

	//Back side tCalc
	//pData[4];	//Top right corner 
	//pData[7];	//Bottom left corner
	tempXmin = -1e26, tempXmax = 1e26, tempYmin = -1e26, tempYmax = 1e26, tempZmin = -1e26, tempZmax = 1e26;
	if(tV0.x - tP0.x != 0)
	{
		tempXmin = (pData[4].x - tP0.x)*invX;
		tempXmax = (pData[7].x - tP0.x)*invX;
		if(tempXmin > tempXmax)
		{
			temp = tempXmax;
			tempXmax = tempXmin;
			tempXmin = temp;
		}
	}
	if(tV0.y - tP0.y != 0)
	{
		tempYmin = (pData[4].y - tP0.y)*invY;
		tempYmax = (pData[7].y - tP0.y)*invY;
		if(tempYmin > tempYmax)
		{
			temp = tempYmax;
			tempYmax = tempYmin;
			tempYmin = temp;
		}
	}
	if(tV0.z - tP0.z != 0)
	{
		tempZmin = (pData[4].z - tP0.z)*invZ;
		tempZmax = (pData[7].z - tP0.z)*invZ;
		if(tempZmin > tempZmax)
		{
			temp = tempZmax;
			tempZmax = tempZmin;
			tempZmin = temp;
		}
	}
	if(tempXmax != tempXmin)
	{
		if(tempXmin < xtMin) xtMin = tempXmin;
		if(tempXmax > xtMax) xtMax = tempXmax;
	}
	if(tempYmax != tempYmin)
	{
		if(tempYmin < ytMin) ytMin = tempYmin;
		if(tempYmax > ytMax) ytMax = tempYmax;
	}
	if(tempZmax != tempZmin)
	{
		if(tempZmin < ztMin) ztMin = tempZmin;
		if(tempZmax > ztMax) ztMax = tempZmax;
	}

	if(xtMin > tMin && xtMin > ytMin && xtMin > ztMin)
		tMin = xtMin;
	else if(ytMin > ztMin)
		tMin = ytMin;
	else 
		tMin = ztMin;
	if(xtMax < tMax && xtMax < ytMax && xtMax < ztMax)
		tMax = xtMax;
	else if(ytMax < ztMax)
		tMax = ytMax;
	else 
		tMax = ztMax;

	if(tMin > tMax)
		return -1;

	return tMin;
}
