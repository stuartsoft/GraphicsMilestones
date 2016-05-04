#include "RayTracer.h"

const vec3 BACKGROUND_COLOR = vec3(0, 0, 0);
const vec3 MATERIAL_COLOR = vec3(85,45,125);
const unsigned MAX_DEPTH = 1;
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
	point.w = 1;
	vec4 newPoint = inverse(T) * point;

	if(geom->getType() == "triangle")
	{
		//bott left point
		vec3 point1 = vec3(-0.5f, 0.0f, 0.0f);
		//bott right point
		vec3 point2 = vec3(0.5f, 0.0f, 0.0f);
		//top point
		vec3 point3 = vec3(0.0f, 1.0f, 0.0f);

		normal = inverse(T) * vec4(cross(point2 - point1, point3 - point1), 1.0f);
	}
	else if(geom->getType() == "sphere")
	{
		normal = newPoint;
	}
	else if(geom->getType() == "cube")
	{
		//front face
		vec4 norm1 = vec4(0.0f, 0.0f, 1.0f, 0.0f);
		//back face
		vec4 norm2 = vec4(0.0f, 0.0f, -1.0f, 0.0f);
		//left face
		vec4 norm3 = vec4(-1.0f, 0.0f, 0.0f, 0.0f);
		//right face
		vec4 norm4 = vec4(1.0f, 0.0f, 0.0f, 0.0f);
		//top face
		vec4 norm5 = vec4(0.0f, 1.0f, 0.0f, 0.0f);
		//bottom face
		vec4 norm6 = vec4(0.0f, -1.0f, 0.0f, 0.0f);

		if(abs(newPoint.x - 0.5f) < 0.00001f)
			normal = T * norm4;
		else if(abs(newPoint.x + 0.5f) < 0.00001f)
			normal = T * norm3;
		else if(abs(newPoint.y - 0.5f) < 0.00001f)
			normal = T * norm5;
		else if(abs(newPoint.y + 0.5f) < 0.00001f)
			normal = T * norm6;
		else if(abs(newPoint.z - 0.5f) < 0.00001f)
			normal = T *  norm1;
		else
			normal =  T * norm2;

		//normal.z = abs(normal.z);

		//normal = normalize(normal);

		//std::cout<<normal.x <<", " <<normal.y << ", " <<normal.z<<std::endl;
	}
	else 
	{
		//Misspelled the shape type
		std::cout << "ERROR: Incorrect geometry type\n";
		system("PAUSE");
		exit(0);
	}

	return normalize(normal);
}

vec3 RayTracer::shadowFeeler(vec4 intersectionPoint, mat4 T, vec4 normal, unsigned self){
	bool obstruction = false;
	float ka = 0.3f, kd = 0.7f;
	vec3 ambient, diffuse;
	vec3 colorCalc;
	//Geometry *geom;
	//unsigned num;

	//Check for an object between the object and the light 
	for(unsigned i = 0; i < sceneGeom.size(); i++){
		if(i == self) continue;

		double result = intersectionTests(sceneGeom[i], intersectionPoint, (lightPos - intersectionPoint), objectMovement[i]);
	
		if(result > 0 && result <= 1){
			obstruction = true;
		}
	}

	//Blinn-phong code
	vec4 L = normalize(lightPos - intersectionPoint);

	vec4 V = normalize(vec4(eyePos, 1.0f) - intersectionPoint);

	ambient = objectColor[self];

	if(obstruction)
	{
		diffuse = vec3(0,0,0);
	}
	else
	{
		diffuse = clamp(dot(L, normal), 0.0f, 1.0f) * objectColor[self];
	}

	colorCalc = vec3(ka * ambient + kd * diffuse);

	return colorCalc;
}

vec3 RayTracer::reflection(unsigned depth, vec3 currentColor, const mat4& transMatrix, vec4 R, unsigned reflectedObject, vec4 IPoint)
{
	double t = 1e26;
	Geometry * intersectGeometry = new Geometry;
	unsigned int self;
	for(unsigned num=0; num < sceneGeom.size(); ++num)
	{
		//Make sure it isn't reflecting with itself
		if(num == reflectedObject) continue;

		double tOne = intersectionTests(sceneGeom[num], IPoint, R, objectMovement[num]);

		//Find the closest intersection point
		if(tOne < t && tOne != -1)
		{
			t = tOne;
			intersectGeometry = sceneGeom[num];
			self = num;
		}
	}

	if(t != -1 && t != 1e26)
	{
		vec4 iPoint = intersectionPoint(objectMovement[self], R, t, IPoint);
		iPoint.w = 0;
		vec4 norm = getNormal(iPoint, intersectGeometry, objectMovement[self]);
		R = glm::reflect(iPoint, norm);
		R.w = 0.0f;
		currentColor = currentColor * vec3((1 - intersectGeometry->getReflectivity())) + vec3((intersectGeometry->getReflectivity())) * shadowFeeler(iPoint, objectMovement[self], norm, self);

		//Set the max here
		if(depth >= MAX_DEPTH)
			return currentColor;
		else 
			return reflection(depth + 1, currentColor, transMatrix, R, reflectedObject, iPoint);
	}

	return currentColor;

}

void RayTracer::rayGeneration(const mat4& transMatrix, unsigned depth){
	
	vec3 N = vdir;
	N = normalize(N);

	vec3 up = uvec;
	up = normalize(up);
	vec3 U;

	vec3 m = eyePos + N;

	U = -glm::cross(N,up);
	U = normalize(U);

	up = glm::cross(U,N);

	vec3 V, H;

	float tanFovy = tanf(fovy * (PI / 180.0f));

	float ratioX = 1.0f, ratioY = 1.0f;
	if(imageSize.x > imageSize.y)
		ratioX = ((float)(imageSize.x) / (float)(imageSize.y));
	else 
		ratioY = ((float)(imageSize.y) / (float)(imageSize.x));

	V = up * tanFovy;

	H = U * tanFovy * ratioX;

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
			unsigned self = 666;
			for(unsigned num=0; num < sceneGeom.size(); ++num)
			{
				double tOne = intersectionTests(sceneGeom[num], vec4(eyePos, 1.0f), vec4(R, 0.0f), objectMovement[num]);

				//Find the closest intersection point
				if(tOne < t && tOne != -1)
				{
					t = tOne;
					intersectGeometry = sceneGeom[num];
					self = num;
				}
			}

			//Initialize the color to the background color
			vec3 color = BACKGROUND_COLOR;
			if(t != -1 && t != 1e26)
			{
				vec4 iPoint = intersectionPoint(objectMovement[self], vec4(R, 0.0f), t, vec4(eyePos, 0.0f));
				vec4 norm = getNormal(iPoint, intersectGeometry, objectMovement[self]);
				color = shadowFeeler(iPoint, objectMovement[self], norm, self);

				if(intersectGeometry->getReflectivity() > 0.0)
				{
					vec4 reflectRay = glm::reflect(iPoint, norm);
				
					if(depth < MAX_DEPTH)
						color = reflection(depth, color, objectMovement[self], reflectRay, self, iPoint);
				}
			}

			//Put a cap on the color
			if(color.x >0)
			{
				if(color.x > 255)
					color.x = 255;
				if(color.y > 255)
					color.y = 255;
				if(color.z > 255)
					color.z = 255;
			}

			output(x, y)->Red = (ebmpBYTE)abs(color.x);
			output(x, y)->Green = (ebmpBYTE)abs(color.y);
			output(x, y)->Blue = (ebmpBYTE)abs(color.z);
		}
	}
	output.WriteToFile(outputName.c_str());
}


vec4 RayTracer::intersectionPoint(const mat4& transMatrix, vec4 ray, double t, vec4 startPoint)
{
	vec4 iPoint;

	//vec4 objectSpace_E = transMatrix * startPoint;
	//vec4 objectSpace_P = transMatrix * ray;

	iPoint = startPoint + float(t) * ray;

	return iPoint;
}

