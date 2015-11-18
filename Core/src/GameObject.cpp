#include "GameObject.h"

GameObject::GameObject()
{
	transform = Transform();
	transform.position  = vec3(0, 0, 0);
	transform.rotation = vec3(0, 0, 0);
	transform.scale = vec3(1, 1, 1);
}

GameObject::~GameObject()
{

}