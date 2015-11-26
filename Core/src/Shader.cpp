#include "Shader.h"

Shader::Shader(const std::string& vs, const std::string& fs)
{
	GLuint vs_shader = LoadShaderFromFile(vs, VERTEX_SHADER);
	CheckForCompilerErrors(vs_shader);

	GLuint fs_shader = LoadShaderFromFile(fs, FRAGMENT_SHADER);
	CheckForCompilerErrors(fs_shader);

	currentShaderProgram = glCreateProgram();
	glAttachShader(currentShaderProgram, vs_shader);
	glAttachShader(currentShaderProgram, fs_shader);

	//Link attributes
	glBindAttribLocation(currentShaderProgram, 0, "vertexPosition");
	glBindAttribLocation(currentShaderProgram, 1, "vertexColour");
	glBindAttribLocation(currentShaderProgram, 2, "vertexTexCoords");
	glBindAttribLocation(currentShaderProgram, 3, "vertexNormal");

	glLinkProgram(currentShaderProgram);
	CheckForLinkErrors(currentShaderProgram);
	//now we can delete the VS & FS Programs
	glDeleteShader(vs_shader);
	glDeleteShader(fs_shader);
}

Shader::~Shader()
{
	glDeleteProgram(currentShaderProgram);
}

GLuint Shader::LoadShaderFromFile(const std::string& filename, SHADER_TYPE shaderType)
{
	string fileContents;
	ifstream file;
	file.open(filename.c_str(), std::ios::in);
	if (!file)
	{
		cout << "File could not be loaded" << endl;
		return -1;
	}

	//calculate file size
	if (file.good())
	{
		file.seekg(0, std::ios::end);
		unsigned long len = file.tellg();
		file.seekg(std::ios::beg);
		if (len == 0)
		{
			std::cout << "File has no contents " << std::endl;
			return -1;
		}

		fileContents.resize(len);
		file.read(&fileContents[0], len);
		file.close();
		GLuint program = LoadShaderFromMemory(fileContents.c_str(), shaderType);
		return program;
	}
	cout << "Cannot load shader " + filename << endl;
	return -1;
}

//Load it from a memory buffer
GLuint Shader::LoadShaderFromMemory(const char * pMem, SHADER_TYPE shaderType)
{
	GLuint program = glCreateShader(shaderType);
	glShaderSource(program, 1, &pMem, NULL);
	glCompileShader(program);
	return program;
}

bool Shader::CheckForCompilerErrors(GLuint shaderProgram)
{
	GLint isCompiled = 0;
	glGetShaderiv(shaderProgram, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(shaderProgram, GL_INFO_LOG_LENGTH, &maxLength);
		//The maxLength includes the NULL character
		char* infoLog = new char[maxLength];
		glGetShaderInfoLog(shaderProgram, maxLength, &maxLength, &infoLog[0]);
		cout << "Shader not compiled " << infoLog << endl;
		//We don't need the shader anymore.
		glDeleteShader(shaderProgram);
		return true;
	}

	return false;
}

bool Shader::CheckForLinkErrors(GLuint program)
{
	GLint isLinked = 0;
	glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
	if (isLinked == GL_FALSE) 
	{
		GLint maxLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
		//The maxLength includes the NULL character
		char* infoLog = new char[maxLength];
		glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
		cout << "Shader not linked " << infoLog << endl;
		//We don't need the shader anymore.
		glDeleteProgram(program);
		delete[] infoLog;
		return true;
	}
	return false;
}