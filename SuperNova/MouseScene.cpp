#include "MouseScene.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "GameObject.h"

MouseScene::MouseScene(eSceneName sceneName)
	: Scene(sceneName)
{
	//
}

MouseScene::~MouseScene()
{
	//
}

void MouseScene::Update()
{

	if (this->m_SceneStartFlag == true)
	{
		for (size_t i = 0; i < m_arrobj.size(); i++)
		{
			m_arrobj[i]->Start();
		}
		m_SceneStartFlag = false;
	}

	if (InputManager::GetInstance().IsKeyDown('1')
		|| InputManager::GetInstance().IsKeyPress('1'))
	{
		SceneManager::GetInstance().ChangeScene(eSceneName::MAIN);
	}

	if (InputManager::GetInstance().IsKeyDown('2')
		|| InputManager::GetInstance().IsKeyPress('2'))
	{
		SceneManager::GetInstance().ChangeScene(eSceneName::STAGE1);
	}

	for (size_t i = 0; i < m_arrobj.size(); i++)
	{
		m_arrobj[i]->Update();
	}


}
