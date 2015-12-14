#ifndef _CAMERA_H
#define _CAMERA_H

#include "Common.h"
#include "Transform.h"
#include "Input.h"
#include "Time.h"
#include "Vector.h"
#include "Vertex.h"
#include "Plane.h"

class Camera
{
public:
	Transform transform;
	
	Camera(float fov, float ratio, float zNear, float zFar);
	void Update();
	bool FrustumCulling(glm::vec3 pos);
	void CumputePlanes();

	void ChangeRatio(float r)
	{
		ratio = r;

		// compute width and height of the near and far plane sections
		float tang = glm::tan(fov * 0.5f) * 2;
		nearPlane.y = zNear * tang;
		nearPlane.x = nearPlane.y * ratio;
		farPlane.y = zFar  * tang;
		farPlane.x = farPlane.y * ratio;
	}
	glm::mat4 GetViewMatrix()
	{
		return glm::lookAt(transform.position.ConvertToVec3(), transform.position.ConvertToVec3() + forward, up);
	}
	glm::mat4 GetProjectionMatrix()
	{
		return glm::perspective(fov, ratio, zNear, zFar);
	}

private:
	float fov;
	float ratio;
	float zNear;
	float zFar;
	glm::vec3 forward;
	glm::vec3 up;
	glm::vec3 right;
	Vector2 nearPlane;
	Vector2 farPlane;
	Plane planes[6];
};

#endif