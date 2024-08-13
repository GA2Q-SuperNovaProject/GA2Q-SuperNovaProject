#include "Stage1.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "BulletManager.h"
#include "SoundManager.h"

Stage1::Stage1(eSceneName sceneName)
	: Scene(sceneName), m_isNowScene(false), m_isMusicStart(false)
{

}

Stage1::~Stage1()
{

}

void Stage1::Update()
{
	//[TW] 만약 Stage2에도 나중에 반영되어야 한다.
	BulletManager::GetInstance().UpdateManager(eBulletDiff::EASY, this);
	

	/// Sound 재생
	if (SceneManager::GetInstance().GetCurScene() == this && !m_isNowScene)
	{
		m_isNowScene = true;
		m_isMusicStart = true;
	}

	if (m_isMusicStart)
	{
		SoundManager::StopAllSound();
		SoundManager::PlaySounds(SOUND_STAGE1);
		m_isMusicStart = false;
	}

	if (playerObject == nullptr)
	{
		playerObject = FindObjectInScene(eObjectName::PLAYER);
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

void Stage1::LateUpdate()
{
	//콜리젼 관련 체크를 위해 필수.
	for (size_t i = 0; i < m_arrobj.size(); i++)
	{
		m_arrobj[i]->LateUpdate();
	}
}
