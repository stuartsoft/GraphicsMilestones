#pragma once

/**
 * These were made just to keep the parameter lists of the VoxelBuffer functions from being really long.
 * 
 * CDB
 */
 
struct vec3 {
	float x;
	float y;
	float z;
};

struct ivec3 {
	int x;
	int y;
	int z;
};

struct vox{
	float density;
	float light;
};
