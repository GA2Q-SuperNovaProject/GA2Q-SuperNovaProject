#pragma once
#include "GameObject.h"
#include "Transform.h"

class TWKObject4 : public GameObject
{
public:
	TWKObject4(eObjectTag tag, eObjectName name, Transform transform, int imageIndex);
	~TWKObject4();

	virtual void Update() override;
	virtual void Render() override;
};