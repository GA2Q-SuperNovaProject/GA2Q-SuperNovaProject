#pragma once
#include <vector>
#include <string>
#include "Vec2.h"
#include "EnumDefine.h"
#include "Transform.h"

/// <summary>
/// ������Ʈ���� �з��ϴ� ������Ʈ�Ŵ���
/// GameObject �� ��Ӱ��谡 �ƴϴ�. ������ �� ������ ��.
/// 2023.02.08 [nadong]
/// </summary>

class GameObject;

class ObjectManager
{
public:
	static ObjectManager& GetInstance()
	{
		static ObjectManager inst;
		return inst;
	}

	///[TW] ���� ObjectManager�� ���� ��ü�� ���� �� ������, �̿��� �߰����� �Ű������� ���� ���Ѵ�.
	/// (���ø� ���� �ذ�Ǵ� ����) => ��ư, ���Ŀ� ����� ����. 
	/// (Enum �߰�, Else-If ���⼭ �߰��ϴ� �� ���� �ʱ�!
	GameObject* CreateObject(eObjectTag objType, eObjectName name, Transform transform);

	void DeleteObjectByName(eObjectName name);
	void DeleteObjectsByTag(eObjectTag tag, int maxCount = 100);

	//�̸��� ������ ������Ʈ�� ã�� �´�
	GameObject* FindObjectByName(eObjectName name);

private:
	ObjectManager();
	~ObjectManager();

	// �޸� ������ + ������ ������Ʈ �̵���
	std::vector<GameObject*> m_ObjectList;
};

