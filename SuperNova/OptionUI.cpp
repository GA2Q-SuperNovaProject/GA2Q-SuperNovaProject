#include "OptionUI.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "MouseInputManager.h"
#include "SoundManager.h"
#include "RenderSystem.h"
#include "Scene.h"
#include "MainUI.h"
#include "GameUI.h"
#include "Debug.h"

OptionUI::OptionUI(eObjectTag tag, eObjectName name, Transform transform)
	: GameObject(tag, name, transform)
{
	Sortation();
}

OptionUI::~OptionUI()
{

}

void OptionUI::Update()
{
	ClickEvent();
}

void OptionUI::Render()
{
	RenderSystem::GetInstance().DrawSprite(m_imageIndex, m_pTransform->GetPosition().x, m_pTransform->GetPosition().y, this->GetPTransform());
}

void OptionUI::Sortation()
{
	switch (m_name)
	{
		case eObjectName::OPTION_MENU:
			m_imageIndex = IMAGE_OPTION_MENU;
			break;

		case eObjectName::OPTION_BAR:
			m_imageIndex = IMAGE_OPTION_BAR;
			break;

		case eObjectName::OPTION_SOUNDBOX:
			m_imageIndex = IMAGE_OPTION_BOX;
			break;

		case eObjectName::OPTION_BGMBOX:
			m_imageIndex = IMAGE_OPTION_BOX;
			break;

		case eObjectName::OPTION_QUIT:
			m_imageIndex = IMAGE_OPTION_QUIT;
			break;
	}
}

void OptionUI::ClickEvent()
{
	if (MouseInputManager::GetInstance().IsOnBoard(m_pTransform->m_Position, m_imageIndex))
	{

		if (m_isClick == false && InputManager::GetInstance().IsKeyDown(VK_LMB)
			|| InputManager::GetInstance().IsKeyPress(VK_LMB))
		{
			m_isClick = true;

			switch (m_name)
			{
				case eObjectName::OPTION_SOUNDBOX:
					m_pTransform->m_Position.x = MouseInputManager::GetInstance().GetPos().x;

					if (m_pTransform->m_Position.x <= 901)
					{
						m_pTransform->m_Position.x = 901;
					}

					if (m_pTransform->m_Position.x >= 1247)
					{
						m_pTransform->m_Position.x = 1247;
					}
					VolumeEvent();
					break;

				case eObjectName::OPTION_BGMBOX:
					m_pTransform->m_Position.x = MouseInputManager::GetInstance().GetPos().x;

					if (m_pTransform->m_Position.x <= 901)
					{
						m_pTransform->m_Position.x = 901;
					}

					if (m_pTransform->m_Position.x >= 1247)
					{
						m_pTransform->m_Position.x = 1247;
					}
					VolumeEvent();
					break;

				case eObjectName::OPTION_QUIT:
					if (SceneManager::GetInstance().GetCurScene()->GetName() == eSceneName::MAIN_OPTION)
					{
						SceneManager::GetInstance().ChangeScene(eSceneName::MAIN);
					}
					
					if (SceneManager::GetInstance().GetCurScene()->GetName() == eSceneName::STAGE1)
					{
						//GameUI::GetIsGameOptionOn
					}
					int i = 0;
					break;
			};

			//switch (m_changedImageIndex)
			//{
			//case IMAGE_START_A:
			//	SceneManager::GetInstance().ChangeScene(eSceneName::STAGE1);
			//	break;

			//case IMAGE_OPTION_A:
			//	SceneManager::GetInstance().ChangeScene("MainOption");
			//	break;

			//case IMAGE_CREDIT_A:
			//	m_ShowCreditPopup = true;
			//	break;

			//case IMAGE_QUIT_A:
			//	HWND hWnd = GetFocus();
			//	DestroyWindow(hWnd);
			//	break;
			//}
		}
	}
	else
	{
		if (m_isClick == true && InputManager::GetInstance().IsKeyDown(VK_LMB))
		{
			m_isClick = false;
		}
	}
}

void OptionUI::VolumeEvent()
{
	float volume = (1247 - m_pTransform->m_Position.x) / 394;

	SoundManager::SetSoundVolume(SOUND_STAGE1, volume);
}
