#pragma once
#include <windows.h>
#include "GameObject.h"

class StarPiece2 : public GameObject
{
public:

	StarPiece2(eObjectTag tag, eObjectName name, Transform transform);
	~StarPiece2();

	void Update();
	void Render();

private:
	Vec2 temp;
	Vec2 mouse;

	bool m_mouseClick;
};