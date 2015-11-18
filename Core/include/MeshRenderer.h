#ifndef _MESHRENDERER
#define _MESHRENDERER

#include "Common.h"
#include "Component.h"
#include "Camera.h"
#include "Shader.h"
#include "Mesh.h"

class MeshRenderer : public Component
{
public:
	MeshRenderer();
	~MeshRenderer();

	void Update();
	void RenderGameObject(Camera* camera);

private:

	Shader* shader;

	mat4 MVPMatrix;
	GLuint fullScreenShaderProgram;
};

#endif