#ifndef _MATERIAL_H
#define _MATERIAL_H

#include"Common.h"
#include "Component.h"
#include "Shader.h"
#include "Light.h"

class Material
{
public:

	shared_ptr<Shader> shader;

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

	GLuint& GetDiffuseMap()
	{
		return m_DiffuseMap;
	};

	//Use Defuse shader by default
	Material()
	{
		//Compile Shader
	}

	Material(string vs, string fs)
	{
		//Compile Shader
		shader = shared_ptr<Shader>(new Shader(vs, fs));
	}

	//Memory cleanup
	~Material()
	{

	}

	void CalculateLighting(Light* light)
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

private:
	vec4 m_AmbientMaterial;
	vec4 m_DiffuseMaterial;
	vec4 m_SpecularMaterial;
	GLuint m_DiffuseMap;

};


#endif