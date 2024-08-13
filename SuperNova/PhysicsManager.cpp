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

//������ Physics�� ����Ǿ� �ִ�, Position�� �и�, GameObject�� ����.
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

//[TW] PhysicsManager�� �Լ��� �޾Ƽ� �̸� ������ �����ؾ� �Ǵ� ��Ȳ.
//Physics�� ������ �޴� ��ü���ٰ��� ������ �� �ִ� ��, 
//�׸���, �浹�� ������Ʈ���ٰ��� ���� ������ �� �־�� �Ѵ�.
//

