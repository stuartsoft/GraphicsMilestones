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

class VoxelBuffer {

private:
	//you'll want to add things here
	vox *voxelMatrix;
	float delta;
	ivec3 dimensions;

	ivec3 VoxelBuffer::posToVoxIndex(const vec3& coords) const;

public:
	VoxelBuffer(float delta, const ivec3& dimensions);
	~VoxelBuffer(void){};
	float densityRead(const vec3& coords) const;
	float lightRead(const vec3& coords) const;
	void densityWrite(const vec3& coords, float value);
	void lightWrite(const vec3& coords, float value);
	vec3 getVoxelCenter(const vec3& coords) const;
	vec3 getVoxelCenter(const ivec3& coords) const;
	static VoxelBuffer* factory(const std::string& filename);
};