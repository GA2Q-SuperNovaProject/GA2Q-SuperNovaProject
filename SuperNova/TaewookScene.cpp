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
	for (size_t i = 0; i < m_arrobj.size(); i++) // [TW] 모든 오버로드된 씬이 있으면, 이를 수행해야 한다.
	{
		m_arrobj[i]->Update();
	}
}

void TaewookScene::LateUpdate()
{
	for (size_t i = 0; i < m_arrobj.size(); i++) // [TW] 모든 오버로드된 씬이 있으면, 이를 수행해야 한다.
	{
		m_arrobj[i]->LateUpdate();
	}
}
