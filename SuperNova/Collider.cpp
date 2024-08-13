#include "Collider.h"
#include "Transform.h";

Collider::Collider(const Transform& transform, int imageIndex) :
	otherCollidedObject(nullptr)
{
	m_pTransform = &transform; //주소 자체 할당.
	m_imageIndex = imageIndex;

	//m_FixedQueueOfTwo.Enqueue(false);
	//m_FixedQueueOfTwo.Enqueue(false); //NULL 오류를 나지 않게 하기 위해.
	//이제 ContentOfIndex(0), ContentOfIndex(1) 로 각각
	//			현재				과거					측정 가능.
}

Collider::~Collider()
{

}

void Collider::SetOtherCollidedObject(GameObject* other)
{
	otherCollidedObject = other;
}

GameObject* Collider::GetOtherCollidedObject()
{
	return otherCollidedObject;
}
