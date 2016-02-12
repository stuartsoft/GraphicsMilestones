//Main Driver

#include "VoxelBuffer.h"
#include <string>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include "vec3.h"

using namespace std;

int main(int argc, char** argv) {
	return 0;
}

void parse(string filename){
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