#include "Light.h"


Light::Light()
{

}

Light::~Light()
{

}

void Light::CalculateLighting(shared_ptr<Material> material)
{
	GLint ambientLightColourLocation = glGetUniformLocation(currentShaderProgram, "ambientLightColour");
	GLint ambientMaterialColourLocation = glGetUniformLocation(currentShaderProgram, "ambientMaterialColour");

	GLint diffuseLightColourLocation = glGetUniformLocation(currentShaderProgram, "diffuseLightColour");
	GLint diffuseLightMaterialLocation = glGetUniformLocation(currentShaderProgram, "diffuseMaterialColour");
	GLint lightDirectionLocation = glGetUniformLocation(currentShaderProgram, "lightDirection");

	GLint specularLightColourLocation = glGetUniformLocation(currentShaderProgram, "specularLightColour");
	GLint specularLightMaterialLocation = glGetUniformLocation(currentShaderProgram, "specularMaterialColour");
	GLint specularPowerLocation = glGetUniformLocation(currentShaderProgram, "specularPower");
	
	glUniform4fv(ambientLightColourLocation, 1, value_ptr(GetAmbientLightColour()));
	glUniform4fv(ambientMaterialColourLocation, 1, value_ptr(GetAmbientMaterial()));

	glUniform4fv(diffuseLightColourLocation, 1, value_ptr(GetDiffuseLightColour()));
	glUniform4fv(diffuseLightMaterialLocation, 1, value_ptr(gameObject->GetDiffuseMaterial()));
	glUniform3fv(lightDirectionLocation, 1, value_ptr(camera->GetLightDirection()));

	glUniform4fv(specularLightColourLocation, 1, value_ptr(GetSpecularLightColour()));
	glUniform4fv(specularLightMaterialLocation, 1, value_ptr(gameObject->GetSpecularMaterial()));
	glUniform1f(specularPowerLocation, GetSpecularPower());
}

