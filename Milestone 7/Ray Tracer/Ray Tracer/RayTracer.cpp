#include "RayTracer.h"

const vec3 BACKGROUND_COLOR = vec3(0,0,0);
#define PI 3.14159

rayTracer::rayTracer(vector<Geometry> geomList)
{
	colorBuffer = new vec3[(int)(imageResolution.x * imageResolution.y)];

	geomStack = geomList;

	//Hard coded variables
	backgroundColor = BACKGROUND_COLOR;
	materialColor = vec3(187,0,0);
	lightColor = vec3(255, 255, 255);
	lightPosition = vec3(5, 0, -5);
	viewDirection = vec3(0, 0, 0);
	cameraPosition = vec4(5, -5, 5, 1);
	imageResolution = vec2(100, 100);

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

	return colorBuffer;
}


vec3 rayTracer::rayTrace(glm::vec3 pixelColor, const vec4& reflectedRay, const double& depth)
{
	//t set to "infinity"
	double t = std::numeric_limits<double>::max();

	Geometry geomPoint;

	//For each geometry (These will be stored in the scene graph)
	for(unsigned int i=0; i < geomStack.size(); ++i)
	{
		//Run the intersection test and return the lowest t value
		double tOne = intersectTest(reflectedRay, geomStack[i]);

		if(tOne != -1 && tOne < t)
		{
			t = tOne;
			geomPoint = geomStack[i];
		}
	}

	if(t != std::numeric_limits<double>::max())
	{
		//Get the specific point on the object that was intersected with
		vec3 point = RPoint(geomPoint, t);

		//Get the normal of that point
		vec3 normal = getPointNormal(point, geomPoint);
		
		//Calculate lighting for the pixel (pixel color with lighting applied)
		//Check the shadow feelers to figure out if there is anything between 
		//the object and the light source
		//The lighting is blinn-phong without specular 
		pixelColor = calculateLight(shadowFeeler(point), normal);
	}

	//This will be changed to be the correct color along the way
	return pixelColor;
}

// Do the correct intersection test based on 
// the geometry type and return the t value
double rayTracer::intersectTest(const vec4& ray, Geometry geom)
{
	double returnT = std::numeric_limits<double>::max();

	if(geom.getType() == "cube")
		returnT = Test_RayCubeIntersect(cameraPosition, ray, geom.getPoints());
	else if(geom.getType() == "sphere")
		returnT = Test_RaySphereIntersect(cameraPosition, ray, geom.getPoints());
	else if(geom.getType() == "polygon");
		//returnT = Test_RayPolyIntersect(cameraPosition, ray, geom.getPoints());
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
	vVec.x = upVector.x * tanf(angle * ((float)PI / 180.0f));
	vVec.y = upVector.y * tanf(angle * ((float)PI / 180.0f));
	vVec.z = upVector.z * tanf(angle * ((float)PI / 180.0f));

	//Generate the M ray
	mVec.x = cameraPosition.x + nVec.x;
	mVec.y = cameraPosition.y + nVec.y;
	mVec.z = cameraPosition.z + nVec.z;
	
	vec3 uVec = -cross(nVec, upVector);
	
	//Make the upVector orthogonal to the nVec and uVec
	upVector = cross(nVec, uVec);

	//Generate the H ray
	hVec.x = (uVec.x * tan(angle * ((float)PI / 180.0f))) * ratioX;
	hVec.y = (uVec.y * tan(angle * ((float)PI / 180.0f))) * ratioX;
	hVec.z = (uVec.z * tan(angle * ((float)PI / 180.0f))) * ratioX;

	return;
}

//Stilll probably 
bool rayTracer::shadowFeeler(vec3 point)
{
	//Ray from the point of intersection to the light source
	vec4 reflectedRay = vec4((lightPosition - point), 1.0f);

	//For each geometry (These will be stored in the scene graph)
	for(unsigned int i=0; i < geomStack.size(); ++i)
	{
		//Probably something like this for the shadow feeler (Pulled from ray trace)
		double tOne = intersectTest(reflectedRay, geomStack[i]);

		//If it hits, return true for shadow feeler 
		if(tOne != -1 || tOne != 0)
			return true;
	}

	//If it didn't hit anything, then a false return is an indicator of that 
	return false;
}

//Blinn-phong lighting without specular
vec3 rayTracer::calculateLight(bool shadow, vec3 normal)
{
	vec3 colorCalc = materialColor;

	//Blinn-phong code
	//If there is a shadow, then don't calculate the diffuse lighting

	return colorCalc;
}

//Use this to get the specific point of the geometry 
vec3 rayTracer::RPoint(Geometry geom, double t)
{
	vec3 point;

	//if(geom.getType() == "cube")
	//	returnT = Test_RayCubeIntersect(cameraPosition, ray, geom.getPoints());
	//else if(geom.getType() == "sphere")
	//	returnT = Test_RaySphereIntersect(cameraPosition, ray, geom.getPoints());
	//else if(geom.getType() == "polygon")
	//	returnT = Test_RayPolyIntersect(cameraPosition, ray, geom.getPoints());
	
	return point;
}

vec3 rayTracer::getPointNormal(vec3 point, Geometry geomPoint)
{
	vec3 normal;

	return normal;
}

void rayTracer::writeToFile()
{
	BMP output1;

	output1.SetBitDepth(24);
	output1.SetSize(imageResolution.x, imageResolution.y);

	vec3 currentPixel;

	//Generate first image
	for(int x=0; x < imageResolution.x; x++)
	{
		for(int y=0; y < imageResolution.y; y++)
		{
			currentPixel = generateRay(x, y);
			output1(x,y)->Red = (ebmpBYTE)currentPixel.x * 255;
			output1(x,y)->Green = (ebmpBYTE)currentPixel.y * 255;
			output1(x,y)->Blue = (ebmpBYTE)currentPixel.z * 255;
		}
	}

	//Put the data into a bmp image 
	output1.WriteToFile(outputFileName.c_str());

	return;
}
