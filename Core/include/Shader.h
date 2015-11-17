#ifndef _SHADER_H
#define _SHADER_H

#include "Common.h"

class Shader
{
public:
	Shader();
	~Shader();


	enum SHADER_TYPE
	{
		VERTEX_SHADER = GL_VERTEX_SHADER,
		FRAGMENT_SHADER = GL_FRAGMENT_SHADER
	};

	GLuint LoadShaderFromMemory(const char * pMem, SHADER_TYPE shaderType);

	GLuint LoadShaderFromFile(const string& filename, SHADER_TYPE shaderType);

	bool CheckForCompilerErrors(GLuint shaderProgram);

	bool CheckForLinkErrors(GLuint program);


};

#endif

