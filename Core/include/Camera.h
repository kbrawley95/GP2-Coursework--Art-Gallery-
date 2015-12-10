#ifndef _CAMERA_H
#define _CAMERA_H

#include "Common.h"
#include "Transform.h"
#include "Input.h"
#include "Time.h"

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
		if (keysPressed[SDLK_a])
		{
			Vector3 Translate = Vector3(glm::vec3(transform.GetWorldMatrix()[0]) * 10.0f * deltaTime);
			transform.position.x += Translate.x;
			transform.position.y += Translate.y;
			transform.position.z += Translate.z;
		}
		if (keysPressed[SDLK_d])
		{
			Vector3 Translate = Vector3(glm::vec3(transform.GetWorldMatrix()[0]) * 10.0f * deltaTime);
			transform.position.x -= Translate.x;
			transform.position.y -= Translate.y;
			transform.position.z -= Translate.z;
		}
		if (keysPressed[SDLK_w])
		{
			Vector3 Translate = Vector3(glm::vec3(transform.GetWorldMatrix()[2]) * 10.0f * deltaTime);
			transform.position.x += Translate.x;
			transform.position.y += Translate.y;
			transform.position.z += Translate.z;
		}
		if (keysPressed[SDLK_s])
		{
			Vector3 Translate = Vector3(glm::vec3(transform.GetWorldMatrix()[2]) * 10.0f * deltaTime);
			transform.position.x -= Translate.x;
			transform.position.y -= Translate.y;
			transform.position.z -= Translate.z;
		}

		transform.rotation.y -= mouseDelta.x;
		transform.rotation.x += mouseDelta.y;

		if (transform.rotation.x < -30)
			transform.rotation.x = -30;
		else if (transform.rotation.x > 30)
			transform.rotation.x = 30;

		forward = glm::vec3(transform.GetWorldMatrix()[2]);
		up = glm::vec3(transform.GetWorldMatrix()[1]);
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