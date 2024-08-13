#include "Normal_Ending.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "MouseInputManager.h"
#include "SoundManager.h"
#include "RenderSystem.h"
#include "Scene.h"
#include "Debug.h"

Normal_Ending::Normal_Ending(eObjectTag tag, eObjectName name, Transform transform)
	: GameObject(tag, name, transform), m_isClick(false), m_KeyCount(1)
{
	Sortation();
}

Normal_Ending::~Normal_Ending()
{

}

void Normal_Ending::Update()
{
	ClickEvent();
}

void Normal_Ending::Render()
{

	switch (m_KeyCount)
	{
		case 1:
			if (m_name == eObjectName::NORMAL1)
			{
				m_imageIndex = IMAGE_NORMAL_SCENE;
				RenderSystem::GetInstance().DrawSprite(m_imageIndex, m_pTransform->GetPosition().x, m_pTransform->GetPosition().y, this->GetPTransform());
			}
			if (m_name == eObjectName::NORMAL_LINE1)
			{
				m_imageIndex = IMAGE_NORMAL_LINE1;
				RenderSystem::GetInstance().DrawSprite(m_imageIndex, m_pTransform->GetPosition().x, m_pTransform->GetPosition().y, this->GetPTransform());
			}
			break;
		case 2:
			SceneManager::GetInstance().ChangeScene(eSceneName::MAIN);
			m_KeyCount = 1;
			break;
	}
}

void Normal_Ending::Sortation()
{
	switch (m_name)
	{
		case eObjectName::NORMAL1:
			m_imageIndex = IMAGE_NORMAL_SCENE;
			break;

		case eObjectName::NORMAL_LINE1:
			m_imageIndex = IMAGE_NORMAL_LINE1;
			break;
	}
}

void Normal_Ending::ClickEvent()
{
	if (InputManager::GetInstance().IsKeyDown(VK_SPACE) &&
		SceneManager::GetInstance().GetCurScene()->GetName() == eSceneName::NORMAL_ENDING)
	{
		m_KeyCount++;
	}
}
