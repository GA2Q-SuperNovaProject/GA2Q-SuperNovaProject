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
	//[TW] ���� Stage2���� ���߿� �ݿ��Ǿ�� �Ѵ�.
	BulletManager::GetInstance().UpdateManager(eBulletDiff::EASY, this);
	

	/// Sound ���
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

	for (size_t i = 0; i < m_arrobj.size(); i++) // [TW] ��� �����ε�� ���� ������, �̸� �����ؾ� �Ѵ�.
	{
		m_arrobj[i]->Update();
	}
}

void Stage1::LateUpdate()
{
	//�ݸ��� ���� üũ�� ���� �ʼ�.
	for (size_t i = 0; i < m_arrobj.size(); i++)
	{
		m_arrobj[i]->LateUpdate();
	}
}
