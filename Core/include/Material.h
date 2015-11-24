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

private:
	vec4 m_AmbientMaterial;
	vec4 m_DiffuseMaterial;
	vec4 m_SpecularMaterial;
	GLuint m_DiffuseMap;

};


#endif