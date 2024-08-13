#include "CircleCollider.h"
#include "Transform.h";
#include "CollideInfoMap.h"
#include "Math.h"

CircleCollider::CircleCollider(const Transform& transform, int imageIndex)
	: Collider(transform, imageIndex), m_Radius(-1)
{
	//���⼭ Render���� �޾ƿ���, �̹��� ������ �޾ƿ;� ��.
	//Radius�� ����.
	m_Radius = (CollideInfoMap::GetInstance().GetWidthByImageIndex(imageIndex))/2.0f;
}

CircleCollider::~CircleCollider()
{

}

//Scale�� �� x���� �ݿ� ����. '��'�� ���ǿ� ���߾�� ��. (NO Ÿ��!)
void CircleCollider::UpdateCollider()
{
	Vec2 tmpPos = m_pTransform->GetPosition();
	m_CircleCollider.position = Math::ApplyTransform(tmpPos, *m_pTransform);
	m_CircleCollider.radius = m_Radius * m_pTransform->GetScale().x;
}

Vec2Circle CircleCollider::GetWorldCircle()
{
	return m_CircleCollider;
}
