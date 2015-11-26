#ifndef _CAMERA_H
#define _CAMERA_H

#include "Common.h"
#include "Component.h"
#include "GameObject.h"
#include "Transform.h"
#include "Scene.h"

class Camera : public Component
{
public:
	mat4 viewMatrix;
	mat4 projMatrix;

	float fov;
	float aspect;
	float zNear;
	float zFar;

	void Update();
	void Input(SDL_Event* e);

	Camera(shared_ptr<GameObject> g);
	~Camera();

private:
	vec3 forward;
	vec3 up;
};

#endif