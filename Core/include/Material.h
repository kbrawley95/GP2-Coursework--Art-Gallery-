#ifndef _MATERIAL_H
#define _MATERIAL_H

#include "Common.h"
#include "ShaderLoader.h"
#include "TextureLoader.h"

class Material
{
public:
	//Loads a default shader
	Material(std::string vsPath, std::string fsPath);
	~Material();
	void LoadTexture(std::string filename);

	GLuint GetTexture();
	GLuint GetShader();

private:
	GLuint shaderProgram;
	GLuint diffuseMap;
};

#endif