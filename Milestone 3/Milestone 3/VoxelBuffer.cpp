#include "VoxelBuffer.h"
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

//constructor
VoxelBuffer::VoxelBuffer(float delta, const ivec3& dimensions){
	//voxelMatrix = new vox[dimensions.x * dimensions.y * dimensions.z];
	int totalVoxels = dimensions.x * dimensions.y * dimensions.z;
	voxelMatrix = (vox*) malloc(sizeof(vox)* totalVoxels);
	this->delta = delta;
	this->dimensions = dimensions;
}

VoxelBuffer* VoxelBuffer::factory(const std::string& filename){

	ifstream file(filename);
	string line;
	getline(file,line);
	stringstream ss(line);
	string tok = "";
	ss >> tok;

	float delt;
	ss >> tok;
	delt = stof(tok);

	getline(file, line);
	int x,y,z;
	ss = stringstream(line);
	ss >> tok;
	ss >> tok;
	x = stoi(tok);
	ss >> tok;
	y = stoi(tok);
	ss >> tok;
	z = stoi(tok);

	int totalVoxels = x*y*z;
	//cout <<"total voxels"<<totalVoxels<<endl;

	ivec3 dimensions = ivec3();
	dimensions.x = x;
	dimensions.y = y;
	dimensions.z = z;
	VoxelBuffer *resultVoxelBuffer = new VoxelBuffer(delt, dimensions);

	for (int i = 0;i<z;i++){
		for (int j = 0;j<y;j++){
			for (int k = 0;k<x;k++){
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
	return voxelMatrix[index.z*dimensions.y*dimensions.x + index.y*dimensions.x + index.x].density;
}

float VoxelBuffer::lightRead(const vec3& coords) const{
	ivec3 index = posToVoxIndex(coords);
	return voxelMatrix[index.z*dimensions.y*dimensions.x + index.y*dimensions.x + index.x].light;
}

void VoxelBuffer::densityWrite(const vec3& coords, float value){
	ivec3 index = posToVoxIndex(coords);
	voxelMatrix[index.z*dimensions.y*dimensions.x + index.y*dimensions.x + index.x].density = value;
}

void VoxelBuffer::lightWrite(const vec3& coords, float value){
	ivec3 index = posToVoxIndex(coords);
	voxelMatrix[index.z*dimensions.y*dimensions.x + index.y*dimensions.x + index.x].light = value;
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

	return tempivec3;
}
