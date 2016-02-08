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

void readConfig(string filename, string& bmpfilename, unsigned int &wid, unsigned int &height, vec3 &eyePos, vec3 &vdir, vec3 &uvec, float &fovy);
void runRayTrace(string file);

int main(int argc, char** argv) {

	runRayTrace("test1.txt");
	runRayTrace("test2.txt");
	runRayTrace("test3.txt");
	return 0;
}

void readConfig(string filename, string& bmpfilename, unsigned int &wid, unsigned int &height, vec3 &eyePos, vec3 &vdir, vec3 &uvec, float &fovy){
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


void runRayTrace(string file){
	
	string bmpfilename;
	unsigned int wid, height;
	vec3 eyePos;
	vec3 vdir;
	vec3 uvec;
	float fovy;

	readConfig(file,bmpfilename, wid, height, eyePos,vdir, uvec, fovy);

	BMP output;
	output.SetSize(wid, height);
	output.SetBitDepth(24);
	vec3 N = vdir;
	N = N.normalize();
	vec3 up = uvec;
	up = up.normalize();
	vec3 U;

	vec3 m = eyePos + N;

	//cross product N and up to find U
	U.x = (N.y*up.z-N.z*up.y);
	U.y = (N.z*up.x-N.x*up.z);
	U.z = (N.x*up.y-N.y*up.x);
	U = U.normalize();

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
			R = R.normalize();

			output(x, y)->Red = abs(R.x)*255;
			output(x, y)->Green = abs(R.y)*255;
			output(x, y)->Blue = abs(R.z)*255;
		}
	}

	output.WriteToFile(bmpfilename.c_str());
}