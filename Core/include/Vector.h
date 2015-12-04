#ifndef _VECTOR_H
#define _VECTOR_H

#include "Common.h"

struct Vector2
{
	float x;
	float y;

	Vector2()
	{
		x = 0;
		y = 0;
	}

	Vector2(float a, float b)
	{
		x = a;
		y = b;
	}

	Vector2 operator+(Vector2 a)
	{
		return{ x + a.x, y + a.y };
	}

	Vector2 operator=(glm::vec2 a)
	{
		return{ a.x, a.y };
	}

	glm::vec2 ConvertToVec2()
	{
		return glm::vec2(x, y);
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

	Vector3(glm::vec3 v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
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

	Vector3 operator+=(Vector3 a)
	{
		return{ x + a.x, y + a.y, z + a.z };
	}

	Vector3 operator*(float a)
	{
		return{ x * a, y * a, z * a };
	}

	Vector3 operator=(glm::vec3 a)
	{
		return{ a.x, a.y, a.z };
	}

	glm::vec3 ConvertToVec3()
	{
		return glm::vec3(x, y, z);
	}
};

struct Vector4
{
	float x;
	float y;
	float z;
	float w;

	Vector4()
	{
		x = 0;
		y = 0;
		z = 0;
	}

	Vector4(float a, float b, float c, float d)
	{
		x = a;
		y = b;
		z = c;
		w = d;
	}

	Vector4 operator+(Vector4 a)
	{
		return{ x + a.x, y + a.y, z + a.z, w + a.w };
	}

	Vector4 operator=(glm::vec4 a)
	{
		return{ a.x, a.y, a.z, a.w };
	}

	glm::vec4 ConvertToVec4()
	{
		return glm::vec4(x, y, z, w);
	}
};

#endif