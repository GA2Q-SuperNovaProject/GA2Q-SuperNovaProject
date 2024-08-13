#include "True_Ending.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "MouseInputManager.h"
#include "SoundManager.h"
#include "RenderSystem.h"
#include "Scene.h"
#include "Debug.h"

True_Ending::True_Ending(eObjectTag tag, eObjectName name, Transform transform)
	: GameObject(tag, name, transform), m_isClick(false), m_KeyCount(1)
{
	Sortation();
}

True_Ending::~True_Ending()
{

}

void True_Ending::Update()
{
	ClickEvent();
}

void True_Ending::Render()
{
	switch (m_KeyCount)
	{
		case 1:
			if (m_name == eObjectName::TRUE1)
			{
				RenderSystem::GetInstance().DrawSprite(m_imageIndex, m_pTransform->GetPosition().x, m_pTransform->GetPosition().y, this->GetPTransform());
			}
			break;

		case 2:
			if (m_name == eObjectName::TRUE2)
			{
				RenderSystem::GetInstance().DrawSprite(m_imageIndex, m_pTransform->GetPosition().x, m_pTransform->GetPosition().y, this->GetPTransform());
			}
			break;

		case 3:
			if (m_name == eObjectName::TRUE3)
			{
				RenderSystem::GetInstance().DrawSprite(m_imageIndex, m_pTransform->GetPosition().x, m_pTransform->GetPosition().y, this->GetPTransform());
			}
			break;

		case 4:
			if (m_name == eObjectName::TRUE4)
			{
				m_imageIndex = IMAGE_TRUE_SCENE4;
				RenderSystem::GetInstance().DrawSprite(m_imageIndex, m_pTransform->GetPosition().x, m_pTransform->GetPosition().y, this->GetPTransform());
			}
			if (m_name == eObjectName::TRUE_LINE1)
			{
				m_imageIndex = IMAGE_TRUE_LINE1;
				RenderSystem::GetInstance().DrawSprite(m_imageIndex, m_pTransform->GetPosition().x, m_pTransform->GetPosition().y, this->GetPTransform());
			}
			break;

		case 5:
			if (m_name == eObjectName::TRUE5)
			{
				m_imageIndex = IMAGE_TRUE_SCENE5;
				RenderSystem::GetInstance().DrawSprite(m_imageIndex, m_pTransform->GetPosition().x, m_pTransform->GetPosition().y, this->GetPTransform());
			}
			if (m_name == eObjectName::TRUE_LINE2)
			{
				m_imageIndex = IMAGE_TRUE_LINE2;
				RenderSystem::GetInstance().DrawSprite(m_imageIndex, m_pTransform->GetPosition().x, m_pTransform->GetPosition().y, this->GetPTransform());
			}
			break;

		case 6:
			if (m_name == eObjectName::TRUE6)
			{
				m_imageIndex = IMAGE_TRUE_SCENE6;
				RenderSystem::GetInstance().DrawSprite(m_imageIndex, m_pTransform->GetPosition().x, m_pTransform->GetPosition().y, this->GetPTransform());
			}
			if (m_name == eObjectName::TRUE_LINE3)
			{
				m_imageIndex = IMAGE_TRUE_LINE3;
				RenderSystem::GetInstance().DrawSprite(m_imageIndex, m_pTransform->GetPosition().x, m_pTransform->GetPosition().y, this->GetPTransform());
			}
			break;

		case 7:
			if (m_name == eObjectName::TRUE7)
			{
				m_imageIndex = IMAGE_TRUE_SCENE7;
				RenderSystem::GetInstance().DrawSprite(m_imageIndex, m_pTransform->GetPosition().x, m_pTransform->GetPosition().y, this->GetPTransform());
			}
			if (m_name == eObjectName::TRUE_LINE4)
			{
				m_imageIndex = IMAGE_TRUE_LINE4;
				RenderSystem::GetInstance().DrawSprite(m_imageIndex, m_pTransform->GetPosition().x, m_pTransform->GetPosition().y, this->GetPTransform());
			}
			break;

		case 8:
			if (m_name == eObjectName::TRUE8_1)
			{
				m_imageIndex = IMAGE_TRUE_SCENE8_1;
				RenderSystem::GetInstance().DrawSprite(m_imageIndex, m_pTransform->GetPosition().x, m_pTransform->GetPosition().y, this->GetPTransform());
			}
			if (m_name == eObjectName::TRUE_LINE5)
			{
				m_imageIndex = IMAGE_TRUE_LINE5;
				RenderSystem::GetInstance().DrawSprite(m_imageIndex, m_pTransform->GetPosition().x, m_pTransform->GetPosition().y, this->GetPTransform());
			}
			break;

		case 9:
			if (m_name == eObjectName::TRUE8_1)
			{
				m_imageIndex = IMAGE_TRUE_SCENE8_1;
				RenderSystem::GetInstance().DrawSprite(m_imageIndex, m_pTransform->GetPosition().x, m_pTransform->GetPosition().y, this->GetPTransform());
			}
			if (m_name == eObjectName::TRUE8_2)
			{
				m_imageIndex = IMAGE_TRUE_SCENE8_2;
				RenderSystem::GetInstance().DrawSprite(m_imageIndex, m_pTransform->GetPosition().x, m_pTransform->GetPosition().y, this->GetPTransform());
			}
			if (m_name == eObjectName::TRUE_LINE5)
			{
				m_imageIndex = IMAGE_TRUE_LINE5;
				RenderSystem::GetInstance().DrawSprite(m_imageIndex, m_pTransform->GetPosition().x, m_pTransform->GetPosition().y, this->GetPTransform());
			}
			break;

		case 10:
			if (m_name == eObjectName::TRUE9)
			{
				m_imageIndex = IMAGE_TRUE_SCENE9;
				RenderSystem::GetInstance().DrawSprite(m_imageIndex, m_pTransform->GetPosition().x, m_pTransform->GetPosition().y, this->GetPTransform());
				
			}
			if (m_name == eObjectName::TRUE_LINE6)
			{
				m_imageIndex = IMAGE_TRUE_LINE6;
				RenderSystem::GetInstance().DrawSprite(m_imageIndex, m_pTransform->GetPosition().x, m_pTransform->GetPosition().y, this->GetPTransform());
			}
			break;

		case 11:
			if (m_name == eObjectName::TRUE10)
			{
				m_imageIndex = IMAGE_TRUE_SCENE10;
				RenderSystem::GetInstance().DrawSprite(m_imageIndex, m_pTransform->GetPosition().x, m_pTransform->GetPosition().y, this->GetPTransform());
			}
			if (m_name == eObjectName::TRUE_LINE7)
			{
				m_imageIndex = IMAGE_TRUE_LINE7;
				RenderSystem::GetInstance().DrawSprite(m_imageIndex, m_pTransform->GetPosition().x, m_pTransform->GetPosition().y, this->GetPTransform());
			}
			break;

		case 12:
			if (m_name == eObjectName::TRUE11)
			{
				m_imageIndex = IMAGE_TRUE_SCENE11;
				RenderSystem::GetInstance().DrawSprite(m_imageIndex, m_pTransform->GetPosition().x, m_pTransform->GetPosition().y, this->GetPTransform());
			}
			if (m_name == eObjectName::TRUE_LINE8)
			{
				m_imageIndex = IMAGE_TRUE_LINE8;
				RenderSystem::GetInstance().DrawSprite(m_imageIndex, m_pTransform->GetPosition().x, m_pTransform->GetPosition().y, this->GetPTransform());
			}
			break;

		case 13:
			if (m_name == eObjectName::TRUE12)
			{
				m_imageIndex = IMAGE_TRUE_SCENE12;
				RenderSystem::GetInstance().DrawSprite(m_imageIndex, m_pTransform->GetPosition().x, m_pTransform->GetPosition().y, this->GetPTransform());
			}
			if (m_name == eObjectName::TRUE_LINE9)
			{
				m_imageIndex = IMAGE_TRUE_LINE9;
				RenderSystem::GetInstance().DrawSprite(m_imageIndex, m_pTransform->GetPosition().x, m_pTransform->GetPosition().y, this->GetPTransform());
			}
			break;

		case 14:
			if (m_name == eObjectName::TRUE13)
			{
				m_imageIndex = IMAGE_TRUE_SCENE13;
				RenderSystem::GetInstance().DrawSprite(m_imageIndex, m_pTransform->GetPosition().x, m_pTransform->GetPosition().y, this->GetPTransform());
			}
			if (m_name == eObjectName::TRUE_LINE10)
			{
				m_imageIndex = IMAGE_TRUE_LINE10;
				RenderSystem::GetInstance().DrawSprite(m_imageIndex, m_pTransform->GetPosition().x, m_pTransform->GetPosition().y, this->GetPTransform());
			}
			break;

		case 15:
			SceneManager::GetInstance().ChangeScene(eSceneName::MAIN);
			m_KeyCount = 1;
			break;
	}
}

void True_Ending::Sortation()
{
	switch (m_name)
	{
		case eObjectName::TRUE1:
			m_imageIndex = IMAGE_TRUE_SCENE1;
			break;

		case eObjectName::TRUE2:
			m_imageIndex = IMAGE_TRUE_SCENE2;
			break;

		case eObjectName::TRUE3:
			m_imageIndex = IMAGE_TRUE_SCENE3;
			break;

		case eObjectName::TRUE4:
			m_imageIndex = IMAGE_TRUE_SCENE4;
			break;

		case eObjectName::TRUE5:
			m_imageIndex = IMAGE_TRUE_SCENE5;
			break;

		case eObjectName::TRUE6:
			m_imageIndex = IMAGE_TRUE_SCENE6;
			break;

		case eObjectName::TRUE7:
			m_imageIndex = IMAGE_TRUE_SCENE7;
			break;

		case eObjectName::TRUE8_1:
			m_imageIndex = IMAGE_TRUE_SCENE8_1;
			break;

		case eObjectName::TRUE8_2:
			m_imageIndex = IMAGE_TRUE_SCENE8_2;
			break;

		case eObjectName::TRUE9:
			m_imageIndex = IMAGE_TRUE_SCENE9;
			break;

		case eObjectName::TRUE10:
			m_imageIndex = IMAGE_TRUE_SCENE10;
			break;

		case eObjectName::TRUE11:
			m_imageIndex = IMAGE_TRUE_SCENE11;
			break;

		case eObjectName::TRUE12:
			m_imageIndex = IMAGE_TRUE_SCENE12;
			break;

		case eObjectName::TRUE13:
			m_imageIndex = IMAGE_TRUE_SCENE13;
			break;

		case eObjectName::TRUE_LINE1:
			m_imageIndex = IMAGE_TRUE_LINE1;
			break;

		case eObjectName::TRUE_LINE2:
			m_imageIndex = IMAGE_TRUE_LINE2;
			break;

		case eObjectName::TRUE_LINE3:
			m_imageIndex = IMAGE_TRUE_LINE3;
			break;

		case eObjectName::TRUE_LINE4:
			m_imageIndex = IMAGE_TRUE_LINE4;
			break;

		case eObjectName::TRUE_LINE5:
			m_imageIndex = IMAGE_TRUE_LINE5;
			break;

		case eObjectName::TRUE_LINE6:
			m_imageIndex = IMAGE_TRUE_LINE6;
			break;

		case eObjectName::TRUE_LINE7:
			m_imageIndex = IMAGE_TRUE_LINE7;
			break;

		case eObjectName::TRUE_LINE8:
			m_imageIndex = IMAGE_TRUE_LINE8;
			break;

		case eObjectName::TRUE_LINE9:
			m_imageIndex = IMAGE_TRUE_LINE9;
			break;

		case eObjectName::TRUE_LINE10:
			m_imageIndex = IMAGE_TRUE_LINE10;
			break;
	}
}

void True_Ending::ClickEvent()
{
	if (InputManager::GetInstance().IsKeyDown(VK_SPACE) &&
		SceneManager::GetInstance().GetCurScene()->GetName() == eSceneName::TRUE_ENDING)
	{
		m_KeyCount++;
	}
}
