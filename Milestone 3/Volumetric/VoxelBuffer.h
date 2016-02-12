#pragma once

/**
 * This is the header file for a basic voxel buffer with the required functionality.
 * You may edit this as you wish provided these specific functions match their original form exactly.
 * This will aid in efficiently testing your submission by having a common ground from which to build
 * tests.
 * 
 * Cory D. Boatright
 * Jan. 22, 2015
 * COMP 361
 */

#include "vec3.h"
#include <string>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>

using namespace std;

class VoxelBuffer {

private:
	//you'll want to add things here


	ivec3 VoxelBuffer::posToVoxIndex(const vec3& coords) const;

public:

	vox *voxelMatrix;
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
	float delta;
	float step;

	VoxelBuffer(float delta, float fovy, float step, string bmp, unsigned int w, unsigned int h, const vec3& eyePos, const vec3& vdir, const vec3& uvec, const ivec3& XYZC, const vec3& BRGB, const vec3& MRGB, const vec3& LPOS, const vec3& LCOL);
	~VoxelBuffer(void){};
	float densityRead(const vec3& coords) const;
	float lightRead(const vec3& coords) const;
	void densityWrite(const vec3& coords, float value);
	void lightWrite(const vec3& coords, float value);
	vec3 getVoxelCenter(const vec3& coords) const;
	vec3 getVoxelCenter(const ivec3& coords) const;
	static VoxelBuffer* factory(const std::string& filename);

	static ivec3 readIVEC3(ifstream &f, string l);
	static vec3 readVEC3(ifstream &f, string l);
	static int readINT(ifstream &f, string l);
	static float readFLOAT(ifstream &f, string l);
	static string readSTRING(ifstream &f, string l);

};