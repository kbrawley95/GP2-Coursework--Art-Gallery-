#include "Material.h"

Material::Material(std::string vsPath, std::string fsPath)
{
	std::cout << "Loading " << std::endl;
	std::cout << "-" << vsPath << std::endl;
	std::cout << "-" << fsPath << std::endl << std::endl;
	GLuint vertexShaderProgram = 0;
	vertexShaderProgram = loadShaderFromFile(vsPath, VERTEX_SHADER);
	checkForCompilerErrors(vertexShaderProgram);

	GLuint fragmentShaderProgram = 0;
	fragmentShaderProgram = loadShaderFromFile(fsPath, FRAGMENT_SHADER);
	checkForCompilerErrors(fragmentShaderProgram);

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShaderProgram);
	glAttachShader(shaderProgram, fragmentShaderProgram);

	//Link attributes
	glBindAttribLocation(shaderProgram, 0, "vertexPosition");
	glBindAttribLocation(shaderProgram, 1, "vertexColour");
	glBindAttribLocation(shaderProgram, 2, "vertexTexCoords");

	glLinkProgram(shaderProgram);
	checkForLinkErrors(shaderProgram);
	//now we can delete the VS & FS Programs
	glDeleteShader(vertexShaderProgram);
	glDeleteShader(fragmentShaderProgram);
}
Material::~Material()
{

}

void Material::LoadTexture(std::string filename)
{
	std::cout << "Loading " + filename << std::endl;
	//load texture & bind
	diffuseMap = loadTextureFromFile(filename);

	glBindTexture(GL_TEXTURE_2D, diffuseMap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glGenerateMipmap(GL_TEXTURE_2D);
}

GLuint Material::GetTexture()
{
	return diffuseMap;
}
GLuint Material::GetShader()
{
	return shaderProgram;
}