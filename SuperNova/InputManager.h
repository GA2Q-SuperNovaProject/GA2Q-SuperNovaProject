#pragma once
#include <windows.h>
#include "KeyDefine.h"
#include "StructDefine.h"
#include "Vec2.h"
const int KEY_COUNT = 0xFF;

/// <summary>
/// ��ǲ���� �޾ƿ��� �Ŵ���
/// ��� ��� Ű���� �޾ƿ´�. �ٸ��� �� �һ��� ��������
/// �Ϻ��ѰŴ�. �ʰ� Ű�� �Է¹޾Ƽ� ���� �Ϸ��� �Ѵٸ�
/// ��� �ǵ������� �긦 �̿��ϴ°Ŵ� �� ��û��...
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

