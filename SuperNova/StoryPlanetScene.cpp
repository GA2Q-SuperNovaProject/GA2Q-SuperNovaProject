#include "StoryPlanetScene.h"
#include "SoundManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameObject.h"

StoryPlanetScene::StoryPlanetScene(eSceneName sceneName)
	: Scene(sceneName), m_isNowScene(false), m_isMusicStart(false)
{
}

StoryPlanetScene::~StoryPlanetScene()
{
}

void StoryPlanetScene::Update()
{
	if (SceneManager::GetInstance().GetCurScene() == this && !m_isNowScene)
	{
		m_isNowScene = true;
		m_isMusicStart = true;
	}

	if (m_isMusicStart)
	{
		SoundManager::StopAllSound();
		SoundManager::PlaySounds(SOUND_STORY_PLANET);
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
}

//void StoryPlanetScene::LateUpdate()
//{
//}
