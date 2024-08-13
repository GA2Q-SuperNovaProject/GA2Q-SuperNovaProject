#include "SceneManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "ObjectManager.h"
#include "Camera.h"
#include "Debug.h"
#include "RenderSystem.h"
#include "GameManager.h"
#include "BulletManager.h"

/// [TW] SceneHeaderIncludes.h에서는 Scene들이 추가되면서 
/// 생겨나는 개별적인 파생 Scene들의 헤더를 담고 있다.
#include "SceneHeaderIncludes.h"

using namespace std;

SceneManager::SceneManager() : sceneHistory(2)
{
	// 생성자
}

SceneManager::~SceneManager()
{
	for (auto it : m_SceneList)
	{
		if (it != nullptr)
		{
			delete it;
		}
	}
}

void SceneManager::SceneLoop()
{
	CheckForSceneChange();
	ActBuffers();
	ClearBuffers();
	ManageCollisions();
	Update(); //[TW] 업데이트에서 힘을 가하고, 
	ManagePhysics(); //여기서 처리함.
	LateUpdate();
	Render();

}

void SceneManager::ActuallyChangeScene(eSceneName sceneName)
{
	for (auto it : m_SceneList)
	{
		if (it->GetName() == sceneName)
		{
			m_pCurScene->SetActive(false);
			m_pCurScene->m_SceneStartFlag = false;

			m_pCurScene = it;
			m_pCurScene->SetActive(true);
			m_pCurScene->m_SceneStartFlag = true;
		}
	}
}

void SceneManager::ActuallyChangeSceneWithObject(eSceneName sceneName, GameObject* gameObject)
{
	for (auto it : m_SceneList)
	{
		if (it->GetName() == sceneName)
		{
			m_pCurScene->SetActive(false);
			m_pCurScene->m_SceneStartFlag = false;
			m_pCurScene->RemoveObject(gameObject);
			m_pCurScene = it;
			m_pCurScene->SetActive(true);
			m_pCurScene->m_SceneStartFlag = true;
			m_pCurScene->AddObject(gameObject);
		}
	}
	
}

void SceneManager::CheckForSceneChange()
{
	bool sceneSwitch_Toggle = false;
	if (Debug::GetCanDebug())
	{
		Debug::SetCanDebug(false);
		sceneSwitch_Toggle = true;
	}

	if (toChangeScene != eSceneName::NONE)
	{
		if (gameObjectToAddNext == nullptr)
		{
			ActuallyChangeScene(toChangeScene); 
			UpdatePlayerObject(toChangeScene);
			BulletManager::GetInstance().StartBulletManager(toChangeScene);
			sceneHistory.Enqueue(toChangeScene);
		}
		else
		{
			ActuallyChangeSceneWithObject(toChangeScene, gameObjectToAddNext);
			UpdatePlayerObject(toChangeScene);
			BulletManager::GetInstance().StartBulletManager(toChangeScene);
			sceneHistory.Enqueue(toChangeScene);
		}
		Camera::GeInstance().PlayerInit();
	}

	//원래대로 돌려놓기.
	toChangeScene = eSceneName::NONE;
	gameObjectToAddNext = nullptr;
	
	if (sceneSwitch_Toggle)
	{
		Debug::SetCanDebug(true);
		sceneSwitch_Toggle = false;
	}
}

void SceneManager::UpdatePlayerObject(eSceneName sceneName)
{
	for (auto it : m_SceneList)
	{
		if (it->GetName() == sceneName)
		{
			it->UpdatePlayerObject(sceneName);
		}
	}
}

void SceneManager::GameSetup()
{

}

void SceneManager::PutObjectInScene(Scene* scene, GameObject* obj)
{
	obj->belongScene = scene;
	scene->AddObject(obj);
}

//씬ChangeScene; //직접적으로 호출하면 안된다.

void SceneManager::ChangeScene(eSceneName name)
{
	toChangeScene = name;

	GameManager::GetInstance().m_ChangeSceneOn = true;	// 씬을 바꿔주는 타이밍에 페이드인/아웃 변수
	GameManager::GetInstance().transitionStartTime = std::chrono::steady_clock::now();
}

void SceneManager::ChangeSceneWithObject(eSceneName sceneName, GameObject* gameObject)
{
	toChangeScene = sceneName;
	gameObjectToAddNext = gameObject;

	GameManager::GetInstance().m_ChangeSceneOn = true;	// 씬을 바꿔주는 타이밍에 페이드인/아웃 변수
	GameManager::GetInstance().transitionStartTime = std::chrono::steady_clock::now();

}

Scene* SceneManager::GetCurScene()
{
	return m_pCurScene;
}

void SceneManager::SetCurScene(Scene* scene)
{
	m_pCurScene = scene;
	GameManager::GetInstance().m_ChangeSceneOn = true;
}

void SceneManager::SetSceneActive(Scene* scene, bool _bool)
{
	scene->SetActive(_bool);
	scene->m_SceneStartFlag = _bool;

}

Scene* SceneManager::FindSceneByName(eSceneName name)
{
	for (auto it : m_SceneList)
	{
		if (it->GetName() == name)
		{
			return it;
		}
	}
}

void SceneManager::ActBuffers()
{
	for (auto it : m_SceneList)
	{
		it->ActuallyActBuffers();
	}
}

void SceneManager::ClearBuffers()
{
	for (auto it : m_SceneList)
	{
		it->ClearBuffers();
	}
}

void SceneManager::Update()
{
	Camera::GeInstance().Update();

	//for (auto it : m_SceneList)
	//{
	//	if (it->GetActive())
	//	{
			//it->LateUpdate();
	//	}
	//}

	GetCurScene()->Update();
}

void SceneManager::LateUpdate()
{
	//for (auto it : m_SceneList)
	//{
	//	if (it->GetActive())
	//	{
	//		it->LateUpdate(); //내부적으로 Object 단위에서 LateUpdate() 실행시켜줘야
	//	}
	//}
	GetCurScene()->LateUpdate();
}

void SceneManager::ManageCollisions()
{
	//for (auto it : m_SceneList)
	//{
	//	if (it->GetActive() && it == m_pCurScene)
	//	{
	//		//인게임 오브젝트들을 접할 수 있다.
	//		it->ManageCollisions();
	//	}
	//}
	GetCurScene()->ManageCollisions();
}

void SceneManager::ManagePhysics()
{
	//for (auto it : m_SceneList)
	//{
	//	if (it->GetActive() && it == m_pCurScene)
	//	{
	//		//인게임 오브젝트들을 접할 수 있다.
	//		it->ManagePhysics();
	//	}
	//}

	GetCurScene()->ManagePhysics();
}

void SceneManager::Render()
{
	for (auto it : m_SceneList)
	{
		if (it->GetActive() && it == m_pCurScene)
		{
			it->Render();
		}
	}
}


void SceneManager::FadeIn()
{
	for (auto it : m_SceneList)
	{
		if (it->GetActive() && it == m_pCurScene)
		{
			it->FadeIn();
		}
	}
}

void SceneManager::FadeOut()
{
	for (auto it : m_SceneList)
	{
		if (it->GetActive() && it == m_pCurScene)
		{
			it->FadeOut();
		}
	}
}

Scene* SceneManager::CreateScene(eSceneName name)
{
	Scene* tmpScene = nullptr;
	switch (name)
	{
	case eSceneName::MAIN:
		tmpScene = new Main_Scene(name);
		this->m_SceneList.push_back(tmpScene);
		break;	
	
	case eSceneName::MAIN_OPTION:
		tmpScene = new Option_Scene(name);
		this->m_SceneList.push_back(tmpScene);
		break;

	case eSceneName::STAGE1:
		tmpScene = new Stage1(name);
		this->m_SceneList.push_back(tmpScene);
		break;	
	
	case eSceneName::STAGE2:
		tmpScene = new Stage2(name);
		this->m_SceneList.push_back(tmpScene);
		break;	
	
	case eSceneName::STAGE3:
		tmpScene = new Stage3(name);
		this->m_SceneList.push_back(tmpScene);
		break;	
	
	case eSceneName::SNAKE_PLANET:
		tmpScene = new SnakePlanetScene(name);
		this->m_SceneList.push_back(tmpScene);
		break;	

	case eSceneName::STORY_PLANET:
		tmpScene = new StoryPlanetScene(name);
		this->m_SceneList.push_back(tmpScene);
		break;

	case eSceneName::OPENING:
		tmpScene = new Opening_Scene(name);
		this->m_SceneList.push_back(tmpScene);
		break;

	case eSceneName::NORMAL_ENDING:
		tmpScene = new Normal_Scene(name);
		this->m_SceneList.push_back(tmpScene);
		break;

	case eSceneName::BAD_ENDING:
		tmpScene = new Bad_Scene(name);
		this->m_SceneList.push_back(tmpScene);
		break;

	case eSceneName::TRUE_ENDING:
		tmpScene = new True_Scene(name);
		this->m_SceneList.push_back(tmpScene);
		break;
	}
	return tmpScene;
}
