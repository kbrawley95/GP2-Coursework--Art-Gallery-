#include "Light.h"


Light::Light()
{
	ambientLightColour = vec4(0.0f, 0.0f, 1.0f, 1.0f);
	diffuseLightColour = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	specularLightColour = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	specularPower = 25.0f;
}

Light::~Light()
{

}
