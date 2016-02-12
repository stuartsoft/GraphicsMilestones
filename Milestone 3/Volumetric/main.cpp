//Main Driver

#include "EasyBMP.h"
#include "VoxelBuffer.h"
#include <string>
#include <stdlib.h>
#include <fstream>
#include <sstream>

using namespace std;

string bmpfilename;
unsigned int wid, height;
vec3 eyePos;
vec3 vdir;
vec3 uvec;
ivec3 XYZC;
vec3 BRGB;
vec3 MRGB;
vec3 LPOS;
vec3 LCOL;

float fovy;
float delt;
float step;

void parse(string filename);
ivec3 readIVEC3(ifstream &f, string l);
vec3 readVEC3(ifstream &f, string l);
int readINT(ifstream &f, string l);
float readFLOAT(ifstream &f, string l);
string readSTRING(ifstream &f, string l);
void runRayTrace(string file);

int main(int argc, char** argv) {
	parse("test1.txt");


	return 0;
}

void parse(string filename){

	/*
	DELT 1
	STEP 0.5
	XYZC 100 100 100
	BRGB 0.27 0.51 0.71
	MRGB 0.96 0.96 0.96
	FILE BabysFirstCloudImage.bmp
	RESO 640 480
	EYEP 50 50 200
	VDIR 0 0 -1
	UVEC 0 1 0
	FOVY 45
	LPOS 200 0 0
	LCOL 1 1 1
	*/

	ifstream file(filename);
	string line;

	delt = readFLOAT(file, line);
	step = readFLOAT(file, line);
	XYZC = readIVEC3(file, line);
	BRGB = readVEC3(file, line);
	MRGB = readVEC3(file, line);


	bmpfilename = readSTRING(file, line);

	//RESO
	getline(file, line);
	stringstream ss(line);
	string tok = "";
	ss >> tok;
	ss >> tok;
	wid = stoi(tok);
	ss >> tok;
	height = stoi(tok);

	eyePos = readVEC3(file,line);
	vdir = readVEC3(file, line);
	uvec = readVEC3(file, line);

	fovy = readFLOAT(file, line);
	LPOS = readVEC3(file, line);
	LCOL = readVEC3(file, line);

}


ivec3 readIVEC3(ifstream &f, string l){
	getline(f, l);
	int x,y,z;
	stringstream ss(l);
	string tok = "";
	ss >> tok;
	ss >> tok;
	x = stoi(tok);
	ss >> tok;
	y = stoi(tok);
	ss >> tok;
	z = stoi(tok);
	ivec3 temp;
	temp.x = x;
	temp.y = y;
	temp.z = z;
	return temp;
}

vec3 readVEC3(ifstream &f, string l){
	getline(f, l);
	float x,y,z;
	stringstream ss(l);
	string tok = "";
	ss >> tok;
	ss >> tok;
	x = stof(tok);
	ss >> tok;
	y = stof(tok);
	ss >> tok;
	z = stof(tok);
	vec3 temp;
	temp.x = x;
	temp.y = y;
	temp.z = z;
	return temp;
}

int readINT(ifstream &f, string l){
	getline(f, l);
	stringstream ss(l);
	string tok = "";
	ss >> tok;
	ss >> tok;
	return stoi(tok);
}

float readFLOAT(ifstream &f, string l){
	getline(f, l);
	stringstream ss(l);
	string tok = "";
	ss >> tok;
	ss >> tok;
	return stof(tok);
}

string readSTRING(ifstream &f, string l){
	getline(f, l);
	stringstream ss(l);
	string tok = "";
	ss >> tok;
	ss >> tok;
	return tok;
}

void runRayTrace(string file){
	
	string bmpfilename;
	unsigned int wid, height;
	vec3 eyePos;
	vec3 vdir;
	vec3 uvec;
	float fovy;

	BMP output;
	output.SetSize(wid, height);
	output.SetBitDepth(24);
	vec3 N = vdir;
	N = normalize(N);
	vec3 up = uvec;
	up = normalize(up);
	vec3 U;

	vec3 m = eyePos + N;

	//cross product N and up to find U
	U.x = (N.y*up.z-N.z*up.y);
	U.y = (N.z*up.x-N.x*up.z);
	U.z = (N.x*up.y-N.y*up.x);
	U = normalize(U);

	vec3 V, H;
	float tanFovy = tan(fovy * (3.1415f / 180.0));
	V = up * tanFovy;

	H = U * tanFovy;

	for(unsigned int x = 0; x < wid; x++) {
		for(unsigned int y = 0; y < height; y++) {
			vec3 D;
			float xpercent = (2.0f*x/(wid-1)-1);
			float ypercent = (2.0f*y/(height-1)-1);
			D = m + (H * xpercent) + (V * ypercent);
			vec3 R = D - eyePos;
			R = normalize(R);

			output(x, y)->Red = abs(R.x)*255;
			output(x, y)->Green = abs(R.y)*255;
			output(x, y)->Blue = abs(R.z)*255;
		}
	}

	output.WriteToFile(bmpfilename.c_str());
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

vec3 normalize(vec3 temp){
	float len = sqrt(temp.x * temp.x + temp.y*temp.y + temp.z*temp.z);
	vec3 r;
	r.x = temp.x/len;
	r.y = temp.y/len;
	r.z = temp.z/len;
	return r;
}