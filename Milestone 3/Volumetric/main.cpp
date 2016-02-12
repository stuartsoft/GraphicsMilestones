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