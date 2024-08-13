#pragma once
#include <windows.h>
#include "GameObject.h"

class BoosterArrow : public GameObject
{
public:

	BoosterArrow(eObjectTag tag, eObjectName name, Transform transform);
	~BoosterArrow();

	void Update();
	void Render();

private:
	Vec2 temp;

};