#pragma once
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include "Vec2.h"
#include "Debug.h"
#include "Transform.h"
#include "EnumDefine.h"

// �� ���ø��� ������� �־���ұ�??
// ������Ÿ�ӿ� �����ϱ����ؼ�


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

	//��� ��. 
	void ReleaseObjectPool();

	T* BorrowFromObjectPool(eBulletType bulletType); //������Ʈ Ǯ���� �������� �ܰ�.
	void ReturnToObjectPool(T* object); //������Ʈ Ǯ�� ������Ʈ ����.

	//�Ƹ� �Ͼ �ó�����:
	//������ƮPool���� �ν��Ͻ��� �ҷ�����, �̸� ���� ����.
	//������ ��ȣ�ۿ��� �� ������, ReturnToObjectPool�� ����ؼ� �ڽ� �����ϴ� ���.

	//bool�� True�� ����� �� �ִٴ� ���̰�,
	//False�� �� �� ���ٴ� ��.
	std::map<T*, bool> m_BulletPoolMap;

private:
	ObjectPool();
	~ObjectPool();
	
	int poolSize; // ������Ʈ Ǯ�� ���� ������
	int poolCapacity = 0; // ������Ʈ Ǯ�� �ѵ�.

};

template <typename T>
ObjectPool<T>::ObjectPool()
{

}

template <typename T>
ObjectPool<T>::~ObjectPool()
{

}

//Initialize �ι� �ص� �ȴ�.
//�׳� �� 100�� ��������.
template <typename T>
void ObjectPool<T>::Initialize(eObjectTag tag, eObjectName name, int count)
{
	poolCapacity += count; //�̷��� �ؼ� Initialize �Ҽ��� �þ.

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

//������Ʈ Ǯ���� ��������. (�ϳ���)
//���ø��ε�, Bullet Ŭ���� �ܿ� �ٸ� �� ���� ���� ��.
template <typename T>
T* ObjectPool<T>::BorrowFromObjectPool(eBulletType bulletType)
{
	//���: �ϴ��� -> Pool���� ���ͼ� true�� �ֵ��� ã��.
	//�� �߿���, ���� ��� �ֵ��� �� false���?
	//�ε��� �߿��� ���� ������ �ָ� ������ True�� �ٲ㼭 �ݿ�����.
	T* toReturnObject = nullptr;
	bool isAllFalse = true;
	//for (auto it : m_BulletPoolMap)
	//{
	//	//���� ���� ��� �ֵ��� �� False? => �׷��� 
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






