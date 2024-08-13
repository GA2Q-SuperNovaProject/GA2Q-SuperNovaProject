#include "ObjectManager.h"
#include "GameObject.h"
#include "Camera.h"

///[TW] ����ٰ� ������ ��� �߰��Ǵ� ������Ʈ���� �����ؼ� ���� ��.
#include "ObjectHeaderIncludes.h"

using namespace std;

GameObject* ObjectManager::CreateObject(eObjectTag tag, eObjectName name, Transform transform)
{
	///[TW] => ����μ��� �̷��� �ϳ�, �߰��� ����ȭ�ؼ� �߰� Ŭ������ ������ �� ���� �ִ�.
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

		case eObjectTag::BULLET: //���˺��� ���˺� ����
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


// �����±��� �γ� �̻��� ������.
void ObjectManager::DeleteObjectsByTag(eObjectTag tag, int maxCount)
{
	// ������Ʈ ����Ʈ�� ���鼭 ��û�� ��������� �������뿡 �ִ� ����
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

	// �������� ���θ� �����ϴ� ����
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
