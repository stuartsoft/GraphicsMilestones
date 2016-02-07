/**
 * An example program that creates a 24-bit bitmap file that is 800 x 600 and makes a blue/red checkerboard pattern.
 * Uses EasyBMP
 *
 * Cory Boatright
 * University of Pennsylvania, Fall 2011
 * AND Grove City College 2015
 **/

#include "EasyBMP.h"
#include "vec3.h"
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
float fovy;


void readConfig(string filename){
	ifstream file(filename);
	string line;

	//FILE
	getline(file,line);
	stringstream ss(line);
	string tok = "";
	ss >> tok;//skip tag
	ss >> bmpfilename;

	//RESO
	getline(file, line);
	ss = stringstream(line);
	ss >> tok;
	ss >> tok;
	wid = stoi(tok);
	ss >> tok;
	height = stoi(tok);

	//EYEP
	getline(file, line);
	ss = stringstream(line);
	ss >> tok;
	ss >> tok;
	eyePos.x = stof(tok);
	ss >> tok;
	eyePos.y = stof(tok);
	ss >> tok;
	eyePos.z = stof(tok);

	//VDIR
	getline(file,line);
	ss = stringstream(line);
	ss >> tok;
	ss >> tok;
	vdir.x = stof(tok);
	ss >> tok;
	vdir.y = stof(tok);
	ss >> tok;
	vdir.z = stof(tok);

	//UVEC
	getline(file, line);
	ss = stringstream(line);
	ss >> tok;
	ss >> tok;
	uvec.x = stof(tok);
	ss >> tok;
	uvec.y = stof(tok);
	ss >> tok;
	uvec.z = stof(tok);

	//FOVY
	getline(file,line);
	ss = stringstream(line);
	ss >> tok;
	ss >> tok;
	fovy = stof(tok);
}

vec3 normalize(vec3 in){
	float len = sqrt(in.x * in.x + in.y*in.y + in.z*in.z);
	vec3 result = in;
	result.x = in.x/len;
	result.y = in.y/len;
	result.z = in.z/len;
	return result;
}

int main(int argc, char** argv) {

	readConfig("test1.txt");

	BMP output;
	output.SetSize(wid, height);
	output.SetBitDepth(24);
	vec3 N = vdir;
	N = normalize(N);
	vec3 up = uvec;
	up = normalize(up);
	vec3 U;

	vec3 m = eyePos;
	m.x += N.x;
	m.y += N.y;
	m.z += N.z;

	//cross product N and up to find U
	U.x = (N.y*up.z-N.z*up.y);
	U.y = (N.z*up.x-N.x*up.z);
	U.z = (N.x*up.y-N.y*up.x);
	U = normalize(U);

	vec3 V, H;
	V = up;
	float tanFovy = tan(fovy * (3.1415f / 180.0));
	V.x *= tanFovy;
	V.y *= tanFovy;
	V.z *= tanFovy;

	H = U;
	H.x *= tanFovy;
	H.y *= tanFovy;
	H.z *= tanFovy;


	for(unsigned int x = 0; x < wid; x++) {
		for(unsigned int y = 0; y < height; y++) {
			//m*(2*x/(wid-1)-1)*H + (2*y/(height-1)-1)*v;
			vec3 D;
			float xpercent = (2.0f*x/(wid-1)-1);
			float ypercent = (2.0f*y/(height-1)-1);
			D.x = m.x + (xpercent)*H.x + (ypercent)*V.x;
			D.y = m.y + (xpercent)*H.y + (ypercent)*V.y;
			D.z = m.z + (xpercent)*H.z + (ypercent)*V.z;
			vec3 R = D;
			R.x -= eyePos.x;
			R.y -= eyePos.y;
			R.z -= eyePos.z;
			R = normalize(R);

			output(x, y)->Red = abs(R.x)*255;
			output(x, y)->Green = abs(R.y)*255;
			output(x, y)->Blue = abs(R.z)*255;
		}
	}

	output.WriteToFile("output.bmp");
	return 0;
}