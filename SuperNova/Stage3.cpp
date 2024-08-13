#include "Stage3.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "GameObject.h"
#include "InputManager.h"

Stage3::Stage3(eSceneName sceneName)
	: Scene(sceneName), m_isNowScene(false), m_isMusicStart(false)
{

}

Stage3::~Stage3()
{

}

void Stage3::Update()
{
	/// Sound 재생
	if (SceneManager::GetInstance().GetCurScene() == this && !m_isNowScene)
	{
		m_isNowScene = true;
		m_isMusicStart = true;
	}

	if (m_isMusicStart)
	{
		SoundManager::StopAllSound();
		SoundManager::PlaySounds(SOUND_STAGE3);
		m_isMusicStart = false;
	}

	if (InputManager::GetInstance().IsKeyDown(VK_F1))
	{
		SceneManager::GetInstance().ChangeScene(eSceneName::TRUE_ENDING);
	}
	
	if (InputManager::GetInstance().IsKeyDown(VK_F2))
	{
		SceneManager::GetInstance().ChangeScene(eSceneName::NORMAL_ENDING);
	}

	if (this->m_SceneStartFlag == true)
	{
		for (size_t i = 0; i < m_arrobj.size(); i++)
		{
			m_arrobj[i]->Start();
		}
		m_SceneStartFlag = false;
	}

	for (size_t i = 0; i < m_arrobj.size(); i++) // [TW] 모든 오버로드된 씬이 있으면, 이를 수행해야 한다.
	{
		m_arrobj[i]->Update();
	}
}

void Stage3::LateUpdate()
{
	//콜리젼 관련 체크를 위해 필수.
	for (size_t i = 0; i < m_arrobj.size(); i++)
	{
		m_arrobj[i]->LateUpdate();
	}
}
