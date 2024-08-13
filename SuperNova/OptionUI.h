#pragma once
#include "GameObject.h"
#include "Transform.h"


class OptionUI : public GameObject
{
public:
	OptionUI(eObjectTag tag, eObjectName name, Transform transform);
	~OptionUI();

	virtual void Update() override;
	virtual void Render() override;

private:
	bool m_isClick;

	void Sortation();
	void ClickEvent();
	void VolumeEvent();
};

