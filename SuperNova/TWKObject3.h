#pragma once
#include "GameObject.h"
#include "Transform.h"

class TWKObject3 : public GameObject
{
public:
	TWKObject3(eObjectTag tag, eObjectName name, Transform transform, int imageIndex);
	~TWKObject3();

	virtual void Update() override;
	virtual void Render() override;
};