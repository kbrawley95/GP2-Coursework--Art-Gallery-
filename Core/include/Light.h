#ifndef _LIGHT_H
#define _LIGHT_H

#include "Common.h"
#include "Component.h"

class Light :public Component
{
public:

	Light();
	~Light();

	//Getters
	vec3& GetLightDirection()
	{
		return direction;
	};

	vec4& GetAmbientLightColour()
	{
		return ambientLightColour;
	};

	vec4& GetDiffuseLightColour()
	{
		return diffuseLightColour;
	};

	vec4& GetSpecularLightColour()
	{
		return specularLightColour;
	};

	float GetSpecularPower()
	{
		return specularPower;
	}

private:
	vec4 ambientLightColour;
	vec4 diffuseLightColour;
	vec4 specularLightColour;
	float specularPower;
	vec3 direction;
};

#endif