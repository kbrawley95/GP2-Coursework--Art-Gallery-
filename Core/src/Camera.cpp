#include "Camera.h"


Camera::Camera(const vec3& pos, float fov, float aspect, float zNear, float zFar)
{
	projMatrix = perspective(fov, aspect, zNear, zFar);
	viewMatrix = lookAt(m_Position, m_Position + m_Forward, m_Up);
	m_Position = pos;
	m_Forward = vec3(0, 0, 1);
	m_Up = vec3(0, 1, 0);
}

Camera::~Camera()
{
}

mat4 Camera::GetLookAt()
{
	return projMatrix* viewMatrix;
}

void Camera::Update()
{
	projMatrix;
	viewMatrix = lookAt(m_Position, m_Position + m_Forward, m_Up);

	mat4 translationMatrix = translate(mat4(1.0f), m_Position);
	mat4 scaleMatrix = scale(mat4(1.0f), m_Scale);

	mat4 rotationMatrix = rotate(mat4(1.0f), m_Rotation.x, vec3(1.0f, 0.0f, 0.0f))*
		rotate(mat4(1.0f), m_Rotation.y, vec3(0.0f, 1.0f, 0.0f))*
		rotate(mat4(1.0f), m_Rotation.z, vec3(0.0f, 0.0f, 1.0f));
}
