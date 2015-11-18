#ifndef _CAMERA_H
#define _CAMERA_H

#include "Common.h"
#include "GameObject.h"

class Camera : public Component
{
public:	
	void Start();
	void Update();
	void Render();
	mat4 GetLookAt();

	Camera(float fov, float aspect, float zNear, float zFar);
	~Camera();
private:
	mat4 viewMatrix;
	mat4 projMatrix;
	vec3 m_Forward;
	vec3 m_Up;

	vec3 m_pos;
	vec3 m_rot;
	vec3 m_scale;
};

#endif