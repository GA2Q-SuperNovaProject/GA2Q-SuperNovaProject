#pragma once
#include <windows.h>
#include "GameObject.h"

class StarPiece1 : public GameObject
{
public:

	StarPiece1(eObjectTag tag, eObjectName name, Transform transform);
	~StarPiece1();

	virtual void Start() override;

	virtual void Update() override;
	virtual void Render() override;

	bool PlayerTouch(); // �÷��̾�� �ε������� üũ�ϴ� �Լ�
private:
	Vec2 temp;
	Vec2 mouse;

	bool m_mouseClick;
};