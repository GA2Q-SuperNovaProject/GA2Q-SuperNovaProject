#pragma once
#include <windows.h>
#include "KeyDefine.h"
#include "StructDefine.h"
#include "Vec2.h"
const int KEY_COUNT = 0xFF;

/// <summary>
/// 인풋값을 받아오는 매니저
/// 얘는 모든 키값을 받아온다. 다른거 뭐 할생각 하지마라
/// 완벽한거다. 너가 키를 입력받아서 뭔갈 하려고 한다면
/// 얘는 건들지마라 얘를 이용하는거다 이 멍청아...
/// 2023-02-08 [nadong]
/// </summary>
class InputManager
{
public:
	static InputManager& GetInstance()
	{
		static InputManager inst;
		return inst;
	}

public:
	void Update();
	bool IsKeyDown(int keyCode);
	bool IsKeyPress(int keyCode);
	bool IsKeyUp(int keyCode);
	bool IsKeyNone(int keyCode);


private:
	InputManager();
	~InputManager();

	int m_PrevKeyState[KEY_COUNT] = { 0, };
	int m_NowKeyState[KEY_COUNT] = { 0, };
};

