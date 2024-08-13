#pragma once
#include <windows.h>
#include "Vec2.h"
#include "CollideInfoMap.h"
#include "StructDefine.h"


class MouseInputManager
{
public:
	static MouseInputManager& GetInstance()
	{
		static MouseInputManager inst;
		return inst;
	}


	void Update();
	// void Click();
	
	bool IsOnBoard(Vec2 position, int imageIndex);
	bool IsOnBoardRect(Vec2 position, Rect2D rect);
	
	bool IsOnBoard(Vec2 position, Vec2 starpos); //������ ���ڸ� �δ� ��



	Vec2 GetPos() const {return m_Pos;}

private:
	MouseInputManager();
	~MouseInputManager();

	// �츮�� ������ Vector2 �ε� �̰ɷ� x,y ��ǥ���� �ް� �;����� �ȵȴ�.
	// �¿��̰� ���� ����� ����� ������ ���� ���ε�...�� ����� ���İ�!
	Vec2 m_Pos;

	// GetCursorPos�� �������� POINT ����ü
	POINT m_Pt;
};

