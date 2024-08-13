#include "StarPiece3.h"
#include "Debug.h"
#include "Camera.h"
#include "InputManager.h"
#include "MouseInputManager.h"
#include "Vec2.h"
#include "RenderSystem.h"
#include "Transform.h"

using namespace std;

StarPiece3::StarPiece3(eObjectTag tag, eObjectName name, Transform transform)
	: GameObject(tag, name, transform), temp(transform.GetPosition())
{

}

StarPiece3::~StarPiece3()
{

}

void StarPiece3::Update()
{
	m_pTransform->SetPosition(Camera::GeInstance().WorldToCameraPOINT_UI(temp));

	if (MouseInputManager::GetInstance().IsOnBoard(m_pTransform->m_Position, m_imageIndex))
	{
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

		/*m_pTransform->m_Position.x = mouse.x;
		m_pTransform->m_Position.y = mouse.y;*/
		//Debug::Trace(" ", m_pTransform->m_Position.x, m_pTransform->m_Position.y);
	}
}

void StarPiece3::Render()
{
	RenderSystem::GetInstance().DrawSprite(m_imageIndex, m_pTransform->GetPosition().x, m_pTransform->GetPosition().y, this->GetPTransform());

	if (m_mouseClick == true)
	{
		RenderSystem::GetInstance().DrawSprite(m_imageIndex, mouse.x, mouse.y);
	}

}

