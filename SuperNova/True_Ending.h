#pragma once
#include "GameObject.h"
#include "Transform.h"

class True_Ending : public GameObject
{
public:
	True_Ending(eObjectTag tag, eObjectName name, Transform transform);
	~True_Ending();

	virtual void Update() override;
	virtual void Render() override;

private:
	bool m_isClick;
	int m_KeyCount;

	void Sortation();
	void ClickEvent();
};

