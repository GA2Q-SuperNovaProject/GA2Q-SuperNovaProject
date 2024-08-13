#include "Bad_Ending.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "MouseInputManager.h"
#include "SoundManager.h"
#include "RenderSystem.h"
#include "Scene.h"
#include "Debug.h"

Bad_Ending::Bad_Ending(eObjectTag tag, eObjectName name, Transform transform)
	: GameObject(tag, name, transform), m_isClick(false), m_KeyCount(1)
{
	Sortation();
}

Bad_Ending::~Bad_Ending()
{

}

void Bad_Ending::Update()
{
	GameOver();
	ClickEvent();
}

void Bad_Ending::Render()
{
	switch (m_KeyCount)
	{
		case 1:
			if (m_name == eObjectName::BAD1)
			{
				RenderSystem::GetInstance().DrawSprite(m_imageIndex, m_pTransform->GetPosition().x, m_pTransform->GetPosition().y, this->GetPTransform());
			}
			break;

		case 2:
			if (m_name == eObjectName::BAD2)
			{
				m_imageIndex = IMAGE_BAD_SCENE2;
				RenderSystem::GetInstance().DrawSprite(m_imageIndex, m_pTransform->GetPosition().x, m_pTransform->GetPosition().y, this->GetPTransform());
			}
			if (m_name == eObjectName::BAD_LINE1)
			{
				m_imageIndex = IMAGE_BAD_LINE1;
				RenderSystem::GetInstance().DrawSprite(m_imageIndex, m_pTransform->GetPosition().x, m_pTransform->GetPosition().y, this->GetPTransform());
			}
			break;

		case 3:
			m_isClick = true;

			if (m_name == eObjectName::BAD2)
			{
				m_imageIndex = IMAGE_BAD_SCENE2;
				RenderSystem::GetInstance().DrawSprite(m_imageIndex, m_pTransform->GetPosition().x, m_pTransform->GetPosition().y, this->GetPTransform());
			}
			if (m_name == eObjectName::BAD_LINE1)
			{
				m_imageIndex = IMAGE_BAD_LINE1;
				RenderSystem::GetInstance().DrawSprite(m_imageIndex, m_pTransform->GetPosition().x, m_pTransform->GetPosition().y, this->GetPTransform());
			}

			if (m_name == eObjectName::GAMEOVER)
			{
				m_imageIndex = IMAGE_GAMEOVER;
				RenderSystem::GetInstance().DrawSprite(m_imageIndex, m_pTransform->GetPosition().x, m_pTransform->GetPosition().y, this->GetPTransform());


			}
			else if (m_isMain == true && m_name == eObjectName::GAMEOVER_MAIN)
			{

				m_imageIndex = IMAGE_GAMEOVER_MAIN;
				RenderSystem::GetInstance().DrawSprite(m_imageIndex, m_pTransform->GetPosition().x, m_pTransform->GetPosition().y, this->GetPTransform());
			}
			else if (m_isRetry == true && m_name == eObjectName::GAMEOVER_RETRY)
			{

				m_imageIndex = IMAGE_GAMEOVER_RETRY;
				RenderSystem::GetInstance().DrawSprite(m_imageIndex, m_pTransform->GetPosition().x, m_pTransform->GetPosition().y, this->GetPTransform());
			}
			break;
	}
}

void Bad_Ending::Sortation()
{
	switch (m_name)
	{
		case eObjectName::BAD1:
			m_imageIndex = IMAGE_BAD_SCENE1;
			break;

		case eObjectName::BAD2:
			m_imageIndex = IMAGE_BAD_SCENE2;
			break;

		case eObjectName::BAD_LINE1:
			m_imageIndex = IMAGE_BAD_LINE1;
			break;

		case eObjectName::GAMEOVER:
			m_imageIndex = IMAGE_GAMEOVER;
			break;

		case eObjectName::GAMEOVER_MAIN:
			m_imageIndex = IMAGE_GAMEOVER_MAIN;
			break;

		case eObjectName::GAMEOVER_RETRY:
			m_imageIndex = IMAGE_GAMEOVER_RETRY;
			break;
	}
}

void Bad_Ending::ClickEvent()
{
	if (InputManager::GetInstance().IsKeyDown(VK_SPACE) &&
		SceneManager::GetInstance().GetCurScene()->GetName() == eSceneName::BAD_ENDING)
	{
		if (m_KeyCount < 3)
		{
			m_KeyCount++;
		}
	}


	if (m_isClick == true && InputManager::GetInstance().IsKeyDown(VK_LMB))
	{
		if (m_isMain == true)
		{
			SceneManager::GetInstance().ActuallyChangeScene(eSceneName::MAIN);
			m_isClick = false;
			m_KeyCount = 1;
			m_isMain = false;
			m_isRetry = false;
		}
		else if (m_isRetry == true)
		{
			SceneManager::GetInstance().ActuallyChangeScene(eSceneName::TRUE_ENDING);
			m_isClick = false;
			m_KeyCount = 1;
			m_isMain = false;
			m_isRetry = false;
		}
	}
}

void Bad_Ending::GameOver()
{
	if ((m_isMain == true || m_isRetry == true) &&
		m_name == eObjectName::GAMEOVER || m_name == eObjectName::GAMEOVER_MAIN || m_name == eObjectName::GAMEOVER_RETRY)
	{
		Rect2D main =
		{
			600,
			360,
			1320,
			530
		};

		Rect2D retry =
		{
			600,
			550,
			1320,
			720
		};


		if (MouseInputManager::GetInstance().IsOnBoardRect(MouseInputManager::GetInstance().GetPos(), main))
		{
			m_isMain = true;
			m_isRetry = false;
		}
		else if (MouseInputManager::GetInstance().IsOnBoardRect(MouseInputManager::GetInstance().GetPos(), retry))
		{
			m_isRetry = true;
			m_isMain = false;
		}
		else
		{
			m_isMain = false;
			m_isRetry = false;
		}
	}
}
