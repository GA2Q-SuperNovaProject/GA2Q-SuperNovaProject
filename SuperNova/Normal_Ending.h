#pragma once
#include "GameObject.h"
#include "Transform.h"

class Normal_Ending : public GameObject
{
public:
	Normal_Ending(eObjectTag tag, eObjectName name, Transform transform);
	~Normal_Ending();

	virtual void Update() override;
	virtual void Render() override;

private:
	bool m_isClick;
	int m_KeyCount;


	void Sortation();
	void ClickEvent();
};

