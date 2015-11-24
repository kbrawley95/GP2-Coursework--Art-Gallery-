#ifndef _MATERIAL_H
#define _MATERIAL_H

#include"Common.h"
#include "Component.h"

class Material : public Component
{
public:

	shared_ptr<Shader> vs;
	shared_ptr<Shader> fs;

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

	//Use Defuse shader by default
	Material()
	{
		//Compile Shader
	}

	Material(shared_ptr<Shader> vs, shared_ptr<Shader> fs)
	{
		//Compile Shader
		Material::vs = vs;
		Material::fs = fs;
	}

	//Memory cleanup
	~Material()
	{

	}

private:
	vec4 m_AmbientMaterial;
	vec4 m_DiffuseMaterial;
	vec4 m_SpecularMaterial;
	GLuint m_DiffuseMap;

};


#endif