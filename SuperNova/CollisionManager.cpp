///Collision은 거의 완료된 상태에서 일단은 Hold. [23.02.13]

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

// [TW] 애초에 여기에 들어올 애들은 모두 충돌이 가능할 애들이다, 그리고 WorldSpace 기준 화면에 들어오는 애들.
// 추후에 바뀔 것, GetWorldPosition()같은 애하고 특정 범위의 Rect2D 안에 있느냐에 따라서 동작.
//현재 화면 보이는 범위에 소속되어 있고, 그 중 콜라이더가 아닌 애들.
void CollisionManager::TakeInCollidableObjects(GameObject* gameObject)
{
	m_CollideObjectList.push_back(gameObject);
}

//모든 충돌 가능하고 (유효한) 오브젝트가 TakeInCollidableObjects를 통해 들어온 후, 실행되는 것!
void CollisionManager::UpdateColliders()
{
	for (auto it : m_CollideObjectList)
	{
		CollisionDetection::UpdateCollisionStates(it);
	}
}

void CollisionManager::CompareColliders()
{
	for (auto it : m_CollideObjectList) //메인 옵젝
	{
		for (auto it2 : m_CollideObjectList) //부가적인 오브젝트.
		{
			if (it != it2)
			{
				//Debug::Trace("Got In Half");
				bool temp = CollisionDetection::DetectCollision(it, it2); //콜리젼의 결과를 반환받음.
				//어차피 it, it2에 다 돌 것이니, 한쪽만 적용해주면 된다.
				if (temp)
				{
					it->GetPCollider()->SetOtherCollidedObject(it2);
					it2->GetPCollider()->SetOtherCollidedObject(it);
				}
				it->SetIsCollided(temp);
				it2->SetIsCollided(temp);
				//Debug::Trace("image index: ", it->GetImageIndex());
				//Debug::Trace("HERE?", temp);
				//Enter만 할것이다.
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

//[TW] 오브젝트가 갖다 쓸 수 있는 함수들!


