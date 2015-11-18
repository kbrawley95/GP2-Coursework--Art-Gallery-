#ifndef _SHADER_H
#define _SHADER_H

#include "Common.h"
#include "Component.h"

class Shader : public Component
{
public:

	enum SHADER_TYPE
	{
		VERTEX_SHADER = GL_VERTEX_SHADER,
		FRAGMENT_SHADER = GL_FRAGMENT_SHADER
	};

	GLuint LoadShaderFromMemory(const char * pMem, SHADER_TYPE shaderType);

	GLuint LoadShaderFromFile(const string& filename, SHADER_TYPE shaderType);

	bool CheckForCompilerErrors(GLuint shaderProgram);

	bool CheckForLinkErrors(GLuint program);

	GLuint currentDiffuseMap = 0;
	GLuint currentShaderProgram = 0;


	//Getters
	vec4 AmbientLightColour()
	{
		return ambientLightColour;
	}

	vec4 DiffuseLightColour()
	{
		return diffuseLightColour;
	}

	vec4 SpecularLightColour()
	{
		return specularLightColour;
	}

	float SpecularPower()
	{
		return specularPower;
	}

private:
	
	vec4 ambientLightColour = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	vec4 diffuseLightColour = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	vec4 specularLightColour = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	float specularPower = 25.0f;
};

#endif