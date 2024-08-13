#include "NoteButton.h"
#include "Debug.h"
#include "InputManager.h"
#include "MouseInputManager.h"
#include "Vec2.h"
#include "RenderSystem.h"
#include "Transform.h"

using namespace std;

NoteButton::NoteButton(eObjectTag tag, eObjectName name, Transform transform)
	: GameObject(tag, name, transform), temp(transform.GetPosition()),
	m_mouseClick(false)
{

}

NoteButton::~NoteButton()
{

}

void NoteButton::Update()
{
	m_pTransform->SetPosition(Camera::GeInstance().WorldToCameraPOINT_UI(temp));

	if (MouseInputManager::GetInstance().IsOnBoard(m_pTransform->m_Position, IMAGE_NOTE_BUTTON))
	{
		if (m_mouseClick == false && InputManager::GetInstance().IsKeyDown(VK_LMB))
		{
			m_mouseClick = true;
		}
		else if (m_mouseClick == true && InputManager::GetInstance().IsKeyDown(VK_LMB))
		{
			m_mouseClick = false;
		}
	}
}

void NoteButton::Render()
{
	RenderSystem::GetInstance().DrawSprite(m_imageIndex, m_pTransform->GetPosition().x, m_pTransform->GetPosition().y, this->GetPTransform());
	
	if (m_mouseClick == true)
	{
		RenderSystem::GetInstance().DrawSprite(IMAGE_NOTE_MAIN,
			//Camera::GeInstance().WorldToCameraPOINT(),
			960,
			540,
			this->GetPTransform());
	}
}
