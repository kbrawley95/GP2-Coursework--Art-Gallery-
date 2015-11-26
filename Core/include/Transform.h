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
		position = Vector3(0, 0, 0);
		rotation = Vector3(0, 0, 0);
		scale = Vector3(1, 1, 1);
	}
};

#endif