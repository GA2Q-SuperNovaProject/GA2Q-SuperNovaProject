#pragma once
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include "Vec2.h"
#include "Debug.h"
#include "Transform.h"
#include "EnumDefine.h"

// 왜 템플릿은 헤더에만 있어야할까??
// 컴파일타임에 인지하기위해서


template <typename T>
class ObjectPool
{
public:
	static ObjectPool& GetInstance()
	{
		static ObjectPool inst;
		return inst;
	}

	void Initialize(eObjectTag tag, eObjectName name,int count);

	//없어도 됨. 
	void ReleaseObjectPool();

	T* BorrowFromObjectPool(eBulletType bulletType); //오브젝트 풀에서 가져오는 단계.
	void ReturnToObjectPool(T* object); //오브젝트 풀로 오브젝트 리턴.

	//아마 일어날 시나리오:
	//오브젝트Pool에서 인스턴스를 불러오고, 이를 통해 접근.
	//각각의 상호작용을 한 다음에, ReturnToObjectPool을 사용해서 자신 리턴하는 방식.

	//bool이 True면 사용할 수 있다는 뜻이고,
	//False면 쓸 수 없다는 뜻.
	std::map<T*, bool> m_BulletPoolMap;

private:
	ObjectPool();
	~ObjectPool();
	
	int poolSize; // 오브젝트 풀에 남은 사이즈
	int poolCapacity = 0; // 오브젝트 풀의 한도.

};

template <typename T>
ObjectPool<T>::ObjectPool()
{

}

template <typename T>
ObjectPool<T>::~ObjectPool()
{

}

//Initialize 두번 해도 된다.
//그냥 한 100개 만들어놓자.
template <typename T>
void ObjectPool<T>::Initialize(eObjectTag tag, eObjectName name, int count)
{
	poolCapacity += count; //이렇게 해서 Initialize 할수록 늘어남.

	for (size_t i = 0; i < count; i++)
	{
		T* t = new T(tag, name,
			Transform(Vec2(0, 0), 0, Vec2(1, 1)));
		if (name == eObjectName::SHOOTHING_STAR)
		{
			t->PutCollider(eColType::BOX, IMAGE_SHOOTING_STAR);
			t->SetColState(true);
		}
		else if (name == eObjectName::SHOOTHING_STAR_TAIL)
		{
			t->PutCollider(eColType::BOX, IMAGE_SHOOTING_STAR_TAIL);
			t->SetColState(true);
		}
		else
		{
			t->PutCollider(eColType::BOX, IMAGE_SATELLITE);
			t->SetColState(true);
		}
		m_BulletPoolMap.insert(std::pair<T*,bool>(t,true));
	}
}

//오브젝트 풀에서 빌려오기. (하나씩)
//템플릿인데, Bullet 클래스 외에 다른 걸 쓰면 뻑날 것.
template <typename T>
T* ObjectPool<T>::BorrowFromObjectPool(eBulletType bulletType)
{
	//방식: 일단은 -> Pool에서 들어와서 true인 애들을 찾음.
	//그 중에서, 만약 모든 애들이 다 false라면?
	//인덱스 중에서 가장 먼저인 애를 강제로 True로 바꿔서 반영해줌.
	T* toReturnObject = nullptr;
	bool isAllFalse = true;
	//for (auto it : m_BulletPoolMap)
	//{
	//	//만약 쓰는 모든 애들이 다 False? => 그러면 
	//	
	//	
	//}
	auto it = m_BulletPoolMap.begin();
	for (it; it != m_BulletPoolMap.end(); it++)
	{
		if (it->second == true)
		{
			it->second = false;
			it->second = false;
			isAllFalse = false;
			toReturnObject = it->first;
			break;
		}
	}

	if (isAllFalse)
	{
		auto tmp = m_BulletPoolMap.begin();
		toReturnObject = tmp->first;
	}

	if (bulletType == eBulletType::LINEAR)
	{
		toReturnObject->SetName(eObjectName::SHOOTHING_STAR);
	}
	else if (bulletType == eBulletType::FOLLOW)
	{
		toReturnObject->SetName(eObjectName::SATELLITE);
	}
	else
	{
		toReturnObject->SetName(eObjectName::SHOOTHING_STAR_TAIL);
	}

	return toReturnObject;
}

template <typename T>
void ObjectPool<T>::ReturnToObjectPool(T* object)
{
	auto it = m_BulletPoolMap.begin();
	for (it; it != m_BulletPoolMap.end(); it++)
	{
		if (it->first == object)
		{
			m_BulletPoolMap.at(it->first) = true;
			//it->second = true;
		}
	}
}

template <typename T>
void ObjectPool<T>::ReleaseObjectPool() //
{
	delete m_BulletPoolMap;
}

//






