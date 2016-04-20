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

void generateAndRender(string filename);

//driver
int main(int argc, char** argv) {
	cout<<"Get comfortable. This is going to take a while."<<endl;
	generateAndRender("test1.txt");
	generateAndRender("test2.txt");
	generateAndRender("test3.txt");

	return 0;
}

void generateAndRender(string filename){
	cout<<endl<<"Parsing "<<filename<<endl;
	VoxelBuffer *subject1 = VoxelBuffer::factory(filename);
	cout<<"Generating voxel buffer"<<endl;
	for (int i = 0;i<subject1->numItems;i++){
		subject1->generateVoxelBuffer(i);
	}
	cout<<"Rendering "<<filename<<endl;
	runRayTrace(subject1);
	delete subject1;
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

	vec3 farX = vb->getVoxelCenter(vec3(vb->XYZC.x-1,0,0));
	vec3 farY = vb->getVoxelCenter(vec3(0, vb->XYZC.y-1,0));
	vec3 farZ = vb->getVoxelCenter(vec3(0,0,vb->XYZC.z-1));

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
			while (xi.z > farZ.z ){
				xi = xi + marchdiff;//quickly march from the eye until we have reached the start of the voxel buffer
			}
			//xi.z = vb->XYZC.z-1; 
			vec3 c;
			c.x = 0;
			c.y = 0;
			c.z = 0;
			while(true){//first layer ray marching. Marching into the voxel buffer from the camera

				xi =  xi + marchdiff;
				
				ivec3 voxIndex = vb->posToVoxIndex(xi);
				if (voxIndex.x < 0 || voxIndex.y < 0 || voxIndex.z < 0)
					break;

				vec3 voxCenter = vb->getVoxelCenter(voxIndex);
				float deltaTau;
				
				if (voxCenter.x > vb->XYZC.x || voxCenter.y > vb->XYZC.y || voxCenter.z > vb-> XYZC.z)
					break;

				deltaTau = exp(-kappa * vb->step * vb->densityRead(voxCenter));
				
				tau *= deltaTau;

				vec3 N = vb->LPOS - voxCenter;//vector from the voxel to the light
				float distToLight = sqrt(N.x * N.x + N.y*N.y + N.z*N.z);
				N = normalize(N);
				float densitySum = 0;
				float Q;
				if(vb->lightRead(voxCenter) == -1){
					for (float marchDist = 0.0f;marchDist <=distToLight;marchDist+=vb->step){
						//nested ray march from voxel to light
						//this is the lighting ray march, calculating the lighting for the voxel
						vec3 coord = voxCenter + (N*marchDist);
						ivec3 voxIndex2 = vb->posToVoxIndex(coord);
						if (voxIndex2.x < 0 || voxIndex2.y <0 || voxIndex2.z < 0 )
							break;//we are outside of the voxel buffer. Stop this march!
					
						densitySum += vb->densityRead(coord) * vb->step;
					}
					Q = exp(-kappa*densitySum);//Q is the light value calculated from the light ray march above
					vb->lightWrite(voxCenter,Q);
				}
				Q = vb->lightRead(voxCenter);

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