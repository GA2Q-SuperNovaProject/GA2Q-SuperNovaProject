#include "PhysicsManager.h"
#include "TimeManager.h"
#include "Transform.h"
#include "Debug.h"
const int MAX_PHYSICS_CNT = 150;

PhysicsManager::PhysicsManager()
{

}

PhysicsManager::~PhysicsManager()
{

}

void PhysicsManager::Initialize()
{
	m_physicsObjList.reserve(MAX_PHYSICS_CNT);
}

//이전에 Physics가 적용되어 있다, Position만 분리, GameObject로 편입.
//

void PhysicsManager::TakeInBodies(GameObject* object)
{
	m_physicsObjList.push_back(object);
}

void PhysicsManager::ApplyForceToBodies()
{
	for (auto it : m_physicsObjList)
	{
		it->GetPBody()->Integrate(it->GetPTransform());
		//Debug::Trace("Physics ",it->GetPTransform()->GetPosition().x, it->GetPTransform()->GetPosition().y);
	}
	//Debug::Trace("Physics Applied!");
}

void PhysicsManager::ClearBodiesInVector()
{
	m_physicsObjList.clear();
}

//[TW] PhysicsManager는 함수를 받아서 이를 가지고 실행해야 되는 상황.
//Physics의 영향을 받는 전체에다가도 적용할 수 있는 힘, 
//그리고, 충돌한 오브젝트에다가도 힘을 적용할 수 있어야 한다.
//

