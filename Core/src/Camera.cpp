#include "Camera.h"

Camera::Camera(shared_ptr<GameObject> g) : Component(g)
{
	fov = 90;
	aspect = 1;
	zNear = 0.1f;
	zFar = 1000;
	forward = vec3(0, 0, 1);
	up = vec3(0, 1, 0);
	projMatrix = perspective(fov, aspect, zNear, zFar);
	viewMatrix = lookAt(pos, pos + forward, up);
}

Camera::~Camera()
{

}

void Camera::Update()
{
	viewMatrix = lookAt(pos, pos + forward, up);

	mat4 translationMatrix = translate(mat4(1.0f), pos);
	mat4 scaleMatrix = scale(mat4(1.0f), sca);

	mat4 rotationMatrix = rotate(mat4(1.0f), rot.x, vec3(1.0f, 0.0f, 0.0f))*
		rotate(mat4(1.0f), rot.y, vec3(0.0f, 1.0f, 0.0f))*
		rotate(mat4(1.0f), rot.z, vec3(0.0f, 0.0f, 1.0f));

	gameObject->transform->position = pos;
	gameObject->transform->rotation = rot;
	gameObject->transform->scale = sca;
}

mat4 Camera::GetLookAt()
{
	return projMatrix * viewMatrix;
}