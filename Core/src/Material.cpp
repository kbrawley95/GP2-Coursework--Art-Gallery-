#include "Material.h"

Material::Material()
{
	//Compile Shader
	shader = shared_ptr<Shader>(new Shader("", ""));
}

Material::Material(string vs, string fs)
{
	//Compile Shader
	shader = shared_ptr<Shader>(new Shader(vs, fs));
}

Material::~Material()
{

}

void Material::CalculateLighting(shared_ptr<Light> light)
{
	GLint ambientLightColourLocation = glGetUniformLocation(shader->currentShaderProgram, "ambientLightColour");
	GLint ambientMaterialColourLocation = glGetUniformLocation(shader->currentShaderProgram, "ambientMaterialColour");

	GLint diffuseLightColourLocation = glGetUniformLocation(shader->currentShaderProgram, "diffuseLightColour");
	GLint diffuseLightMaterialLocation = glGetUniformLocation(shader->currentShaderProgram, "diffuseMaterialColour");
	GLint lightDirectionLocation = glGetUniformLocation(shader->currentShaderProgram, "lightDirection");

	GLint specularLightColourLocation = glGetUniformLocation(shader->currentShaderProgram, "specularLightColour");
	GLint specularLightMaterialLocation = glGetUniformLocation(shader->currentShaderProgram, "specularMaterialColour");
	GLint specularPowerLocation = glGetUniformLocation(shader->currentShaderProgram, "specularPower");

	glUniform4fv(ambientLightColourLocation, 1, value_ptr(light->GetAmbientLightColour()));
	glUniform4fv(ambientMaterialColourLocation, 1, value_ptr(GetAmbientMaterial()));

	glUniform4fv(diffuseLightColourLocation, 1, value_ptr(light->GetDiffuseLightColour()));
	glUniform4fv(diffuseLightMaterialLocation, 1, value_ptr(GetDiffuseMaterial()));
	glUniform3fv(lightDirectionLocation, 1, value_ptr(light->GetLightDirection()));

	glUniform4fv(specularLightColourLocation, 1, value_ptr(light->GetSpecularLightColour()));
	glUniform4fv(specularLightMaterialLocation, 1, value_ptr(GetSpecularMaterial()));
	glUniform1f(specularPowerLocation, light->GetSpecularPower());
}