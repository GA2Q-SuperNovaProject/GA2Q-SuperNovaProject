#pragma once
#include <windows.h>
#include "GameObject.h"

class StarPiece3 : public GameObject
{
public:

	StarPiece3(eObjectTag tag, eObjectName name, Transform transform);
	~StarPiece3();

	void Update();
	void Render();

private:
	Vec2 temp;
	Vec2 mouse;

	bool m_mouseClick;
};