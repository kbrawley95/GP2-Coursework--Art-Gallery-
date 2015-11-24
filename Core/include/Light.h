#ifndef _LIGHT_H
#define _LIGHT_H

#include "Common.h"
#include "Component.h"
#include "Material.h"

class Light :public Component
{
public:
	//Getters
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

	vec4 ambientLightColour = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	vec4 diffuseLightColour = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	vec4 specularLightColour = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	float specularPower = 25.0f;
};

#endif