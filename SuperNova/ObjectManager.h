#pragma once
#include <vector>
#include <string>
#include "Vec2.h"
#include "EnumDefine.h"
#include "Transform.h"

/// <summary>
/// 오브젝트들을 분류하는 오브젝트매니저
/// GameObject 와 상속관계가 아니다. 생각할 때 주의할 것.
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

	///[TW] 현재 ObjectManager는 하위 객체를 만들어낼 수 있으나, 이에는 추가적인 매개변수가 들어가지 못한다.
	/// (템플릿 들어가면 해결되는 문제) => 여튼, 추후에 고려할 문제. 
	/// (Enum 추가, Else-If 여기서 추가하는 것 잊지 않기!
	GameObject* CreateObject(eObjectTag objType, eObjectName name, Transform transform);

	void DeleteObjectByName(eObjectName name);
	void DeleteObjectsByTag(eObjectTag tag, int maxCount = 100);

	//이름을 넣으면 오브젝트를 찾아 온다
	GameObject* FindObjectByName(eObjectName name);

private:
	ObjectManager();
	~ObjectManager();

	// 메모리 관리용 + 씬사이 오브젝트 이동용
	std::vector<GameObject*> m_ObjectList;
};

