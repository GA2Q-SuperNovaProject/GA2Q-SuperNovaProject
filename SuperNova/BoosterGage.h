#pragma once
#include <windows.h>
#include "GameObject.h"

class BoosterGage : public GameObject
{
public:

	BoosterGage(eObjectTag tag, eObjectName name, Transform transform);
	~BoosterGage();

	void Update();
	void Render();

private:
	Vec2 temp;

	int m_boostcount;
	


};