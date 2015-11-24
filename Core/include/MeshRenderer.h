#ifndef _MESHRENDERER
#define _MESHRENDERER

#include "Common.h"
#include "Mesh.h"
#include "Component.h"
#include "Camera.h"
#include "Light.h"
#include "Material.h"

class MeshRenderer : public Component
{
public:

	
	MeshRenderer();
	~MeshRenderer();

	void RenderGameObject(Camera* camera, shared_ptr<Light> light);

	void Update(Camera* camera, shared_ptr<Light> light);

private:

	shared_ptr<Material> material;
	mat4 MVPMatrix;
};

#endif

