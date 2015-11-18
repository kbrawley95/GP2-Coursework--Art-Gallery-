#ifndef _VECTOR3_H
#define _VECTOR3_H

#include "Common.h"

struct Vector3
{
	float x;
	float y;
	float z;

	Vector3 operator+(Vector3 a)
	{
		return {x + a.x, y + a.y, z + a.z};
	}

	Vector3 operator=(vec3 a)
	{
		return{ a.x, a.y, a.z };
	}

	vec3 ConvertToVec3()
	{
		return vec3(x,y,z);
	}
};

#endif