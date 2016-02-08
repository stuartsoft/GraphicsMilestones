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

	vec3 normalize(){
		float len = sqrt(x * x + y*y + z*z);
		vec3 r;
		r.x = x/len;
		r.y = y/len;
		r.z = z/len;
		return r;
	}
};

vec3 operator +(const vec3 &v1, const vec3 &v2){
	vec3 r;
	r.x = v1.x + v2.x;
	r.y = v1.y + v2.y;
	r.z = v1.z + v2.z;
	return r;
}

vec3 operator -(const vec3 &v1, const vec3 &v2){
	vec3 r;
	r.x = v1.x - v2.x;
	r.y = v1.y - v2.y;
	r.z = v1.z - v2.z;
	return r;
}

vec3 operator *(const vec3 &v1, const vec3 &v2){
	vec3 r;
	r.x = v1.x * v2.x;
	r.y = v1.y * v2.y;
	r.z = v1.z * v2.z;
	return r;
}

vec3 operator *(const vec3 &v1, const float &a){
	vec3 r;
	r.x = v1.x * a;
	r.y = v1.y * a;
	r.z = v1.z * a;
	return r;
}

vec3 operator /(const vec3 &v1, const float &a){
	vec3 r;
	r.x = v1.x / a;
	r.y = v1.y / a;
	r.z = v1.z / a;
	return r;
}



struct ivec3 {
	int x;
	int y;
	int z;
};

struct vox{
	float density;
	float light;
};