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
	Material(string vs, string fs);

	//Memory cleanup
	~Material();

	void CalculateLighting(shared_ptr<Light> light);
	void SetMainTexture(const string& filename);

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

private:
	vec4 m_AmbientMaterial;
	vec4 m_DiffuseMaterial;
	vec4 m_SpecularMaterial;
	GLuint m_DiffuseMap;

};


#endif