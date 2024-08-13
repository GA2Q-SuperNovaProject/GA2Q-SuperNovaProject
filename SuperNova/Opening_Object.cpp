#include "Opening_Object.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "MouseInputManager.h"
#include "SoundManager.h"
#include "RenderSystem.h"
#include "Scene.h"
#include "Debug.h"

Opening_Object::Opening_Object(eObjectTag tag, eObjectName name, Transform transform)
	: GameObject(tag, name, transform), m_isClick(false), m_KeyCount(1)
{
	Sortation();
}

Opening_Object::~Opening_Object()
{

}

void Opening_Object::Update()
{
	ClickEvent();
	
}

void Opening_Object::Render()
{
		switch (m_KeyCount)
		{
			case 1:
				if (m_name == eObjectName::OPENING1)
				{
					m_imageIndex = IMAGE_OPENING_SCENE1;
					RenderSystem::GetInstance().DrawSprite(m_imageIndex, m_pTransform->GetPosition().x, m_pTransform->GetPosition().y, this->GetPTransform());
				}
				if (m_name == eObjectName::OPENING_LINE1)
				{
					m_imageIndex = IMAGE_OPENING_LINE1;
					RenderSystem::GetInstance().DrawSprite(m_imageIndex, m_pTransform->GetPosition().x, m_pTransform->GetPosition().y, this->GetPTransform());
				}
				break;

			case 2:
				if (m_name == eObjectName::OPENING2)
				{
					m_imageIndex = IMAGE_OPENING_SCENE2;
					RenderSystem::GetInstance().DrawSprite(m_imageIndex, m_pTransform->GetPosition().x, m_pTransform->GetPosition().y, this->GetPTransform());
				}
				if (m_name == eObjectName::OPENING_LINE2)
				{
					m_imageIndex = IMAGE_OPENING_LINE2;
					RenderSystem::GetInstance().DrawSprite(m_imageIndex, m_pTransform->GetPosition().x, m_pTransform->GetPosition().y, this->GetPTransform());
				}
				break;
			case 3:
				if (m_name == eObjectName::OPENING3)
				{
					m_imageIndex = IMAGE_OPENING_SCENE3;
					RenderSystem::GetInstance().DrawSprite(m_imageIndex, m_pTransform->GetPosition().x, m_pTransform->GetPosition().y, this->GetPTransform());
				}
				if (m_name == eObjectName::OPENING_LINE3)
				{
					m_imageIndex = IMAGE_OPENING_LINE3;
					RenderSystem::GetInstance().DrawSprite(m_imageIndex, m_pTransform->GetPosition().x, m_pTransform->GetPosition().y, this->GetPTransform());
				}
				break;
			case 4:
				if (m_name == eObjectName::OPENING3)
				{
					m_imageIndex = IMAGE_OPENING_SCENE3;
					RenderSystem::GetInstance().DrawSprite(m_imageIndex, m_pTransform->GetPosition().x, m_pTransform->GetPosition().y, this->GetPTransform());
				}
				if (m_name == eObjectName::OPENING4)
				{
					m_imageIndex = IMAGE_OPENING_SCENE4;
					RenderSystem::GetInstance().DrawSprite(m_imageIndex, m_pTransform->GetPosition().x, m_pTransform->GetPosition().y, this->GetPTransform());
				}
				if (m_name == eObjectName::OPENING_LINE4)
				{
					m_imageIndex = IMAGE_OPENING_LINE4;
					RenderSystem::GetInstance().DrawSprite(m_imageIndex, m_pTransform->GetPosition().x, m_pTransform->GetPosition().y, this->GetPTransform());
				}
				break;
			case 5:
				if (m_name == eObjectName::OPENING5)
				{
					m_imageIndex = IMAGE_OPENING_SCENE5;
					RenderSystem::GetInstance().DrawSprite(m_imageIndex, m_pTransform->GetPosition().x, m_pTransform->GetPosition().y, this->GetPTransform());
				}
				if (m_name == eObjectName::OPENING_LINE5)
				{
					m_imageIndex = IMAGE_OPENING_LINE5;
					RenderSystem::GetInstance().DrawSprite(m_imageIndex, m_pTransform->GetPosition().x, m_pTransform->GetPosition().y, this->GetPTransform());
				}
				break;
			case 6:
				SceneManager::GetInstance().ChangeScene(eSceneName::STAGE1);
				m_KeyCount = 1;
				break;
		}
}

void Opening_Object::Sortation()
{
	switch (m_name)
	{
		case eObjectName::OPENING1:
			m_imageIndex = IMAGE_OPENING_SCENE1;
			break;

		case eObjectName::OPENING2:
			m_imageIndex = IMAGE_OPENING_SCENE2;
			break;

		case eObjectName::OPENING3:
			m_imageIndex = IMAGE_OPENING_SCENE3;
			break;

		case eObjectName::OPENING4:
			m_imageIndex = IMAGE_OPENING_SCENE4;
			break;

		case eObjectName::OPENING5:
			m_imageIndex = IMAGE_OPENING_SCENE5;
			break;

		case eObjectName::OPENING_LINE1:
			m_imageIndex = IMAGE_OPENING_LINE1;
			break;

		case eObjectName::OPENING_LINE2:
			m_imageIndex = IMAGE_OPENING_LINE2;
			break;

		case eObjectName::OPENING_LINE3:
			m_imageIndex = IMAGE_OPENING_LINE3;
			break;

		case eObjectName::OPENING_LINE4:
			m_imageIndex = IMAGE_OPENING_LINE4;
			break;

		case eObjectName::OPENING_LINE5:
			m_imageIndex = IMAGE_OPENING_LINE5;
			break;
	}
}

void Opening_Object::ClickEvent()
{
	if (InputManager::GetInstance().IsKeyDown(VK_SPACE) &&
		SceneManager::GetInstance().GetCurScene()->GetName() == eSceneName::OPENING)
	{
		m_KeyCount++;
	}
}
