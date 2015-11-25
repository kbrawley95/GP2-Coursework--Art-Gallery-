#ifndef _MESHRENDERER
#define _MESHRENDERER

#include "Common.h"
#include "Mesh.h"
#include "Component.h"
#include "Camera.h"
#include "Material.h"
#include "GameObject.h"
#include "Scene.h"

class MeshRenderer : public Component
{
public:
	GLuint VBO;
	GLuint EBO;
	GLuint VAO;

	MeshRenderer(shared_ptr<GameObject> g);
	~MeshRenderer();

	void SetMaterial(shared_ptr<Material> material);
	shared_ptr<Material> GetMaterial();

	void Update();
	void Render();

private:

	shared_ptr<Material> material;
	mat4 MVPMatrix;
};

#endif