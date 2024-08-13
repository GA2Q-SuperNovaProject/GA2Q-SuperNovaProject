#include "Stage2.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "BulletManager.h"
#include "SoundManager.h"

Stage2::Stage2(eSceneName sceneName)
	: Scene(sceneName), m_isNowScene(false), m_isMusicStart(false)
{

}

Stage2::~Stage2()
{

}

void Stage2::Update()
{
	BulletManager::GetInstance().UpdateManager(eBulletDiff::HARD, this);

	if (SceneManager::GetInstance().GetCurScene() == this && !m_isNowScene)
	{
		m_isNowScene = true;
		m_isMusicStart = true;
	}

	if (m_isMusicStart)
	{
		SoundManager::StopAllSound();
		SoundManager::PlaySounds(SOUND_STAGE2);
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


