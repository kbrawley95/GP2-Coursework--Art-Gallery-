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
	viewMatrix = lookAt((*gameObject).transform.position.ConvertToVec3(), (*gameObject).transform.position.ConvertToVec3() + forward, up);
}

Camera::~Camera()
{

}

void Camera::Update()
{
	viewMatrix = lookAt((*gameObject).transform.position.ConvertToVec3(), (*gameObject).transform.position.ConvertToVec3() + forward, up);

	mat4 translationMatrix = translate(mat4(1.0f), (*gameObject).transform.position.ConvertToVec3());
	mat4 scaleMatrix = scale(mat4(1.0f), (*gameObject).transform.scale.ConvertToVec3());

	mat4 rotationMatrix = rotate(mat4(1.0f), (*gameObject).transform.rotation.ConvertToVec3().x, vec3(1.0f, 0.0f, 0.0f))*
		rotate(mat4(1.0f), (*gameObject).transform.rotation.ConvertToVec3().y, vec3(0.0f, 1.0f, 0.0f))*
		rotate(mat4(1.0f), (*gameObject).transform.rotation.ConvertToVec3().z, vec3(0.0f, 0.0f, 1.0f));
}

void Camera::Input(SDL_Event* e)
{
	if (e->type == SDL_KEYDOWN)
	{
		switch (e->key.keysym.sym)
		{
		case SDLK_a:
			cout << gameObject->transform.position.x << endl;
			gameObject->transform.position.x -= 2.0f * deltaTime;
			break;
		case SDLK_d:
			cout << gameObject->transform.position.x << endl;
			gameObject->transform.position.x += 2.0f * deltaTime;
			break;
		case SDLK_w:
			cout << gameObject->transform.position.z << endl;
			gameObject->transform.position.z += 2.0f * deltaTime;
			break;
		case SDLK_s:
			cout << gameObject->transform.position.z << endl;
			gameObject->transform.position.z -= 2.0f * deltaTime;
			break;
		}
	}
}