#pragma once
#include "GameObject.h"
#include "Transform.h"

class WhaleStatue : public GameObject
{
public:
	WhaleStatue(eObjectTag tag, eObjectName name, Transform transform);
	~WhaleStatue();

	virtual void Start() override;

	virtual void Update() override;
	virtual void Render() override;


private:
	Vec2 temp;

	GameObject* m_starpiece1;
	GameObject* m_starpiece2;
	GameObject* m_starpiece3;

	//Rect2D starPos1;
	//Rect2D starPos2;
	//Rect2D starPos3;
	//Rect2D starPos4;
	//Rect2D starPos5;
};

