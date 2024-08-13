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
	
	bool IsOnBoard(Vec2 position, Vec2 starpos); //조각상 별자리 두는 용



	Vec2 GetPos() const {return m_Pos;}

private:
	MouseInputManager();
	~MouseInputManager();

	// 우리가 만들어둔 Vector2 인데 이걸로 x,y 좌표값을 받고 싶었으나 안된다.
	// 태욱이가 오면 물어보자 방법은 언제나 있을 것인데...그 방법이 뭐냐고!
	Vec2 m_Pos;

	// GetCursorPos를 쓰기위한 POINT 구조체
	POINT m_Pt;
};

