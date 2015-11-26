#ifndef _VECTOR_H
#define _VECTOR_H

#include "Common.h"

struct Vector2
{
	float x;
	float y;

	Vector2 operator+(Vector2 a)
	{
		return{ x + a.x, y + a.y };
	}

	Vector2 operator=(vec2 a)
	{
		return{ a.x, a.y };
	}

	vec2 ConvertToVec2()
	{
		return vec2(x, y);
	}
};

struct Vector3
{
	float x;
	float y;
	float z;

	Vector3()
	{
		x = 0;
		y = 0;
		z = 0;
	}

	Vector3(float a, float b, float c)
	{
		x = a;
		y = b;
		z = c;
	}

	Vector3 operator+(Vector3 a)
	{
		return{ x + a.x, y + a.y, z + a.z };
	}

	Vector3 operator=(vec3 a)
	{
		return{ a.x, a.y, a.z };
	}

	vec3 ConvertToVec3()
	{
		return vec3(x, y, z);
	}
};

#endif