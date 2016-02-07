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
int wid, height;
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

int main(int argc, char** argv) {
	unsigned int width = 800;
	unsigned int height = 600;

	readConfig("test1.txt");

	BMP output;
	output.SetSize(width, height);
	output.SetBitDepth(24);
	
	for(unsigned int x = 0; x < width; x++) {
		for(unsigned int y = 0; y < height; y++) {
			
		}
	}

	output.WriteToFile("output.bmp");
	return 0;
}