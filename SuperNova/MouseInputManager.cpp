#include "MouseInputManager.h"
#include "InputManager.h"
#include "StructDefine.h"
#include "Debug.h"
#include "RenderSystem.h"

// ���콺�� �ǽð� ��ǥ�� �޾Ƽ� ������Ʈ �Ѵ�.
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
	// �̹��� �ε����� �̿��ؼ� width�� height�� �޴´�.
	// �׸� ������ ���� �� �ִ�.
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
// 	// ���콺�� Ŭ�� ���¿� ���� ������ ���ҵ��� �ٸ��� �ؾ��Ѵ�.
// 	// ��ǥ�� ������ͼ� �ؾ��ϴµ� �� �κ��� ��� �ұ�
// 	
// 	// ���콺 ������ Ŭ��,���� �������� ���
// 	if (InputManager::GetInstance().IsKeyDown(VK_LBUTTON)
// 		|| InputManager::GetInstance().IsKeyPress(VK_LBUTTON))
// 	{
// 		// ������Ʈ�� ���� ���� ���
// 		// ������Ʈ�� ��ǥ���� ���콺�� ��ǥ���� ���� �������� ���� ������?
// 
// 		// UI�� Ŭ�� ���� ���
// 		// GameStart�� ���� ��ư�� �ܹ߼� Ŭ������ �����ϴϱ� �װ� �� ��� �ϸ�ɱ�?
// 	}
// 
// 	// ���콺 �������� Ŭ��, ���� �������� ���
// 	if (InputManager::GetInstance().IsKeyDown(VK_RBUTTON)
// 		|| InputManager::GetInstance().IsKeyPress(VK_RBUTTON))
// 	{
// 
// 	}
// }
