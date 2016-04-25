#include "RayTracer.h"

const vec3 BACKGROUND_COLOR = vec3(0,0,0);
#define PI 3.14159

rayTracer::rayTracer(vector<Geometry> geomList, string outputName)
{
	colorBuffer = new vec3[(int)(imageResolution.x * imageResolution.y)];

	//Make a copy of the geometry list 
	geomStack = geomList;
	
	//Set the name for the output bmp file
	outputFileName = outputName;

	//Hard coded variables
	backgroundColor = BACKGROUND_COLOR;
	materialColor = vec3(187,0,0);
	lightColor = vec3(255, 255, 255);
	lightPosition = vec4(5, 0, -5, 0);
	viewDirection = vec4(0, 0, 0, 1);
	cameraPosition = vec4(5, -5, 5, 0);
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

	writeToFile();

	return colorBuffer;
}


vec3 rayTracer::rayTrace(glm::vec3 pixelColor, const vec4& reflectedRay, const double& depth)
{
	//t set to "infinity"
	double t = std::numeric_limits<double>::max();

	string geoType;
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
			geoType = geomStack[i].getType();
		}
	}

	if(t != std::numeric_limits<double>::max())
	{
		//Get the specific point on the object that was intersected with
		vec4 point = RPoint(geomPoint, t, reflectedRay);

		//Get the normal of that point
		vec4 normal = getPointNormal(point, geomPoint);
		
		//Calculate lighting for the pixel (pixel color with lighting applied)
		//Check the shadow feelers to figure out if there is anything between 
		//the object and the light source
		//The lighting is blinn-phong without specular 
		pixelColor = calculateLight(shadowFeeler(point), normal, geomPoint, point);
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
	nVec = vec3(viewDirection) - vec3(cameraPosition);

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
bool rayTracer::shadowFeeler(vec4 point)
{
	//Ray from the point of intersection to the light source
	vec4 reflectedRay = vec4(lightPosition - point);

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
vec3 rayTracer::calculateLight(bool shadow, vec4 normal, Geometry geomPoint, vec4 Rpoint)
{
	float ka = 0.1F, kd = 0.5F;
	vec3 ambient, diffuse;
	vec3 colorCalc = materialColor;
	vec3 defaultObjectColor = vec3(255,0,0);

	//Blinn-phong code
	//If there is a shadow, then don't calculate the diffuse lighting

	vec4 L = normalize(lightPosition - Rpoint);

	vec4 V = normalize(cameraPosition - Rpoint);

	vec4 H = normalize(L + V);

	ambient = defaultObjectColor;

	if(shadow)
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

//Use this to get the specific point of the geometry 
vec4 rayTracer::RPoint(Geometry geom, double t, vec4 ray)
{
	vec4 Rpoint;

	//if(geom.getType() == "cube")
	//	returnT = Test_RayCubeIntersect(cameraPosition, ray, geom.getPoints());
	//else if(geom.getType() == "sphere")
	//	returnT = Test_RaySphereIntersect(cameraPosition, ray, geom.getPoints());
	//else if(geom.getType() == "polygon")
	//	returnT = Test_RayPolyIntersect(cameraPosition, ray, geom.getPoints());

	vec4 objectSpace_E = inverse(geom.getPoints()) * cameraPosition;
	vec4 objectSpace_P = inverse(geom.getPoints()) * ray;

	Rpoint = objectSpace_E + vec4(vec3((float)t), 1) * objectSpace_P;
	
	return Rpoint;
}

vec4 rayTracer::getPointNormal(vec4 point, Geometry geomPoint)
{
	vec4 normal;

	if(geomPoint.getType() == "triangle")
	{
		//bott left point
		vec3 point1 = vec3(-0.5, 0, 0);
		//bott right point
		vec3 point2 = vec3(0.5, 0, 0);
		//top point
		vec3 point3 = vec3(0, 1, 0);

		normal = geomPoint.getPoints() * vec4(cross(point2 - point1, point3 - point1), 1);
	}
	else if(geomPoint.getType() == "sphere")
	{
		normal = point;
		normal.w = 1;
		normal = geomPoint.getPoints() * normal;
	}
	else if(geomPoint.getType() == "cube")
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
			normal = geomPoint.getPoints() * norm4;
		if(abs(point.x + 0.5f) < 0.001)
			normal = geomPoint.getPoints() * norm3;
		if(abs(point.y - 0.5f) < 0.001)
			normal = geomPoint.getPoints() * norm4;
		if(abs(point.y + 0.5f) < 0.001)
			normal = geomPoint.getPoints() * norm6;
		if(abs(point.z - 0.5f) < 0.001)
			normal = geomPoint.getPoints() * norm1;
		if(abs(point.z + 0.5f) < 0.001)
			normal = geomPoint.getPoints() * norm2;
	}

	return normal;
}

void rayTracer::writeToFile()
{
	BMP output1;

	output1.SetBitDepth(24);
	output1.SetSize((int)imageResolution.x, (int)imageResolution.y);

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
