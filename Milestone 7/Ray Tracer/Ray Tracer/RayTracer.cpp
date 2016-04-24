#include "RayTracer.h"

const vec3 BACKGROUND_COLOR = vec3(0,0,0);
#define PI 3.14159

rayTracer::rayTracer()
{
	colorBuffer = new vec3[(int)(imageResolution.x * imageResolution.y)];

	return;
}

rayTracer::~rayTracer()
{
	delete [] colorBuffer;
}

vec3* rayTracer::runTracer()
{
	for(unsigned row = 0; row < imageResolution.x; ++row)
	{
		for(unsigned column = 0; column < imageResolution.y; ++column)
		{
			colorBuffer[column * (int)imageResolution.x + row] = generateRay(row, column);
		}
	}
}


vec3 rayTracer::rayTrace(glm::vec3 pixelColor, const vec4& reflectedRay, const double& depth)
{
	//t set to "infinity"
	double t = std::numeric_limits<double>::max();

	//For each geometry (These will be stored in the scene graph)
	for(unsigned int i=0; i < geomStack.size(); ++i)
	{
		//Run the intersection test and return the lowest t value
		double tOne = intersectTest(reflectedRay, geomStack[i]);

		if(tOne != -1 && tOne < t)
			t = tOne;
	}

	if(t != std::numeric_limits<double>::max())
	{
		//Check shadow feelers
		shadowFeeler();
		//Calculate lighting for the pixel (pixel color with lighting applied)
		//The lighting is blinn-phong without specular 
		pixelColor = calculateLight();
	}

	//This will be changed to be the correct color along the way
	return pixelColor;
}

// Do the correct intersection test based on 
// the geometry type and return the t value
double rayTracer::intersectTest(const vec4& ray, geometry geom)
{
	double returnT = std::numeric_limits<double>::max();

	if(geom.getType() == "cube")
		returnT = Test_RayCubeIntersect(cameraPosition, ray, geom);
	else if(geom.getType() == "sphere")
		returnT = Test_RaySphereIntersect(cameraPosition, ray, geom);
	else if(geom.getType() == "polygon")
		returnT = Test_RayPolyIntersect(cameraPosition, ray, geom);
	else
	{
		//Misspelled the shape type
		cout << "ERROR: Incorrect geometry type\n";
		system("PAUSE");
		exit(0);
	}

	return returnT;
};

//Generate each ray from the eye
vec3 rayTracer::generateRay(int x, int y)
{
	vec4 ray;
	vec3 colorTotal;

	ray.x = mVec.x + ((2.0f * x/(imageResolution.x - 1.0f)) - 1.0f) * hVec.x + (2.0f * y/(imageResolution.y - 1.0f) - 1.0f) * vVec.x;
	ray.y = mVec.y + ((2.0f * x/(imageResolution.x - 1.0f)) - 1.0f) * hVec.y + (2.0f * y/(imageResolution.y - 1.0f) - 1.0f) * vVec.y;
	ray.z = mVec.z + ((2.0f * x/(imageResolution.x - 1.0f)) - 1.0f) * hVec.z + (2.0f * y/(imageResolution.y - 1.0f) - 1.0f) * vVec.z;

	ray.x -= cameraPosition.x;
	ray.y -= cameraPosition.y;
	ray.z -= cameraPosition.z;
	ray.w = 1;

	ray = normalize(ray);

	colorTotal = rayTrace(BACKGROUND_COLOR, ray, 0);

	return colorTotal;
}

void rayTracer::setData()
{
	nVec = viewDirection - vec3(cameraPosition);

	normalize(nVec);

	float ratioX = 1.0f, ratioY = 1.0f;

	if(imageResolution.x > imageResolution.y)
		ratioX = ((float)(imageResolution.x) / (float)(imageResolution.y));
	else 
		ratioY = ((float)(imageResolution.y) / (float)(imageResolution.x));

	//Generate the V ray
	vVec.x = upVector.x * tanf(angle * (PI / 180.0f));
	vVec.y = upVector.y * tanf(angle * (PI / 180.0f));
	vVec.z = upVector.z * tanf(angle * (PI / 180.0f));

	//Generate the M ray
	mVec.x = cameraPosition.x + nVec.x;
	mVec.y = cameraPosition.y + nVec.y;
	mVec.z = cameraPosition.z + nVec.z;
	
	vec3 uVec = -cross(nVec, upVector);
	
	//Make the upVector orthogonal to the nVec and uVec
	upVector = cross(nVec, uVec);

	//Generate the H ray
	hVec.x = (uVec.x * tan(angle * (PI / 180.0f))) * ratioX;
	hVec.y = (uVec.y * tan(angle * (PI / 180.0f))) * ratioX;
	hVec.z = (uVec.z * tan(angle * (PI / 180.0f))) * ratioX;

	return;
}

void rayTracer::shadowFeeler()
{
	//For each geometry (These will be stored in the scene graph)
	for(unsigned int i=0; i < geomStack.size(); ++i)
	{
		//Probably something like this for the shadow feeler (Pulled from ray trace)
		//double tOne = intersectTest(reflectedRay, geomStack[i]);

		//if(tOne != -1 && tOne < t)
		//	t = tOne;
	}

	return;
}

//Blinn-phong lighting without specular
vec3 rayTracer::calculateLight()
{
	vec3 colorCalc;

	return colorCalc;
}