#include "InputManager.h"
#include "Debug.h"


void InputManager::Update()
{
	// 모든 키값을 싹 훑어서 체크한다.
	HWND hWnd = GetFocus();
	if (nullptr != hWnd)
	{
		for (int i = 0; i < KEY_COUNT; i++)
		{
			m_PrevKeyState[i] = m_NowKeyState[i];
			m_NowKeyState[i] = GetAsyncKeyState(i);
		}
	}
}

// 이제 막 입력을 했을 때
bool InputManager::IsKeyDown(int keyCode)
{
	return (m_PrevKeyState[(int)keyCode] == 0) && (m_NowKeyState[(int)keyCode] & 0x8000);
}

// 계속 입력을 하고 있을 때
bool InputManager::IsKeyPress(int keyCode)
{
	return (m_PrevKeyState[(int)keyCode] & 0x8000) && (m_NowKeyState[(int)keyCode] & 0x8000);
}

// 입력이 끝날 때
bool InputManager::IsKeyUp(int keyCode)
{
	return (m_PrevKeyState[(int)keyCode] & 0x8000) && (m_NowKeyState[(int)keyCode] == 0);
}

// 입력이 없을 때
bool InputManager::IsKeyNone(int keyCode)
{
	return (m_PrevKeyState[(int)keyCode] == 0) && (m_NowKeyState[(int)keyCode] == 0);
}

InputManager::InputManager()
{
	
}

InputManager::~InputManager()
{

}
