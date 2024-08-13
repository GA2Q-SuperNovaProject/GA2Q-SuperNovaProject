#include "ObjectManager.h"
#include "GameObject.h"
#include "Camera.h"

///[TW] 여기다가 앞으로 모든 추가되는 오브젝트들을 정리해서 넣을 것.
#include "ObjectHeaderIncludes.h"

using namespace std;

GameObject* ObjectManager::CreateObject(eObjectTag tag, eObjectName name, Transform transform)
{
	///[TW] => 현재로서는 이렇게 하나, 중간에 세분화해서 추가 클래스를 만들어야 할 수도 있다.
	GameObject* tmpobject = nullptr;
	switch (tag)
	{
		case eObjectTag::PLAYER:
			tmpobject = new Player(tag, name, transform, GIF_STANDING);
			break;

		case eObjectTag::BACKGROUND:
			tmpobject = new Background(tag, name, transform);
			break;

		case eObjectTag::MAIN_UI:
			tmpobject = new MainUI(tag, name, transform);
			break;

		case eObjectTag::OPTION_UI:
			tmpobject = new OptionUI(tag, name, transform);
			break;

		case eObjectTag::INGAME_UI:
			tmpobject = new GameUI(tag, name, transform);
			break;

		case eObjectTag::PLANET:
			tmpobject = new Planet(tag, name, transform);
			break;

		case eObjectTag::OBSTACLE:
			tmpobject = new Obstacle(tag, name, transform);
			break;

		case eObjectTag::ITEM:
			tmpobject = new Item(tag, name, transform);
			break;

		case eObjectTag::EVENTOBJECT:
			tmpobject = new EventObject(tag, name, transform);
			break;

		case eObjectTag::BULLET: //별똥별과 별똥별 꼬리
			tmpobject = new Bullet(tag, name, transform);
			break;

		case eObjectTag::OPENING:
			tmpobject = new Opening_Object(tag, name, transform);
			break;

		case eObjectTag::NORMAL_ENDING:
			tmpobject = new Normal_Ending(tag, name, transform);
			break;

		case eObjectTag::TRUE_ENDING:
			tmpobject = new True_Ending(tag, name, transform);
			break;

		case eObjectTag::BAD_ENDING:
			tmpobject = new Bad_Ending(tag, name, transform);
			break;

		case eObjectTag::TWK_OBJECT_ONE:
			tmpobject = new TWKObject1(tag, name, transform, DEBUG_WOOD);
			break;

		case eObjectTag::TWK_OBJECT_TWO:
			tmpobject = new TWKObject2(tag, name, transform, DEBUG_BRICK);
			break;
	}
	m_ObjectList.push_back(tmpobject);

	return tmpobject;
}

void ObjectManager::DeleteObjectByName(eObjectName name)
{
	auto it = m_ObjectList.begin();
	for (it; it != m_ObjectList.end(); it++)
	{
		if ((*it)->GetName() == name)
		{
			m_ObjectList.erase(it);
			delete* it;
		}
	}
}


// 같은태그의 두놈 이상을 조진다.
void ObjectManager::DeleteObjectsByTag(eObjectTag tag, int maxCount)
{
	// 오브젝트 리스트를 돌면서 숙청할 쓰레기들을 쓰레기통에 넣는 과정
	vector<GameObject*> garbage;
	auto it = m_ObjectList.begin();
	for (it; it != m_ObjectList.end(); it++)
	{
		if ((*it)->GetTag() == tag)
		{
			m_ObjectList.erase(it);
			garbage.push_back(*it);
		}
		if (garbage.size() > maxCount)
		{
			break;
		}
	}

	// 쓰레기통 내부를 삭제하는 과정
	for (auto it : garbage)
	{
		delete it;
	}
}

GameObject* ObjectManager::FindObjectByName(eObjectName name)
{
	for (auto it : m_ObjectList)
	{
		if (it->GetName() == name)
		{
			return it;
		}
	}
}


ObjectManager::ObjectManager()
{

}

ObjectManager::~ObjectManager()
{
	// Range-based for
	for (auto it : m_ObjectList)
	{
		if (it != nullptr)
		{
			delete it;
		}
	}
}
