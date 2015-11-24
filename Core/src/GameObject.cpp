#include "GameObject.h"

GameObject::GameObject()
{
	transform = Transform();
	transform.position  = vec3(0, 0, 0);
	transform.rotation = vec3(0, 0, 0);
	transform.scale = vec3(1, 1, 1);
}

GameObject::~GameObject()
{

}

mat4 GameObject::GetModelMatrix()
{

	mat4 translationMatrix = translate(mat4(1.0f), transform.position.ConvertToVec3());
	mat4 scaleMatrix = scale(mat4(1.0f), transform.scale.ConvertToVec3());

	mat4 rotationMatrix = rotate(mat4(1.0f), transform.rotation.x, vec3(1.0f, 0.0f, 0.0f))*
		rotate(mat4(1.0f), transform.rotation.y, vec3(0.0f, 1.0f, 0.0f))*
		rotate(mat4(1.0f), transform.rotation.z, vec3(0.0f, 0.0f, 1.0f));

	m_ModelMatrix = translationMatrix*scaleMatrix*rotationMatrix;
	return m_ModelMatrix;
}

void GameObject::LoadShader(const string& vsFilename, const string& fsFilename)
{

}
