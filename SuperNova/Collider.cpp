#include "Collider.h"
#include "Transform.h";

Collider::Collider(const Transform& transform, int imageIndex) :
	otherCollidedObject(nullptr)
{
	m_pTransform = &transform; //�ּ� ��ü �Ҵ�.
	m_imageIndex = imageIndex;

	//m_FixedQueueOfTwo.Enqueue(false);
	//m_FixedQueueOfTwo.Enqueue(false); //NULL ������ ���� �ʰ� �ϱ� ����.
	//���� ContentOfIndex(0), ContentOfIndex(1) �� ����
	//			����				����					���� ����.
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
