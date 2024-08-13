#include "StarPiece2.h"
#include "Debug.h"
#include "Camera.h"
#include "InputManager.h"
#include "MouseInputManager.h"
#include "Vec2.h"
#include "RenderSystem.h"
#include "Transform.h"

using namespace std;

StarPiece2::StarPiece2(eObjectTag tag, eObjectName name, Transform transform)
	: GameObject(tag, name, transform), temp(transform.GetPosition())
{

}

StarPiece2::~StarPiece2()
{

}

void StarPiece2::Update()
{
	m_pTransform->SetPosition(Camera::GeInstance().WorldToCameraPOINT_UI(temp));
	if (MouseInputManager::GetInstance().IsOnBoard(m_pTransform->m_Position, IMAGE_STAR_PIECE2))
	{
		//InputManager::GetInstance().IsKeyPress(VK_LMB) || �� ������ �־����� �ʾƵ� �� �־��ְ� �Ǹ� �ٸ� �͵��� ���� �ٴ� ������
		if (m_mouseClick == false && InputManager::GetInstance().IsKeyDown(VK_LMB))
		{
			m_mouseClick = true;
		}
	}
	if (m_mouseClick == true && InputManager::GetInstance().IsKeyUp(VK_LMB))
	{
		m_mouseClick = false;
	}

	if (m_mouseClick == true)
	{
		mouse = MouseInputManager::GetInstance().GetPos();
		m_pTransform->m_Position.x = mouse.x;
		m_pTransform->m_Position.y = mouse.y;
		//Debug::Trace(" ", m_pTransform->m_Position.x, m_pTransform->m_Position.y);
	}
}

void StarPiece2::Render()
{
	RenderSystem::GetInstance().DrawSprite(m_imageIndex, m_pTransform->GetPosition().x, m_pTransform->GetPosition().y, this->GetPTransform());

	if (m_mouseClick == true)
	{
		RenderSystem::GetInstance().DrawSprite(m_imageIndex, mouse.x, mouse.y, this->GetPTransform());
	}

}
