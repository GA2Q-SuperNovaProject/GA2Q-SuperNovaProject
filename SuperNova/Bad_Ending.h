#pragma once
#include "GameObject.h"
#include "Transform.h"
#include "StructDefine.h"

class Bad_Ending : public GameObject
{
public:
	Bad_Ending(eObjectTag tag, eObjectName name, Transform transform);
	~Bad_Ending();

	virtual void Update() override;
	virtual void Render() override;

private:
	bool m_isClick;
	int m_KeyCount;

	bool m_isMain = false;
	bool m_isRetry = false;

	void Sortation();
	void ClickEvent();

	void GameOver();

	Rect2D main;
	Rect2D retry;

	// Rect2D main =
	// {
	// 	600,
	// 	360,
	// 	1320,
	// 	530
	// };
	// 
	// Rect2D retry =
	// {
	// 	600,
	// 	550,
	// 	1320,
	// 	720
	// };
};

