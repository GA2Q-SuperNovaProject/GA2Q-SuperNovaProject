#pragma once
#include "GameObject.h"
#include "Transform.h"
#include "StructDefine.h"

class MainUI : public GameObject
{
public:
	MainUI(eObjectTag tag, eObjectName name, Transform transform);
	~MainUI();

	virtual void Start();
	virtual void Update() override;
	virtual void Render() override;

private:
	int m_changedImageIndex;
	bool m_isClick;
	static bool m_ShowCreditPopup;
	bool m_isPop;

	void Sortation();
	void ClickEvent();

	GameObject* playButton;
	GameObject* optionButton;
	GameObject* creditButton;

	Rect2D creditScreenRect =
	{
		610,
		190,
		1310,
		890
	};
};

