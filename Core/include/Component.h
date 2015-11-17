#ifndef _COMPONENT_H
#define _COMPONENT_H

#include "Common.h"
#include "GameObject.h"

class Component
{
public:

	Component() :m_OwnerGameObj(0){}
	~Component();

	typedef string gameObjID;

	virtual void Update();

	GameObject* GetOwner()const { return m_OwnerGameObj; }

private:

	GameObject* m_OwnerGameObj;
	
};

#endif

