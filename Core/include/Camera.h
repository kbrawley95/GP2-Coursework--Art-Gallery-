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

	//Keyboard State
	const Uint8 *keyboardState;
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
		keyboardState = SDL_GetKeyboardState(NULL);

		if (keyboardState[SDL_SCANCODE_A])
		{
			transform.position.x += 10.0f*deltaTime;
		}
		else if (keyboardState[SDL_SCANCODE_D])
		{
			transform.position.x -= 10.0f*deltaTime;
		}
		else if (keyboardState[SDL_SCANCODE_W])
		{
			transform.position.z += 10.0f*deltaTime;
		}
		else if (keyboardState[SDL_SCANCODE_S])
		{
			transform.position.z -= 10.0f*deltaTime;
		}
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