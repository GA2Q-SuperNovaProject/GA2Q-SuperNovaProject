#pragma once
#include "Collider.h"
#include "StructDefine.h"

/// [TW] CircleCollider, 원 콜라이더. 타원으로 변환되게 스케일을 활용하면 측정 안됩니다.

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

