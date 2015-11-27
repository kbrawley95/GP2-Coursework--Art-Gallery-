#ifndef _CAMERA_H
#define _CAMERA_H

#include "Common.h"
#include "Transform.h"

class Camera
{
public:
	Transform transform;
	float fov;
	float aspectRatio;
	float zNear;
	float zFar;

	void Update()
	{

	}

	Camera()
	{
		fov = 45.0f;
		aspectRatio = 800/ 600;
		zNear = 0.1f;
		zFar = 1000.0f;
		forward = glm::vec3(0.0f, 0.0f, 1.0f);
		up = glm::vec3(0.0f, 1.0f, 0.0f);
		transform = Transform();
	}
	~Camera()
	{

	}

	glm::mat4 GetViewMatrix()
	{
		return glm::lookAt(transform.position.ConvertToVec3(), transform.position.ConvertToVec3() + forward, up);
	}

	glm::mat4 GetProjectionMatrix()
	{
		return glm::perspective(fov, aspectRatio, zNear, zFar);
	}
private:
	glm::vec3 forward;
	glm::vec3 up;
};

#endif