#pragma once
#include <windows.h>
#include "GameObject.h"
#include "Camera.h"


class NoteButton : public GameObject
{
public:

	NoteButton(eObjectTag tag, eObjectName name, Transform transform);
	~NoteButton();

	virtual void Update() override;
	virtual void Render() override;

private:
	Vec2 temp; 
	Vec2 m_buttonlocation = Camera::GeInstance().WorldToCameraPOINT(Vec2(3200, 2800));

	bool m_mouseClick;
};