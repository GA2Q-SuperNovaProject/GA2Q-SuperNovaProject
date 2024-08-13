#pragma once
#include "Collider.h"
#include "StructDefine.h"

/// [TW] BoxCollider, ���簢�� �ݶ��̴�.

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

	//Box Collider ����, �ٿ�ĳ����. �ʿ�.
	Vec2Rect GetWorldRect(); //Local Space -> WorldSpace, ��ȯ.

private:
	float m_Width; //[TW] �޾ƿ;� �Ѵ�..
	float m_Height;

	Vec2Rect m_RectCollider;
};

