#include "Opening_Scene.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "GameObject.h"

Opening_Scene::Opening_Scene(eSceneName sceneName)
	: Scene(sceneName)
{

}

Opening_Scene::~Opening_Scene()
{

}

void Opening_Scene::Update()
{
	for (size_t i = 0; i < m_arrobj.size(); i++)
	{
		m_arrobj[i]->Update();
	}

	if (InputManager::GetInstance().IsKeyDown('P'))
	{
		SceneManager::GetInstance().ChangeScene(eSceneName::STAGE1);
	}
}
