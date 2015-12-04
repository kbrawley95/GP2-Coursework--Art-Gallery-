#ifndef _CAMERA_H
#define _CAMERA_H

#include "Common.h"
#include "Transform.h"
#include "Input.h"

class Camera
{
public:
	Transform transform;
	float fov;
	float aspectRatio;
	float zNear;
	float zFar;

	//Keyboard State
	int currentTime, prevTime;
	float deltaTime;

	void Update()
	{
		prevTime = currentTime;
		currentTime = SDL_GetTicks();
		deltaTime = (currentTime - prevTime) / 1000.0f;
		KeyboardState();
	}

	void KeyboardState()
	{
		if (keysPressed[SDLK_a])
		{
			transform.position.x += 10.0f*deltaTime;
		}
		else if (keysPressed[SDLK_d])
		{
			transform.position.x -= 10.0f*deltaTime;
		}
		else if (keysPressed[SDLK_w])
		{
			transform.position.z += 10.0f*deltaTime;
		}
		else if (keysPressed[SDLK_s])
		{
			transform.position.z -= 10.0f*deltaTime;
		}

		if (keysPressed[SDLK_LEFT])
		{
			transform.rotation.y += 10.0f*deltaTime;
		}
		else if (keysPressed[SDLK_RIGHT])
		{
			transform.rotation.y -= 10.0f*deltaTime;
		}
		else if (keysPressed[SDLK_UP])
		{
			transform.rotation.z += 10.0f*deltaTime;
		}
		else if (keysPressed[SDLK_DOWN])
		{
			transform.rotation.z -= 10.0f*deltaTime;
		}

		transform.rotation.y -= mouseDelta.x;
		transform.rotation.x += mouseDelta.y;

		if (transform.rotation.x < -30)
			transform.rotation.x = -30;
		else if (transform.rotation.x > 30)
			transform.rotation.x = 30;

		forward = glm::vec3(transform.GetWorldMatrix()[2]);
		
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