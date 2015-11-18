#include "Camera.h"

Camera::Camera(float fov, float aspect, float zNear, float zFar)
{
	m_Forward = vec3(0, 0, 1);
	m_Up = vec3(0, 1, 0);
	projMatrix = perspective(fov, aspect, zNear, zFar);
	viewMatrix = lookAt(m_pos, m_pos + m_Forward, m_Up);
}

Camera::~Camera()
{

}

void Camera::Start()
{

}

void Camera::Update()
{
	viewMatrix = lookAt(m_pos, m_pos + m_Forward, m_Up);

	mat4 translationMatrix = translate(mat4(1.0f), m_pos);
	mat4 scaleMatrix = scale(mat4(1.0f), m_scale);

	mat4 rotationMatrix = rotate(mat4(1.0f), m_rot.x, vec3(1.0f, 0.0f, 0.0f))*
		rotate(mat4(1.0f), m_rot.y, vec3(0.0f, 1.0f, 0.0f))*
		rotate(mat4(1.0f), m_rot.z, vec3(0.0f, 0.0f, 1.0f));

	gameObject->transform.position = m_pos;
	gameObject->transform.rotation = m_rot;
	gameObject->transform.scale = m_scale;
}

void Camera::Render()
{

}

mat4 Camera::GetLookAt()
{
	return projMatrix* viewMatrix;
}