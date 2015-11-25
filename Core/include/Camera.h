#ifndef _CAMERA_H
#define _CAMERA_H

#include "Common.h"
#include "Component.h"
#include "GameObject.h"
#include "Transform.h"

class Camera : public Component
{
public:

	mat4 GetLookAt();
	void Update();

	Camera(float fov, float aspect, float zNear, float zFar);
	~Camera();

private:
	mat4 viewMatrix;
	mat4 projMatrix;
	vec3 forward;
	vec3 up;

	vec3 pos;
	vec3 rot;
	vec3 sca;
};

#endif