#include "Main_Scene.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "SoundManager.h"


Main_Scene::Main_Scene(eSceneName sceneName)
	: Scene(sceneName), m_isNowScene(false), m_isMusicStart(false)
{

}

Main_Scene::~Main_Scene()
{

}

void Main_Scene::Update()
{
	if (SceneManager::GetInstance().GetCurScene() == this && !m_isNowScene)
	{
		m_isNowScene = true;
		m_isMusicStart = true;
	}

	if (m_isMusicStart)
	{
		SoundManager::StopAllSound();
		SoundManager::PlaySounds(SOUND_INTRO);
		m_isMusicStart = false;
	}

	if (this->m_SceneStartFlag == true)
	{
		for (size_t i = 0; i < m_arrobj.size(); i++)
		{
			m_arrobj[i]->Start();
		}
		m_SceneStartFlag = false;
	}

	for (size_t i = 0; i < m_arrobj.size(); i++)
	{
		m_arrobj[i]->Update();
	}

	//if (InputManager::GetInstance().IsKeyDown('2')
	//	|| InputManager::GetInstance().IsKeyPress('2'))
	//{
	//	SceneManager::GetInstance().ChangeScene(eSceneName::STAGE1);
	//}

	//if (InputManager::GetInstance().IsKeyDown(VK_F2)
	//	|| InputManager::GetInstance().IsKeyPress(VK_F2))
	//{
	//	SceneManager::GetInstance().ChangeScene(eSceneName::STAGE2);
	//}

	//if (InputManager::GetInstance().IsKeyDown(VK_F3)
	//	|| InputManager::GetInstance().IsKeyPress(VK_F3))
	//{
	//	SceneManager::GetInstance().ChangeScene(eSceneName::STAGE3);
	//}
	//
	//if (InputManager::GetInstance().IsKeyDown('4')
	//	|| InputManager::GetInstance().IsKeyPress('4'))
	//{
	//	SceneManager::GetInstance().ChangeScene(eSceneName::SNAKE_PLANET);
	//}

	//if (InputManager::GetInstance().IsKeyDown('5')
	//	|| InputManager::GetInstance().IsKeyPress('5'))
	//{
	//	SceneManager::GetInstance().ChangeScene(eSceneName::STORY_PLANET);
	//}

	// if(InputManager::GetInstance().Update())
}

void Main_Scene::LateUpdate()
{
	for (size_t i = 0; i < m_arrobj.size(); i++)
	{
		m_arrobj[i]->LateUpdate();
	}
}
