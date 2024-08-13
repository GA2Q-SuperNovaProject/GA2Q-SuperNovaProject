#include "BoxCollider.h"
#include "Transform.h";
#include "Math.h"
#include "CollideInfoMap.h"	
BoxCollider::BoxCollider(const Transform& transform, int imageIndex)
	: Collider(transform, imageIndex), m_Height(-1), m_Width(-1)
{
	//여기서 Render에서 받아오든, 이미지 정보를 받아와야 함.
	//Width, Height에 대해.
	m_Width = CollideInfoMap::GetInstance().GetWidthByImageIndex(imageIndex);
	m_Height = CollideInfoMap::GetInstance().GetHeightByImageIndex(imageIndex);
}

BoxCollider::~BoxCollider()
{

}

void BoxCollider::UpdateCollider()
{
	//이 부분에 월드 스페이스로 반환하는 연산을 시행한다. [TW]
	Vec2 tmpPos = m_pTransform->GetPosition();
	Rect2D tmpRect = { tmpPos.x - (m_Width / 2.0f), tmpPos.y - (m_Height / 2.0f),
					   tmpPos.x + (m_Width / 2.0f), tmpPos.y + (m_Height / 2.0f) };
	m_RectCollider.topLeft = Math::ApplyTransform(tmpRect.GetTL(), *m_pTransform);
	m_RectCollider.topRight = Math::ApplyTransform(tmpRect.GetTR(), *m_pTransform);
	m_RectCollider.bottomLeft = Math::ApplyTransform(tmpRect.GetBL(), *m_pTransform);
	m_RectCollider.bottomRight = Math::ApplyTransform(tmpRect.GetBR(), *m_pTransform);
}

Vec2Rect BoxCollider::GetWorldRect()
{
	//위 UpdateCollider에서 계산된 값을 반환할 뿐이다. [TW]
	return m_RectCollider;
}

//ChangeScene해주는 것도...Loop 끝났을 때?
