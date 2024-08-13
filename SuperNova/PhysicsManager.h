#pragma once
#include <vector>
#include <string>
#include "Transform.h"
#include "GameObject.h"

class PhysicsManager
{
public:
	PhysicsManager();
	~PhysicsManager();

	static PhysicsManager& GetInstance()
	{
		static PhysicsManager inst;
		return inst;
	}
	
	void Initialize();
	void TakeInBodies(GameObject* object);
	void ApplyForceToBodies();
	void ClearBodiesInVector();
	


private:
	std::vector<GameObject*> m_physicsObjList;

};

//이 후에 Scene루프에서 이를 시행해줘야 한다.