#ifndef _TRANSFORM_H
#define _TRANSFORM_H

#include "Vector3.h"

class Transform
{
public:
	Vector3 position;
	Vector3 rotation;
	Vector3 scale;

	Transform();
	~Transform();
};

#endif