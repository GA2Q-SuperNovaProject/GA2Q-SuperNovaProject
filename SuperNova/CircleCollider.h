#pragma once
#include "Collider.h"
#include "StructDefine.h"

/// [TW] CircleCollider, �� �ݶ��̴�. Ÿ������ ��ȯ�ǰ� �������� Ȱ���ϸ� ���� �ȵ˴ϴ�.

class CircleCollider : public Collider
{
public:
	CircleCollider(const Transform& transform, int imageIndex);
	virtual ~CircleCollider();

	virtual void UpdateCollider() override;

	float GetRadius() const { return m_Radius; }
	void SetRadius(float val) { m_Radius = val; }

	Vec2Circle GetWorldCircle();

private:
	float m_Radius;
	Vec2Circle m_CircleCollider;
	
};

