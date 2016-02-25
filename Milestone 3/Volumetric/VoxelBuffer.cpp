/* 
Stuart Bowman 2016

This is the Voxel Buffer class. It contains the actual voxel matrix, environment data, 
an input file parser, and helper functions.
*/

#include "VoxelBuffer.h"
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

//constructor
VoxelBuffer::VoxelBuffer(float delta, float fovy, float step, string bmp, unsigned int w, unsigned int h, const vec3& eyePos, const vec3& vdir, const vec3& uvec, const ivec3& XYZC, const vec3& BRGB, const vec3& MRGB, const vec3& LPOS, const vec3& LCOL){
	//voxelMatrix = new vox[dimensions.x * dimensions.y * dimensions.z];
	int totalVoxels = XYZC.x * XYZC.y * XYZC.z;
	voxelMatrix = (vox*) malloc(sizeof(vox)* totalVoxels);
	this->delta = delta;
	this->fovy = fovy;
	this->bmpfilename = bmp;
	this->wid = w;
	this->height = h;
	this->eyePos = eyePos;
	this->vdir = vdir;
	this->uvec = uvec;
	this->XYZC = XYZC;
	this->BRGB = BRGB;
	this->MRGB = MRGB;
	this->LPOS = LPOS;
	this->LCOL = LCOL;
	this->step = step;
	this->totalVoxels = totalVoxels;
}

VoxelBuffer* VoxelBuffer::factory(const std::string& filename){

	ifstream file(filename);
	string line;
	
	string mbmp;
	unsigned int mwid, mheight;
	vec3 meyePos;
	vec3 mvdir;
	vec3 muvec;
	ivec3 mXYZC;
	vec3 mBRGB;
	vec3 mMRGB;
	vec3 mLPOS;
	vec3 mLCOL;
	float mstep;
	float mdelta;
	float mfovy;

	mdelta = readFLOAT(file, line);
	mstep = readFLOAT(file, line);
	mXYZC = readIVEC3(file, line);
	mBRGB = readVEC3(file, line);
	mMRGB = readVEC3(file, line);

	mbmp = readSTRING(file, line);

	//RESO
	getline(file, line);
	stringstream ss(line);
	string tok = "";
	ss >> tok;
	ss >> tok;
	mwid = stoi(tok);
	ss >> tok;
	mheight = stoi(tok);

	meyePos = readVEC3(file,line);
	mvdir = readVEC3(file, line);
	muvec = readVEC3(file, line);

	mfovy = readFLOAT(file, line);
	mLPOS = readVEC3(file, line);
	mLCOL = readVEC3(file, line);

	VoxelBuffer *resultVoxelBuffer = new VoxelBuffer(mdelta, mfovy, mstep, mbmp, mwid, mheight, meyePos,mvdir, muvec, mXYZC, mBRGB, mMRGB, mLPOS, mLCOL);

	for (int i = 0;i<mXYZC.z;i++){
		for (int j = 0;j<mXYZC.y;j++){
			for (int k = 0;k<mXYZC.x;k++){
				getline(file, line);
				float val = stof(line);
				ivec3 index;
				index.x = k;
				index.y = j;
				index.z = i;
				resultVoxelBuffer->densityWrite(resultVoxelBuffer->getVoxelCenter(index),val);
					
				resultVoxelBuffer->lightWrite(resultVoxelBuffer->getVoxelCenter(index),-1);
				//cout << index.x<<", "<< index.y<<", "<<index.z<<endl;
				//cout <<val << endl;

			}
		}
	}

	return resultVoxelBuffer;
}

float VoxelBuffer::densityRead(const vec3& coords) const{
	ivec3 index = posToVoxIndex(coords);
	return voxelMatrix[index.z*XYZC.y*XYZC.x + index.y*XYZC.x + index.x].density;
}

float VoxelBuffer::lightRead(const vec3& coords) const{
	ivec3 index = posToVoxIndex(coords);
	return voxelMatrix[index.z*XYZC.y*XYZC.x + index.y*XYZC.x + index.x].light;
}

void VoxelBuffer::densityWrite(const vec3& coords, float value){
	ivec3 index = posToVoxIndex(coords);
	voxelMatrix[index.z*XYZC.y*XYZC.x + index.y*XYZC.x + index.x].density = value;
}

void VoxelBuffer::lightWrite(const vec3& coords, float value){
	ivec3 index = posToVoxIndex(coords);
	voxelMatrix[index.z*XYZC.y*XYZC.x + index.y*XYZC.x + index.x].light = value;
}

vec3 VoxelBuffer::getVoxelCenter(const vec3& coords) const{
	ivec3 index = posToVoxIndex(coords);
	vec3 result;
	result.x = index.x * delta + delta/2;
	result.y = index.y * delta + delta/2;
	result.z = index.z * delta + delta/2;

	return result;
}

vec3 VoxelBuffer::getVoxelCenter(const ivec3& coords) const{
	vec3 result;
	result.x = coords.x * delta + delta/2;
	result.y = coords.y * delta + delta/2;
	result.z = coords.z * delta + delta/2;
	return result;
}

ivec3 VoxelBuffer::posToVoxIndex(const vec3& coords) const {
	ivec3 tempivec3;
	tempivec3.x = floor(coords.x/delta);
	tempivec3.y = floor(coords.y/delta);
	tempivec3.z = floor(coords.z/delta);

	int index = (tempivec3.z*XYZC.y*XYZC.x + tempivec3.y*XYZC.x + tempivec3.x);
	if (index > totalVoxels-1){
		tempivec3.x = -1;
		tempivec3.y = -1;
		tempivec3.z = -1;
	}
	else if (coords.x > XYZC.x * delta || coords.y > XYZC.y * delta || coords.z > XYZC.z * delta){
		tempivec3.x = -1;
		tempivec3.y = -1;
		tempivec3.z = -1;
	}


	return tempivec3;
}


ivec3 VoxelBuffer::readIVEC3(ifstream &f, string l){
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

vec3 VoxelBuffer::readVEC3(ifstream &f, string l){
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

int VoxelBuffer::readINT(ifstream &f, string l){
	getline(f, l);
	stringstream ss(l);
	string tok = "";
	ss >> tok;
	ss >> tok;
	return stoi(tok);
}

float VoxelBuffer::readFLOAT(ifstream &f, string l){
	getline(f, l);
	stringstream ss(l);
	string tok = "";
	ss >> tok;
	ss >> tok;
	return stof(tok);
}

string VoxelBuffer::readSTRING(ifstream &f, string l){
	getline(f, l);
	stringstream ss(l);
	string tok = "";
	ss >> tok;
	ss >> tok;
	return tok;
}
