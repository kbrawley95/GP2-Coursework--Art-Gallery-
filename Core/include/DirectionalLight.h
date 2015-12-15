#ifndef _DIRECTIONALLIGHT_H
#define _DIRECTIONALLIGHT_H

#include "Common.h"
#include "Vector.h"

class DirectionalLight
{
public:
	glm::mat4x4 projection;
	Vector3 direction;
	Vector4 ambientLightColor;
	Vector4 diffuseLightColor;
	Vector4 specularLightColor;
	float specularPower;

	DirectionalLight()
	{
		projection = glm::ortho(-40, 40, -40, 40, -40, 40);
		direction = Vector3(0.0f, -0.5f, 0.5f);
		ambientLightColor = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
		diffuseLightColor = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
		specularLightColor = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
		specularPower = 25.0f;
	}
};

#endif