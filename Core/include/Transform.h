#ifndef _TRANSFORM_H
#define _TRANSFORM_H

#include "Vector.h"

class Transform
{
public:
	Vector3 position;
	Vector3 rotation;
	Vector3 scale;

	Transform()
	{
		position = Vector3(0, 0, 0);
		rotation = Vector3(0, 0, 0);
		scale = Vector3(1, 1, 1);
	}

	glm::mat4 GetWorldMatrix()
	{
		glm::mat4 pos = glm::translate(glm::mat4(1.0f), position.ConvertToVec3());
		glm::mat4 sca = glm::scale(glm::mat4(1.0f), scale.ConvertToVec3());

		glm::mat4 rot = glm::rotate(glm::mat4(1.0f), rotation.x, glm::vec3(1.0f, 0.0f, 0.0f))*
			glm::rotate(glm::mat4(1.0f), rotation.y, glm::vec3(0.0f, 1.0f, 0.0f))*
			glm::rotate(glm::mat4(1.0f), rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	
		return sca * rot * pos;
	}
};

#endif