///Collision�� ���� �Ϸ�� ���¿��� �ϴ��� Hold. [23.02.13]

#include "CollisionManager.h"
#include "GameObject.h"
#include "CollisionDetection.h"
#include "Collider.h"
#include "Debug.h"
#include "Transform.h"
const int RESERVE_START_CNT = 150;

CollisionManager::CollisionManager()
{

}

CollisionManager::~CollisionManager()
{

}

void CollisionManager::Initialize()
{
	m_CollideObjectList.reserve(RESERVE_START_CNT);
}

// [TW] ���ʿ� ���⿡ ���� �ֵ��� ��� �浹�� ������ �ֵ��̴�, �׸��� WorldSpace ���� ȭ�鿡 ������ �ֵ�.
// ���Ŀ� �ٲ� ��, GetWorldPosition()���� ���ϰ� Ư�� ������ Rect2D �ȿ� �ִ��Ŀ� ���� ����.
//���� ȭ�� ���̴� ������ �ҼӵǾ� �ְ�, �� �� �ݶ��̴��� �ƴ� �ֵ�.
void CollisionManager::TakeInCollidableObjects(GameObject* gameObject)
{
	m_CollideObjectList.push_back(gameObject);
}

//��� �浹 �����ϰ� (��ȿ��) ������Ʈ�� TakeInCollidableObjects�� ���� ���� ��, ����Ǵ� ��!
void CollisionManager::UpdateColliders()
{
	for (auto it : m_CollideObjectList)
	{
		CollisionDetection::UpdateCollisionStates(it);
	}
}

void CollisionManager::CompareColliders()
{
	for (auto it : m_CollideObjectList) //���� ����
	{
		for (auto it2 : m_CollideObjectList) //�ΰ����� ������Ʈ.
		{
			if (it != it2)
			{
				//Debug::Trace("Got In Half");
				bool temp = CollisionDetection::DetectCollision(it, it2); //�ݸ����� ����� ��ȯ����.
				//������ it, it2�� �� �� ���̴�, ���ʸ� �������ָ� �ȴ�.
				if (temp)
				{
					it->GetPCollider()->SetOtherCollidedObject(it2);
					it2->GetPCollider()->SetOtherCollidedObject(it);
				}
				it->SetIsCollided(temp);
				it2->SetIsCollided(temp);
				//Debug::Trace("image index: ", it->GetImageIndex());
				//Debug::Trace("HERE?", temp);
				//Enter�� �Ұ��̴�.
			}
		}
	}
}

void CollisionManager::ClearColliderList()
{
	m_CollideObjectList.clear();
}

bool CollisionManager::CheckCollision(GameObject* obj)
{
	if (obj->GetIsCollided() == true)
	{
		return true;
	}
	else
	{
		false;
	}
}

//[TW] ������Ʈ�� ���� �� �� �ִ� �Լ���!


