/* 
Stuart Bowman 2016

This is the driver class. It contains the runRayTrace function for actually ray marching and rendering,
and it contains operator overloading definitions to allow for simplified vector math
*/

#include "EasyBMP.h"
#include "VoxelBuffer.h"

using namespace std;

const float kappa = 0.8f;

void runRayTrace(VoxelBuffer* vb);

//overloaded operators for vectors
vec3 operator +(const vec3 &v1, const vec3 &v2);
vec3 operator -(const vec3 &v1, const vec3 &v2);
vec3 operator *(const vec3 &v1, const vec3 &v2);
vec3 operator *(const vec3 &v1, const float &a);
vec3 operator /(const vec3 &v1, const float &a);

//normalize function
vec3 normalize(const vec3& temp);

//driver
int main(int argc, char** argv) {
	cout<<"Get comfortable. This is going to take a while."<<endl;
	cout<<"Parsing test1"<<endl;
	VoxelBuffer *subject1 = VoxelBuffer::factory("test1.txt");
	cout<<"Rendering test1"<<endl;
	runRayTrace(subject1);

	cout<<"Parsing test2"<<endl;
	VoxelBuffer *subject2 = VoxelBuffer::factory("test2.txt");
	cout<<"Rendering test2"<<endl;

	runRayTrace(subject2);
	cout<<"Parsing test3"<<endl;

	VoxelBuffer *subject3 = VoxelBuffer::factory("test3.txt");
	cout<<"Rendering test3"<<endl;
	runRayTrace(subject3);

	return 0;
}

/*Runs ray marching using ray trace from Milestone 2, and at each step of the ray march, run a nested ray march
from that given point to the light source. This also outputs the rendered data to a bmp*/
void runRayTrace(VoxelBuffer* vb){
	BMP output;
	output.SetSize(vb->wid, vb->height);
	output.SetBitDepth(24);
	vec3 N = vb->vdir;
	N = normalize(N);
	vec3 up = vb->uvec;
	up = normalize(up);
	vec3 U;

	vec3 m = vb->eyePos + N;

	//cross product N and up to find U
	U.x = (N.y*up.z-N.z*up.y);
	U.y = (N.z*up.x-N.x*up.z);
	U.z = (N.x*up.y-N.y*up.x);
	U = normalize(U);

	vec3 V, H;
	float tanFovy = tan(vb->fovy * (3.1415f / 180.0));
	//V = up * phiRes
	//H = u * aspect * phiRes
	V = up * tanFovy;
	H = U *(vb->wid/(float)vb->height)* tanFovy;

	for(unsigned int x = 0; x < vb->wid; x++) {
		
		//cout<<"row "<<x<<endl;
		for(unsigned int y = 0; y < vb->height; y++) {
			vec3 D;
			float xpercent = (2.0f*x/(vb->wid-1)-1);
			float ypercent = (2.0f*y/(vb->height-1)-1);
			D = m + (H * xpercent) + (V * ypercent);
			vec3 R = D - vb->eyePos;
			R = normalize(R);

			vec3 marchdiff = (R * vb->step);

			float tau = 1.0f;
			vec3 xi = vb->eyePos;
			while (xi.z > vb->XYZC.z ){
				xi = xi + marchdiff;//quickly march from the eye until we have reached the start of the voxel buffer
			}
			//xi.z = vb->XYZC.z-1; 
			vec3 c;
			c.x = 0;
			c.y = 0;
			c.z = 0;
			while(true){//first layer ray marching. Marching into the voxel buffer from the camera

				xi =  xi + marchdiff;
				if (xi.x > vb->XYZC.x || xi.x < 0 || xi.y > vb->XYZC.y || xi.y < 0 || xi.z > vb->XYZC.z || xi.z < 0)
					break;//we are outside of the voxel buffer. Stop this march!

				ivec3 voxIndex = vb->posToVoxIndex(xi);
				if (voxIndex.x < 0 || voxIndex.y < 0 || voxIndex.z <0){
					break;//we are outside of the voxel buffer. Stop this march!
				}
					
				vec3 voxCenter = vb->getVoxelCenter(voxIndex);
				float deltaTau;
				
				deltaTau = exp(-kappa * vb->step * vb->densityRead(voxCenter));
				
				tau *= deltaTau;

				vec3 N = vb->LPOS - voxCenter;//vector from the voxel to the light
				float distToLight = sqrt(N.x * N.x + N.y*N.y + N.z*N.z);
				N = normalize(N);
				float densitySum = 0;
				for (float marchDist = 0.0f;marchDist <=distToLight;marchDist+=vb->step){
					//nested ray march from voxel to light
					//this is the lighting ray march, calculating the lighting for the voxel

					vec3 coord = voxCenter + (N*marchDist);
					ivec3 voxIndex2 = vb->posToVoxIndex(coord);
					if (voxIndex2.x < 0 || voxIndex2.y <0 || voxIndex2.z < 0 )
						break;//we are outside of the voxel buffer. Stop this march!
					
					densitySum += vb->densityRead(coord) * vb->step;
				}
				float Q = exp(-kappa*densitySum);//Q is the light value calculated from the light ray march above
				vb->lightWrite(voxCenter,Q);
				vec3 change = (((vb->LCOL)*vb->MRGB)*(tau*Q)) * ((1 - deltaTau)/kappa);//the overall change in color for this march
				c = c + change ;//update the color
			}

			c = c + vb->BRGB * tau;//tie the color in with the background color

			//assign color values from calculated color. Multiply by 255 and cap at 255
			output(x, y)->Red = min(c.x*255.0f, 255.0f);
			output(x, y)->Green = min(c.y*255.0f, 255.0f);
			output(x, y)->Blue = min(c.z*255.0f, 255.0f);
		}
	}

	output.WriteToFile(vb->bmpfilename.c_str());
}


vec3 operator +(const vec3 &v1, const vec3 &v2){
	vec3 r;
	r.x = v1.x + v2.x;
	r.y = v1.y + v2.y;
	r.z = v1.z + v2.z;
	return r;
}

vec3 operator -(const vec3 &v1, const vec3 &v2){
	vec3 r;
	r.x = v1.x - v2.x;
	r.y = v1.y - v2.y;
	r.z = v1.z - v2.z;
	return r;
}

vec3 operator *(const vec3 &v1, const vec3 &v2){
	vec3 r;
	r.x = v1.x * v2.x;
	r.y = v1.y * v2.y;
	r.z = v1.z * v2.z;
	return r;
}

vec3 operator *(const vec3 &v1, const float &a){
	vec3 r;
	r.x = v1.x * a;
	r.y = v1.y * a;
	r.z = v1.z * a;
	return r;
}

vec3 operator /(const vec3 &v1, const float &a){
	vec3 r;
	r.x = v1.x / a;
	r.y = v1.y / a;
	r.z = v1.z / a;
	return r;
}

vec3 normalize(const vec3& temp){
	float len = sqrt(temp.x * temp.x + temp.y*temp.y + temp.z*temp.z);
	vec3 r;
	r.x = temp.x/len;
	r.y = temp.y/len;
	r.z = temp.z/len;
	return r;
}