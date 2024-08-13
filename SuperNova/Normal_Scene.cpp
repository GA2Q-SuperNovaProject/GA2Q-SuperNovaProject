#include "Normal_Scene.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "SoundManager.h"

Normal_Scene::Normal_Scene(eSceneName sceneName)
	: Scene(sceneName), m_isNowScene(false), m_isMusicStart(false)
{

}

Normal_Scene::~Normal_Scene()
{

}

void Normal_Scene::Update()
{
	if (SceneManager::GetInstance().GetCurScene() == this && !m_isNowScene)
	{
		m_isNowScene = true;
		m_isMusicStart = true;
	}

	if (m_isMusicStart)
	{
		SoundManager::StopAllSound();
		SoundManager::PlaySounds(SOUND_NORMAL_ENDING);
		m_isMusicStart = false;
	}

	for (size_t i = 0; i < m_arrobj.size(); i++)
	{
		m_arrobj[i]->Update();
	}
}
