#pragma once

/* 
Stuart Bowman 2016

This is the vec3 and ivec3 struct definitions. Their arithmetic operators are overloaded in the driver
*/

/**
 * These were made just to keep the parameter lists of the VoxelBuffer functions from being really long.
 * 
 * CDB
 */
 
struct vec3 {
	float x;
	float y;
	float z;

	vec3(){
	}

	vec3(float X, float Y , float Z){
		x = X;
		y = Y;
		z = Z;
	}
};

struct ivec3 {
	int x;
	int y;
	int z;

	ivec3(){}

	ivec3(int X, int Y, int Z){
		x = X;
		y = Y;
		z = Z;
	}
};

struct vox{
	float density;
	float light;
};