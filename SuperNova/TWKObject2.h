#pragma once
#include "GameObject.h"
#include "Transform.h"

class TWKObject2 : public GameObject
{
public:
	TWKObject2(eObjectTag tag, eObjectName name, Transform transform, int imageIndex);
	~TWKObject2();

	virtual void Update() override;
	virtual void Render() override;

private:
	bool yetToStart = true;
	GameObject* twkOne;
};
