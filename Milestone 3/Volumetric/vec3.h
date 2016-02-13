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
	vec3 operator +=(const vec3 &v1){
		vec3 r;
		r.x = x + v1.x;
		r.y = y + v1.y;
		r.z = z + v1.z;
		return r;
	}

	vec3 operator -=(const vec3 &v1){
		vec3 r;
		r.x = x - v1.x;
		r.y = y - v1.y;
		r.z = z - v1.z;
		return r;
	}

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