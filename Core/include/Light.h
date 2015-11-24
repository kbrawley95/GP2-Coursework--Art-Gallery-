#ifndef _LIGHT_H
#define _LIGHT_H

#include "Common.h"
#include "Component.h"
#include "Material.h"

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

	void CalculateLighting(shared_ptr <Material> material);

private:

	vec4 ambientLightColour;
	vec4 diffuseLightColour;
	vec4 specularLightColour;
	float specularPower;
	vec3 direction;
};

#endif