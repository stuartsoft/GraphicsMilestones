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

	//STUART

	if (solution< 0)//if solution is negative then it's not actually a solution
		return -1;
	return solution;
}

double Test_RayPolyIntersect(const vec4& P0, const vec4& V0, const vec4& p1, const vec4& p2, const vec4& p3, const mat4& T) {
	// TODO fill this in.
	// See the documentation of this function in stubs.h.

	//NATHAN

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
	double xMin, xMax;	//tNear and tFar for x
	double yMin, yMax;	//tNear and tFar for y
	double zMin, zMax;	//tNear and tFar for z

	double xSides[6][2];
	double ySides[6][2];
	double zSides[6][2];

	//Set points for the cube
	vec4 pData[8];
	pData[0] = vec4(- 0.5f, 0.0f,  0.5f, 1.0f);		//front bottom right
	pData[1] = vec4(0.5f, 0.0f, 0.5f, 1.0f);		//front bottom left
	pData[2] = vec4(- 0.5f, 1.0f, 0.5f, 1.0f);		//front top right
	pData[3] = vec4(0.5f, 1.0f, 0.5f, 1.0f);		//front top left
	pData[4] = vec4(- 0.5f, 1.0f, - 0.5f, 1.0f);	//back top right
	pData[5] = vec4(0.5f, 1.0f, - 0.5f, 1.0f);		//back top left
	pData[6] = vec4(- 0.5f, 0.0f, - 0.5f, 1.0f);	//back bottom right
	pData[7] = vec4(0.5f, 0.0f, - 0.5f, 1.0f);		//back bottom left

	//Translate the cube
	for(unsigned i=0; i < 8; i++)
	{
		pData[i] = T * pData[i];
	}

	//Right side tCalc
	//pData[4];	//Top right corner
	//pData[0];	//Bottom left Corner 
	double ** rightCalc = tCalc(P0, V0, pData[4], pData[0]);
	xSides[0][0] = rightCalc[0][0];
	xSides[0][1] = rightCalc[0][1];
	ySides[0][0] = rightCalc[1][0];
	ySides[0][1] = rightCalc[1][1];
	zSides[0][0] = rightCalc[2][0];
	zSides[0][1] = rightCalc[2][1];

	//Left side tCalc
	//pData[2];	//Top right corner 
	//pData[7];	//Bottom left corner 
	double ** leftCalc = tCalc(P0, V0, pData[2], pData[7]);
	xSides[1][0] = leftCalc[0][0];
	xSides[1][1] = leftCalc[0][1];
	ySides[1][0] = leftCalc[1][0];
	ySides[1][1] = leftCalc[1][1];
	zSides[1][0] = leftCalc[2][0];
	zSides[1][1] = leftCalc[2][1];

	//Top side tCalc
	//pData[4];	//Top right corner 
	//pData[3];	//Bottom left corner
	double ** topCalc = tCalc(P0, V0, pData[4], pData[3]);
	xSides[2][0] = topCalc[0][0];
	xSides[2][1] = topCalc[0][1];
	ySides[2][0] = topCalc[1][0];
	ySides[2][1] = topCalc[1][1];
	zSides[2][0] = topCalc[2][0];
	zSides[2][1] = topCalc[2][1];

	//Bottom side tCalc
	//pData[6];	//Top right corner 
	//pData[1];	//Bottom left corner
	double ** bottomCalc = tCalc(P0, V0, pData[6], pData[1]);
	xSides[3][0] = bottomCalc[0][0];
	xSides[3][1] = bottomCalc[0][1];
	ySides[3][0] = bottomCalc[1][0];
	ySides[3][1] = bottomCalc[1][1];
	zSides[3][0] = bottomCalc[2][0];
	zSides[3][1] = bottomCalc[2][1];

	//Front side tCalc
	//pData[2];	//Top right corner
	//pData[1];	//Bottom left corner 
	double ** frontCalc = tCalc(P0, V0, pData[2], pData[1]);
	xSides[4][0] = frontCalc[0][0];
	xSides[4][1] = frontCalc[0][1];
	ySides[4][0] = frontCalc[1][0];
	ySides[4][1] = frontCalc[1][1];
	zSides[4][0] = frontCalc[2][0];
	zSides[4][1] = frontCalc[2][1];

	//Back side tCalc
	//pData[4];	//Top right corner 
	//pData[7];	//Bottom left corner
	double ** backCalc = tCalc(P0, V0, pData[4], pData[7]);
	xSides[5][0] = backCalc[0][0];
	xSides[5][1] = backCalc[0][1];
	ySides[5][0] = backCalc[1][0];
	ySides[5][1] = backCalc[1][1];
	zSides[5][0] = backCalc[2][0];
	zSides[5][1] = backCalc[2][1];

	xMin = xSides[0][0]; xMax = xSides[0][1];
	yMin = ySides[0][0]; yMax = ySides[0][1];
	zMin = zSides[0][0]; zMax = zSides[0][1];
	
	//Find xNear xFar
	for(unsigned i=1; i < 6; i++)
	{
		if(xSides[i][0] < xMin)
			xMin = xSides[i][0];
		if(xSides[i][1] > xMax)
			xMax = xSides[i][1];
	}
	//Find yNear yFar
	for(unsigned i=1; i < 6; i++)
	{
		if(ySides[i][0] < yMin)
			yMin = ySides[i][0];
		if(xSides[i][1] > xMax)
			yMax = ySides[i][1];
	}
	//Find zNear zFar
	for(unsigned i=1; i < 6; i++)
	{
		if(zSides[i][0] < zMin)
			zMin = zSides[i][0];
		if(zSides[i][1] > zMax)
			zMax = zSides[i][1];
	}

	double result;		//Storage for the result

	//If farthest < nearest, the cube misses 
	//Otherwise, t = nearest 
	if((xMin >= xMax && xMin != 1e26 && xMin > 0) || (yMin >= yMax && yMin!= 1e26 && yMin > 0) || (zMin >= zMax && zMin != 1e26 && zMin > 0))
		result = -1;
	else
	{
		if(xMin < yMin && xMin > 0)
		{
			if(xMin < zMin)
				result = xMin;
		}
		else if(yMin < zMin && yMin > 0)
			result = yMin;
		else
			result = zMin;
	}

	for(unsigned i=0; i < 3; i++)
	{
		delete [] rightCalc[i];
		delete [] leftCalc[i];
		delete [] backCalc[i];
		delete [] frontCalc[i];
		delete [] topCalc[i];
		delete [] bottomCalc[i];
	}

	delete [] rightCalc;
	delete [] leftCalc;
	delete [] backCalc;
	delete [] frontCalc;
	delete [] topCalc;
	delete [] bottomCalc;


	return result;
}

//Calculate t values for one side
double** tCalc(const vec4& P0, const vec4& V0, const vec4& TR, const vec4& BL)
{
	double ** tResult = new double*[3];

	for(int i=0; i < 3; i++)
	{
		tResult[i] = new double[2];
		for(unsigned j=0; j < 2; j++)
			tResult[i][j] = 1e26;			
	}

	if(V0.x)
	{
		tResult[0][0] = (BL.x - P0.x)/(V0.x);
		tResult[0][1] = (TR.x - P0.x)/(V0.x);
	}
	else
	{
		tResult[0][1] = (BL.x - P0.x)/(V0.x);
		tResult[0][0] = (TR.x - P0.x)/(V0.x);
	}

	//yNear Calc
	if(V0.y)
	{
		tResult[1][0] = (BL.y - P0.y)/(V0.y);
		tResult[1][1] = (TR.y - P0.y)/(V0.y);
	}
	else
	{
		tResult[1][1] = (BL.y - P0.y)/(V0.y);
		tResult[1][0] = (TR.y - P0.y)/(V0.y);
	}


	//zNear Calc
	if(V0.z)
	{
		tResult[2][0] = (BL.z - P0.z)/(V0.z);
		tResult[2][1] = (TR.z - P0.z)/(V0.z);
	}
	else
	{
		tResult[2][1] = (BL.z - P0.z)/(V0.z);
		tResult[2][0] = (TR.z - P0.z)/(V0.z);
	}


	return tResult;
}
