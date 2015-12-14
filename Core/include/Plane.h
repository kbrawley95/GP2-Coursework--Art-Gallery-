#ifndef _PLANE_H
#define _PLANE_H

#include "Common.h"

class Plane
{
public:
	glm::vec3 normal;
	float distance;

	Plane()
	{

	}

	Plane(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3)
	{
		normal = glm::normalize(glm::cross(p2 - p1, p3 - p1));
		distance = glm::dot(normal, p1);
	}

	Plane(glm::vec3 normal, float distance)
	{
		this->normal = normal;
		this->distance = distance;
	}

	float Distance(glm::vec3 point)
	{
		return glm::dot(point, normal) + distance;
	}
};

#endif