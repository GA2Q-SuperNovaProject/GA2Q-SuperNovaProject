#pragma once
#include "Collider.h"
#include "StructDefine.h"

/// [TW] BoxCollider, 직사각형 콜라이더.

class BoxCollider : public Collider
{
public:
	BoxCollider(const Transform& transform, int imageIndex);
	virtual ~BoxCollider();

	virtual void UpdateCollider() override;

	float GetWidth() const { return m_Width; }
	void SetWidth(float val) { m_Width = val; }

	float GetHeight() const { return m_Height; }
	void SetHeight(float val) { m_Height = val; }

	//Box Collider 고유, 다운캐스팅. 필요.
	Vec2Rect GetWorldRect(); //Local Space -> WorldSpace, 반환.

private:
	float m_Width; //[TW] 받아와야 한다..
	float m_Height;

	Vec2Rect m_RectCollider;
};

