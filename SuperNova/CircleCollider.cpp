#include "CircleCollider.h"
#include "Transform.h";
#include "CollideInfoMap.h"
#include "Math.h"

CircleCollider::CircleCollider(const Transform& transform, int imageIndex)
	: Collider(transform, imageIndex), m_Radius(-1)
{
	//여기서 Render에서 받아오든, 이미지 정보를 받아와야 함.
	//Radius에 대해.
	m_Radius = (CollideInfoMap::GetInstance().GetWidthByImageIndex(imageIndex))/2.0f;
}

CircleCollider::~CircleCollider()
{

}

//Scale값 중 x값만 반영 가능. '원'의 정의에 맞추어야 함. (NO 타원!)
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
