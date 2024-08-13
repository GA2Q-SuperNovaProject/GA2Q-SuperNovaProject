#pragma once
#include "GameObject.h"
#include "Transform.h"

class Background : public GameObject
{
public:
	Background(eObjectTag tag, eObjectName name, Transform transform);
	~Background();

	virtual void Update() override;
	virtual void Render() override;

private:
	Vec2 m_beginPos;
	bool m_moving;
	
	void Sortation();
};

