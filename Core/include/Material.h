#ifndef _MATERIAL_H
#define _MATERIAL_H

#include"Common.h"
#include "Component.h"
#include "Shader.h"
#include "Light.h"
#include "Texture.h"

class Material
{
public:

	shared_ptr<Shader> shader;
	//Use Defuse shader by default
	Material();
	Material(shared_ptr<Shader> s);
	Material(string vs, string fs);

	//Memory cleanup
	~Material();

	void CalculateLighting(shared_ptr<Light> light);
	void SetMainTexture(const string& filename);

	vec4& GetAmbientMaterial()
	{
		return ambientMaterial;
	};
	vec4& GetDiffuseMaterial()
	{
		return diffuseMaterial;
	};
	vec4& GetSpecularMaterial()
	{
		return specularMaterial;
	};
	GLuint& GetDiffuseMap()
	{
		return diffuseMap;
	}; 

private:
	vec4 ambientMaterial;
	vec4 diffuseMaterial;
	vec4 specularMaterial;
	GLuint diffuseMap;

};


#endif