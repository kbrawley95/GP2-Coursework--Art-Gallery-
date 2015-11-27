	#ifndef _SHADER_H
	#define _SHADER_H

	#include "Common.h"
	#include "Component.h"

	class Shader
	{
	public:
		enum SHADER_TYPE
		{
			VERTEX_SHADER = GL_VERTEX_SHADER,
			FRAGMENT_SHADER = GL_FRAGMENT_SHADER
		};

		GLuint currentShaderProgram = 0;

		Shader(const std::string& vs, const std::string& fs);
		~Shader();

		GLuint LoadShaderFromMemory(const char * pMem, SHADER_TYPE shaderType);

		GLuint LoadShaderFromFile(const string& filename, SHADER_TYPE shaderType);

		bool CheckForCompilerErrors(GLuint shaderProgram);

		bool CheckForLinkErrors(GLuint program);

	private:

	};

	#endif