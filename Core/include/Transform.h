#ifndef _TRANSFORM_H
#define _TRANSFORM_H

#include "Vector.h"
#include "Component.h"

class Transform
{
public:
	Vector3 position;
	Vector3 rotation;
	Vector3 scale;

	Transform()
	{
		position = vec3(0, 0, 0);
		rotation = vec3(0, 0, 0);
		scale = vec3(1, 1, 1);
	}
};

#endif