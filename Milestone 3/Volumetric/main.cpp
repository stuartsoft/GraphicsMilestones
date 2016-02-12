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

vec3 normalize(vec3 temp){
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

	return 0;
}

void runRayTrace(VoxelBuffer* vb){
	BMP output;
	output.SetSize(vb->wid, vb->height);
	output.SetBitDepth(24);
	vec3 N = vb->vdir;
	N = normalize(N);
	vec3 up = vb->uvec;
	up = normalize(N);
	vec3 U;

	vec3 m = vb->eyePos + N;

	//cross product N and up to find U
	U.x = (N.y*up.z-N.z*up.y);
	U.y = (N.z*up.x-N.x*up.z);
	U.z = (N.x*up.y-N.y*up.x);
	U = normalize(U);

	vec3 V, H;
	float tanFovy = tan(vb->fovy * (3.1415f / 180.0));
	V = up * tanFovy;
	//V = up * phiRes
	//H = u * aspect * phiRes
	H = U * tanFovy;

	for(unsigned int x = 0; x < vb->wid; x++) {
		for(unsigned int y = 0; y < vb->height; y++) {
			vec3 D;
			float xpercent = (2.0f*x/(vb->wid-1)-1);
			float ypercent = (2.0f*y/(vb->height-1)-1);
			D = m + (H * xpercent) + (V * ypercent);
			vec3 R = D - vb->eyePos;
			R = normalize(R);


			output(x, y)->Red = abs(R.x)*255;
			output(x, y)->Green = abs(R.y)*255;
			output(x, y)->Blue = abs(R.z)*255;
		}
	}

	output.WriteToFile(vb->bmpfilename.c_str());
}