#include "MouseInputManager.h"
#include "InputManager.h"
#include "StructDefine.h"
#include "Debug.h"
#include "RenderSystem.h"

// 마우스의 실시간 좌표를 받아서 업데이트 한다.
void MouseInputManager::Update()
{
	HWND hWnd = GetFocus();
	if (nullptr != hWnd)
	{
		GetCursorPos(&m_Pt);
		ScreenToClient(hWnd, &m_Pt);
		m_Pos.x = m_Pt.x;
		m_Pos.y = m_Pt.y;
		//Debug::Trace("Mouse", m_Pos.x, m_Pos.y);
	}
}

bool MouseInputManager::IsOnBoard(Vec2 position, int imageIndex)
{
	float width = CollideInfoMap::GetInstance().GetWidthByImageIndex(imageIndex);
	float height = CollideInfoMap::GetInstance().GetHeightByImageIndex(imageIndex);
	Rect2D rect = { position.x - width / 2.0f,
		position.y - height / 2.0f,
		position.x + width / 2.0f,
		position.y + height / 2.0f
	};

	if (m_Pos.x >= rect.left && m_Pos.x <= rect.right
		&& m_Pos.y >= rect.top && m_Pos.y <= rect.bottom)
	{
		return true;
	}
	else
	{
		return false;
	}
	// 이미지 인덱스를 이용해서 width와 height을 받는다.
	// 네모난 영역을 만들 수 있다.
}

bool MouseInputManager::IsOnBoard(Vec2 position, Vec2 starpos)
{
	return false;
}



bool MouseInputManager::IsOnBoardRect(Vec2 position, Rect2D rect)
{
	if (m_Pos.x >= rect.left && m_Pos.x <= rect.right
		&& m_Pos.y >= rect.top && m_Pos.y <= rect.bottom)
	{
		return true;
	}
	else
	{
		return false;
	}
}

MouseInputManager::MouseInputManager()
{

}

MouseInputManager::~MouseInputManager()
{

}

// void MouseInputManager::Click()
// {
// 	// 마우스의 클릭 상태에 따라 각각의 역할들을 다르게 해야한다.
// 	// 좌표를 가지고와서 해야하는데 그 부분을 어떻게 할까
// 	
// 	// 마우스 왼쪽을 클릭,유지 했을때의 경우
// 	if (InputManager::GetInstance().IsKeyDown(VK_LBUTTON)
// 		|| InputManager::GetInstance().IsKeyPress(VK_LBUTTON))
// 	{
// 		// 오브젝트를 눌린 것일 경우
// 		// 오브젝트의 좌표값이 마우스의 좌표값을 따라 움직여야 하지 않을까?
// 
// 		// UI를 클릭 했을 경우
// 		// GameStart와 같은 버튼은 단발성 클릭으로 가능하니깐 그건 뭐 어떻게 하면될까?
// 	}
// 
// 	// 마우스 오른쪽을 클릭, 유지 했을때의 경우
// 	if (InputManager::GetInstance().IsKeyDown(VK_RBUTTON)
// 		|| InputManager::GetInstance().IsKeyPress(VK_RBUTTON))
// 	{
// 
// 	}
// }
