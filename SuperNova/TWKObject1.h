#pragma once
#include "GameObject.h"
#include "Transform.h"

class TWKObject1 : public GameObject
{
public:
	TWKObject1(eObjectTag tag, eObjectName name, Transform transform, int imageIndex);
	~TWKObject1();

	virtual void Start() override;
	virtual void Update() override;
	virtual void Render() override;

private:
	GameObject* twkTwo;
};
