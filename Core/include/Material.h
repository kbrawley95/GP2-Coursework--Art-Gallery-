#ifndef _MATERIAL_H
#define _MATERIAL_H

#include "Common.h"
#include "Vector.h"

class Material
{
public:
	Vector4 ambientMaterial;
	Vector4 diffuseMaterial;
	Vector4 specularMaterial;
	float specularPower;
	
	Material(std::string vsPath, std::string fsPath);
	~Material();
	void LoadTexture(std::string filename);

	//Skybox Functions
	void SetCubeMapTextures(const std::string& posX, const std::string& negX, const std::string& posY, const std::string& negY, const std::string& posZ, const std::string& negZ);

	GLuint LoadCubemapTexture(const std::string& posX, const std::string& negX, const std::string& posY, const std::string& negY, const std::string& posZ, const std::string& negZ);
	void LoadCubeMapFace(const std::string& filename, GLenum face);


	GLuint GetTexture();
	GLuint GetShader();

private:
	GLuint shaderProgram;
	GLuint diffuseMap;
	GLuint environmentMap;

	enum SHADER_TYPE
	{
		VERTEX_SHADER = GL_VERTEX_SHADER,
		FRAGMENT_SHADER = GL_FRAGMENT_SHADER
	};
	GLuint LoadShaderFromMemory(const char * pMem, SHADER_TYPE shaderType);
	GLuint LoadShaderFromFile(const std::string& filename, SHADER_TYPE shaderType);
	bool CheckForCompilerErrors(GLuint shaderProgram);
	bool CheckForLinkErrors(GLuint program);
	GLuint LoadTextureFromFile(const std::string& filename);
	
	GLuint ConvertSDLSurfaceToTexture(SDL_Surface * surface);
};

#endif