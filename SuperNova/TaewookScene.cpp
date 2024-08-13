#include "TaewookScene.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "GameObject.h"
#include <string>
using namespace std;

TaewookScene::TaewookScene(eSceneName sceneName)
	: Scene(sceneName)
{
	//
}

TaewookScene::~TaewookScene()
{
	//
}

void TaewookScene::Update()
{
	if (this->m_SceneStartFlag == true)
	{
		for (size_t i = 0; i < m_arrobj.size(); i++)
		{
			m_arrobj[i]->Start();
		}
		m_SceneStartFlag = false;
	}

	if (InputManager::GetInstance().IsKeyDown('I'))
	{
		SceneManager::GetInstance().SetCurScene(this);
	}
	for (size_t i = 0; i < m_arrobj.size(); i++) // [TW] ��� �����ε�� ���� ������, �̸� �����ؾ� �Ѵ�.
	{
		m_arrobj[i]->Update();
	}
}

void TaewookScene::LateUpdate()
{
	for (size_t i = 0; i < m_arrobj.size(); i++) // [TW] ��� �����ε�� ���� ������, �̸� �����ؾ� �Ѵ�.
	{
		m_arrobj[i]->LateUpdate();
	}
}
