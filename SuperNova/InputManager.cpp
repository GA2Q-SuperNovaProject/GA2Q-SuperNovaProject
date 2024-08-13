#include "InputManager.h"
#include "Debug.h"


void InputManager::Update()
{
	// ��� Ű���� �� �Ⱦ üũ�Ѵ�.
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

// ���� �� �Է��� ���� ��
bool InputManager::IsKeyDown(int keyCode)
{
	return (m_PrevKeyState[(int)keyCode] == 0) && (m_NowKeyState[(int)keyCode] & 0x8000);
}

// ��� �Է��� �ϰ� ���� ��
bool InputManager::IsKeyPress(int keyCode)
{
	return (m_PrevKeyState[(int)keyCode] & 0x8000) && (m_NowKeyState[(int)keyCode] & 0x8000);
}

// �Է��� ���� ��
bool InputManager::IsKeyUp(int keyCode)
{
	return (m_PrevKeyState[(int)keyCode] & 0x8000) && (m_NowKeyState[(int)keyCode] == 0);
}

// �Է��� ���� ��
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
