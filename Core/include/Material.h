#ifndef _MATERIAL_H
#define _MATERIAL_H

#include"Common.h"
#include "Component.h"
#include "Shader.h"

class Material : public Component
{
public:

	shared_ptr<Shader> vs;
	shared_ptr<Shader> fs;

	vec4& GetAmbientMaterial()
	{
		return m_AmbientMaterial;
	};

	vec4& GetDiffuseMaterial()
	{
		return m_DiffuseMaterial;
	};

	vec4& GetSpecularMaterial()
	{
		return m_SpecularMaterial;
	};

	//Use Defuse shader by default
	Material()
	{
		//Compile Shader
	}

	Material(shared_ptr<Shader> vs, shared_ptr<Shader> fs)
	{
		//Compile Shader
		Material::vs = vs;
		Material::fs = fs;
	}

	//Memory cleanup
	~Material()
	{

	}

	void CalculateLighting(shared_ptr<Light> light)
	{
		GLint ambientLightColourLocation = glGetUniformLocation(vs->currentShaderProgram, "ambientLightColour");
		GLint ambientMaterialColourLocation = glGetUniformLocation(vs->currentShaderProgram, "ambientMaterialColour");

		GLint diffuseLightColourLocation = glGetUniformLocation(vs->currentShaderProgram, "diffuseLightColour");
		GLint diffuseLightMaterialLocation = glGetUniformLocation(vs->currentShaderProgram, "diffuseMaterialColour");
		GLint lightDirectionLocation = glGetUniformLocation(vs->currentShaderProgram, "lightDirection");

		GLint specularLightColourLocation = glGetUniformLocation(vs->currentShaderProgram, "specularLightColour");
		GLint specularLightMaterialLocation = glGetUniformLocation(vs->currentShaderProgram, "specularMaterialColour");
		GLint specularPowerLocation = glGetUniformLocation(vs->currentShaderProgram, "specularPower");

		glUniform4fv(ambientLightColourLocation, 1, value_ptr(light->GetAmbientLightColour()));
		glUniform4fv(ambientMaterialColourLocation, 1, value_ptr(GetAmbientMaterial()));

		glUniform4fv(diffuseLightColourLocation, 1, value_ptr(light->GetDiffuseLightColour()));
		glUniform4fv(diffuseLightMaterialLocation, 1, value_ptr(GetDiffuseMaterial()));
		glUniform3fv(lightDirectionLocation, 1, value_ptr(light->GetLightDirection()));

		glUniform4fv(specularLightColourLocation, 1, value_ptr(light->GetSpecularLightColour()));
		glUniform4fv(specularLightMaterialLocation, 1, value_ptr(GetSpecularMaterial()));
		glUniform1f(specularPowerLocation, light->GetSpecularPower());
	}

private:
	vec4 m_AmbientMaterial;
	vec4 m_DiffuseMaterial;
	vec4 m_SpecularMaterial;
	GLuint m_DiffuseMap;

};


#endif