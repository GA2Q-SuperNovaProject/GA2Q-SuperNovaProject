#include "Option_Scene.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "GameObject.h"

Option_Scene::Option_Scene(eSceneName sceneName)
	: Scene(sceneName)
{

}

Option_Scene::~Option_Scene()
{

}

void Option_Scene::Update()
{
	for (size_t i = 0; i < m_arrobj.size(); i++)
	{
		m_arrobj[i]->Update();
	}
}

void Option_Scene::LateUpdate()
{
	for (size_t i = 0; i < m_arrobj.size(); i++)
	{
		m_arrobj[i]->LateUpdate();
	}
}
