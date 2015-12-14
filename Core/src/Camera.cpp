#include "Camera.h"

Camera::Camera(float fov, float ratio, float zNear, float zFar)
{
	this->fov = fov;
	this->zNear = zNear;
	this->zFar = zFar;
	ChangeRatio(ratio);

	right = glm::vec3(transform.GetWorldMatrix()[0]);
	up = glm::vec3(transform.GetWorldMatrix()[1]);
	forward = glm::vec3(transform.GetWorldMatrix()[2]);
}

bool Camera::FrustumCulling(std::vector<Vertex> vertices, glm::vec3 pos)
{
	CumputePlanes();

	for (int i = 0; i < 6; i++)
	{
		for (int k = 0; k < vertices.size(); k++)
		{
			if (planes[i].Distance(vertices[k].position + pos) < 0)
				return false;
		}
	}

	return true;
}

void Camera::CumputePlanes()
{
	glm::vec3 dir, nc, fc;
	glm::vec3 ntl, ntr, nbl, nbr;
	glm::vec3 ftl, ftr, fbl, fbr;

	// compute the centers of the near and far planes
	nc = transform.position.ConvertToVec3() + forward * zNear;
	fc = transform.position.ConvertToVec3() + forward * zFar;

	// compute the 4 corners of the frustum on the near plane
	ntl = nc + up * nearPlane.y - right * nearPlane.x;
	ntr = nc + up * nearPlane.y + right * nearPlane.x;
	nbl = nc - up * nearPlane.y - right * nearPlane.x;
	nbr = nc - up * nearPlane.y + right * nearPlane.x;

	// compute the 4 corners of the frustum on the far plane
	ftl = fc + up * farPlane.y - right * farPlane.x;
	ftr = fc + up * farPlane.y + right * farPlane.x;
	fbl = fc - up * farPlane.y - right * farPlane.x;
	fbr = fc - up * farPlane.y + right * farPlane.x;

	// compute the six planes
	// the function set3Points assumes that the points
	// are given in counter clockwise order
	planes[0] = Plane(ntr, ntl, ftl);//Top
	planes[1] = Plane(nbl, nbr, fbr);//Bottom
	planes[2] = Plane(ntl, nbl, fbl);//Left
	planes[3] = Plane(nbr, ntr, ftr);//Right
	planes[4] = Plane(ntl, ntr, nbr);//Near
	planes[5] = Plane(ftr, ftl, fbl);//Far
}

void Camera::Update()
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