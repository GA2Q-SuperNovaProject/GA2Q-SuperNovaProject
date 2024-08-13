#pragma once
#include <windows.h>
#include "GameObject.h"

class NoteMain : public GameObject
{
public:

	NoteMain(eObjectTag tag, eObjectName name, Transform transform);
	~NoteMain();

	void Update();
	void Render();

private:
	Vec2 temp;

};