//Main Driver

#include "EasyBMP.h"
#include "VoxelBuffer.h"

using namespace std;

float kappa = 0.8f;

void runRayTrace(VoxelBuffer* vb);

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

int main(int argc, char** argv) {
	VoxelBuffer *subject1 = VoxelBuffer::factory("test1.txt");
	runRayTrace(subject1);
	//return 0;
	VoxelBuffer *subject2 = VoxelBuffer::factory("test2.txt");
	runRayTrace(subject2);
	VoxelBuffer *subject3 = VoxelBuffer::factory("test3.txt");
	runRayTrace(subject3);

	return 0;
}

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
		
		cout<<"row "<<x<<endl;
		for(unsigned int y = 0; y < vb->height; y++) {
			vec3 D;
			float xpercent = (2.0f*x/(vb->wid-1)-1);
			float ypercent = (2.0f*y/(vb->height-1)-1);
			D = m + (H * xpercent) + (V * ypercent);
			vec3 R = D - vb->eyePos;
			R = normalize(R);

			float tau = 1.0f;
			vec3 xi = vb->eyePos;
			xi.z = vb->XYZC.z-1;
			vec3 c;
			c.x = 0;
			c.y = 0;
			c.z = 0;
			while(true){//first layer ray marching

				
				vec3 marchdiff = (R * vb->step);
				xi =  xi + marchdiff;

				ivec3 voxIndex = vb->posToVoxIndex(xi);
				if (voxIndex.x < 0 || voxIndex.y < 0 || voxIndex.z <0)
					break;//we're now outside the voxel buffer
				vec3 voxCenter = vb->getVoxelCenter(voxIndex);
				float deltaTau;
				
				deltaTau = exp(-kappa * vb->step * vb->densityRead(voxCenter));
				
				tau *= deltaTau;

				vec3 N = vb->LPOS - voxCenter;//voxel to light vector
				float distToLight = sqrt(N.x * N.x + N.y*N.y + N.z*N.z);
				N = normalize(N);
				float densitySum = 0;
				for (float marchDist = 0.0f;marchDist <=distToLight;marchDist+=vb->step){//nested ray march from voxel to light
					vec3 coord = voxCenter + (N*marchDist);
					ivec3 voxIndex2 = vb->posToVoxIndex(coord);
					if (voxIndex2.x < 0 || voxIndex2.y <0 || voxIndex2.z < 0 )
						break;
					
					densitySum += vb->densityRead(coord);
					//cout <<coord.x << ", "<<coord.y<<", "<<coord.y<<endl;
				}
				float Q = exp(-kappa*densitySum);
				//if (Q != 1.0f)
					//cout<<Q<<endl;
				vb->lightWrite(voxCenter,Q);
				vec3 change = (((vb->LCOL)*vb->MRGB)*(tau*Q)) * ((1 - deltaTau)/kappa);
				c = c + change ;
			}

			c = c + vb->BRGB * tau;//tie the color in with the background color

			output(x, y)->Red = min(c.x*255.0f, 255.0f);
			output(x, y)->Green = min(c.y*255.0f, 255.0f);
			output(x, y)->Blue = min(c.z*255.0f, 255.0f);
		}
	}

	output.WriteToFile(vb->bmpfilename.c_str());
}