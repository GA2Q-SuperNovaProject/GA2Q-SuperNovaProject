#include "MainUI.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "MouseInputManager.h"
#include "RenderSystem.h"
#include "Debug.h"
#include "Scene.h"
#include "SceneManager.h"

bool MainUI::m_ShowCreditPopup = false;


MainUI::MainUI(eObjectTag tag, eObjectName name, Transform transform)
	: GameObject(tag, name, transform)
{
	Sortation();
}

MainUI::~MainUI()
{

}

void MainUI::Start()
{
	playButton = belongScene->FindObjectInScene(eObjectName::START_BUTTON);
	optionButton = belongScene->FindObjectInScene(eObjectName::OPTION_BUTTON);
	creditButton = belongScene->FindObjectInScene(eObjectName::CREDIT_BUTTON);
}

void MainUI::Update()
{
	ClickEvent();
}

void MainUI::Render()
{
	RenderSystem::GetInstance().DrawSprite(m_changedImageIndex, m_pTransform->GetPosition().x, m_pTransform->GetPosition().y, this->GetPTransform());

	if (m_ShowCreditPopup)
	{
		RenderSystem::GetInstance().DrawSprite(IMAGE_CREDIT_I, 960, 540);
	}

}

void MainUI::Sortation()
{
	switch (m_name)
	{
		case eObjectName::START_BUTTON:
			m_imageIndex = IMAGE_START;
			m_changedImageIndex = IMAGE_START;
			break;

		case eObjectName::OPTION_BUTTON:
			m_imageIndex = IMAGE_OPTION;
			m_changedImageIndex = IMAGE_OPTION;
			break;

		case eObjectName::CREDIT_BUTTON:
			m_imageIndex = IMAGE_CREDIT;
			m_changedImageIndex = IMAGE_CREDIT;
			break;

		case eObjectName::QUIT_BUTTON:
			m_imageIndex = IMAGE_QUIT;
			m_changedImageIndex = IMAGE_QUIT;
			break;
	}
}

void MainUI::ClickEvent()
{
	if (MouseInputManager::GetInstance().IsOnBoard(m_pTransform->m_Position, m_imageIndex))
	{
		m_changedImageIndex = m_imageIndex + 1;

		if (m_isClick == false && InputManager::GetInstance().IsKeyDown(VK_LMB))
		{
			m_isClick = true;

			switch (m_changedImageIndex)
			{
				case IMAGE_START_A:
					if (m_ShowCreditPopup == false)
					{
						SceneManager::GetInstance().ChangeScene(eSceneName::OPENING);
					}
					break;

				case IMAGE_OPTION_A:
					if (m_ShowCreditPopup == false)
					{
						SceneManager::GetInstance().ChangeScene(eSceneName::MAIN_OPTION);
					}
					break;

				case IMAGE_CREDIT_A:
					m_ShowCreditPopup = true;
					break;

				case IMAGE_QUIT_A:
					HWND hWnd = GetFocus();
					DestroyWindow(hWnd);
					break;

			}
		}
	}
	else
	{
		m_changedImageIndex = m_imageIndex;

		if (m_isClick == true && InputManager::GetInstance().IsKeyDown(VK_LMB))
		{
			if (!(MouseInputManager::GetInstance().IsOnBoardRect(MouseInputManager::GetInstance().GetPos(), creditScreenRect)))
			{
				m_isClick = false;
				m_ShowCreditPopup = false;
			}
		}
	}
}

//960, 540

//707, 707