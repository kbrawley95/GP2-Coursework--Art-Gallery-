#include "Camera.h"

Camera::~Camera()
{

}


mat4 Camera::GetLookAt()
{
	return projMatrix * viewMatrix;
}



