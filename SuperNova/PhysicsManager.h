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

//�� �Ŀ� Scene�������� �̸� ��������� �Ѵ�.