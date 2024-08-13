#include "BoxCollider.h"
#include "Transform.h";
#include "Math.h"
#include "CollideInfoMap.h"	
BoxCollider::BoxCollider(const Transform& transform, int imageIndex)
	: Collider(transform, imageIndex), m_Height(-1), m_Width(-1)
{
	//���⼭ Render���� �޾ƿ���, �̹��� ������ �޾ƿ;� ��.
	//Width, Height�� ����.
	m_Width = CollideInfoMap::GetInstance().GetWidthByImageIndex(imageIndex);
	m_Height = CollideInfoMap::GetInstance().GetHeightByImageIndex(imageIndex);
}

BoxCollider::~BoxCollider()
{

}

void BoxCollider::UpdateCollider()
{
	//�� �κп� ���� �����̽��� ��ȯ�ϴ� ������ �����Ѵ�. [TW]
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
	//�� UpdateCollider���� ���� ���� ��ȯ�� ���̴�. [TW]
	return m_RectCollider;
}

//ChangeScene���ִ� �͵�...Loop ������ ��?
