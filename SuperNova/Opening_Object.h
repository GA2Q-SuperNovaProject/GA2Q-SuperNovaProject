#pragma once
#include "GameObject.h"
#include "Transform.h"

class Opening_Object : public GameObject
{
public:
	Opening_Object(eObjectTag tag, eObjectName name, Transform transform);
	~Opening_Object();

	virtual void Update() override;
	virtual void Render() override;

private:
	bool m_isClick;
	int m_KeyCount;

	void Sortation();
	void ClickEvent();
};

