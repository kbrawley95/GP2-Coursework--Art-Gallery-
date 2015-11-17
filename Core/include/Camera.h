#ifndef _CAMERA_H
#define _CAMERA_H

#include "Common.h"

class Camera
{
public:

	//matrices
	mat4 viewMatrix;
	mat4 projMatrix;

	Camera(const vec3& pos, float fov, float aspect, float zNear, float zFar);
	~Camera();

	void Update()
	{
		
	}

	mat4 GetLookAt();

	vec3 Position()
	{
		return m_Position;
	}

	vec3 Rotation()
	{
		return m_Rotation;
	}

	vec3 Scale()
	{
		return m_Scale;
	}

	void SetPosition(vec3& pos)
	{
		m_Position += pos;
	}

	void SetRotation(vec3& rotate)
	{
		m_Rotation.y += rotate.y;
	}


private:
	vec3 m_Forward;
	vec3 m_Up;


	vec3 m_Position;
	vec3 m_Rotation;
	vec3 m_Scale;
};

#endif
