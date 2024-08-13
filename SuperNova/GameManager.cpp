#include "GameManager.h"
#include "InputManager.h"
#include "MouseInputManager.h"
#include "Debug.h"
#include "RenderSystem.h"
#include "Camera.h"
#include "Vec2.h"
#include "Transform.h"
#include "SceneManager.h"
#include "Scene.h"

//단일 업데이트, 매뉴얼 체크. 
void GameManager::Update()
{
	tmpCntTime = std::chrono::steady_clock::now();
	
	if (InputManager::GetInstance().IsKeyDown('T'))
	{
		static bool toggleDebug = false;
		toggleDebug = !toggleDebug;
		Debug::SetCanDebug(toggleDebug);
	}

	if (InputManager::GetInstance().IsKeyDown('Y'))
	{
		Scene* sc = SceneManager::GetInstance().GetCurScene();
		GameObject* ga = sc->FindObjectInScene(eObjectName::PLAYER);
		if (ga == nullptr)
		{
			SceneManager::GetInstance().ChangeScene(eSceneName::MAIN);
		}
		else
		{
			SceneManager::GetInstance().ChangeSceneWithObject(eSceneName::MAIN,ga);
		}
	}

	if (InputManager::GetInstance().IsKeyDown('U'))
	{
		Scene* sc = SceneManager::GetInstance().GetCurScene();
		GameObject* ga = sc->FindObjectInScene(eObjectName::PLAYER);
		if (ga == nullptr)
		{
			SceneManager::GetInstance().ChangeScene(eSceneName::MAIN_OPTION);
		}
		else
		{
			SceneManager::GetInstance().ChangeSceneWithObject(eSceneName::MAIN_OPTION, ga);
		}
	}

	if (InputManager::GetInstance().IsKeyDown('I'))
	{
		Scene* sc = SceneManager::GetInstance().GetCurScene();
		GameObject* ga = sc->FindObjectInScene(eObjectName::PLAYER);
		if (ga == nullptr)
		{
			SceneManager::GetInstance().ChangeScene(eSceneName::STAGE1);
		}
		else
		{
			SceneManager::GetInstance().ChangeSceneWithObject(eSceneName::STAGE1, ga);
		}
	}

	if (InputManager::GetInstance().IsKeyDown('O'))
	{
		Scene* sc = SceneManager::GetInstance().GetCurScene();
		GameObject* ga = sc->FindObjectInScene(eObjectName::PLAYER);
		if (ga == nullptr)
		{
			SceneManager::GetInstance().ChangeScene(eSceneName::STAGE2);
		}
		else
		{
			SceneManager::GetInstance().ChangeSceneWithObject(eSceneName::STAGE2, ga);
		}
	}
	if (InputManager::GetInstance().IsKeyDown('P'))
	{
		Scene* sc = SceneManager::GetInstance().GetCurScene();
		GameObject* ga = sc->FindObjectInScene(eObjectName::PLAYER);
		if (ga == nullptr)
		{
			SceneManager::GetInstance().ChangeScene(eSceneName::STAGE3);
		}
		else
		{
			SceneManager::GetInstance().ChangeSceneWithObject(eSceneName::STAGE3, ga);
		}
	}

	if (InputManager::GetInstance().IsKeyDown('H'))
	{
		Scene* sc = SceneManager::GetInstance().GetCurScene();
		GameObject* ga = sc->FindObjectInScene(eObjectName::PLAYER);
		if (ga == nullptr)
		{
			SceneManager::GetInstance().ChangeScene(eSceneName::SNAKE_PLANET);
		}
		else
		{
			SceneManager::GetInstance().ChangeSceneWithObject(eSceneName::SNAKE_PLANET, ga);
		}
	}

	if (InputManager::GetInstance().IsKeyDown('J'))
	{
		Scene* sc = SceneManager::GetInstance().GetCurScene();
		GameObject* ga = sc->FindObjectInScene(eObjectName::PLAYER);
		if (ga == nullptr)
		{
			SceneManager::GetInstance().ChangeScene(eSceneName::STORY_PLANET);
		}
		else
		{
			SceneManager::GetInstance().ChangeSceneWithObject(eSceneName::STORY_PLANET, ga);
		}
	}

	if (InputManager::GetInstance().IsKeyDown('K'))
	{
		Scene* sc = SceneManager::GetInstance().GetCurScene();
		GameObject* ga = sc->FindObjectInScene(eObjectName::PLAYER);
		if (ga == nullptr)
		{
			SceneManager::GetInstance().ChangeScene(eSceneName::OPENING);
		}
		else
		{
			SceneManager::GetInstance().ChangeSceneWithObject(eSceneName::OPENING, ga);
		}
	}


	if (InputManager::GetInstance().IsKeyDown('L'))
	{
		Scene* sc = SceneManager::GetInstance().GetCurScene();
		GameObject* ga = sc->FindObjectInScene(eObjectName::PLAYER);
		if (ga == nullptr)
		{
			SceneManager::GetInstance().ChangeScene(eSceneName::NORMAL_ENDING);
		}
		else
		{
			SceneManager::GetInstance().ChangeSceneWithObject(eSceneName::NORMAL_ENDING, ga);
		}
	}

	if (InputManager::GetInstance().IsKeyDown('B'))
	{
		Scene* sc = SceneManager::GetInstance().GetCurScene();
		GameObject* ga = sc->FindObjectInScene(eObjectName::PLAYER);
		if (ga == nullptr)
		{
			SceneManager::GetInstance().ChangeScene(eSceneName::BAD_ENDING);
		}
		else
		{
			SceneManager::GetInstance().ChangeSceneWithObject(eSceneName::BAD_ENDING, ga);
		}
	}

	if (InputManager::GetInstance().IsKeyDown('N'))
	{
		Scene* sc = SceneManager::GetInstance().GetCurScene();
		GameObject* ga = sc->FindObjectInScene(eObjectName::PLAYER);
		if (ga == nullptr)
		{
			SceneManager::GetInstance().ChangeScene(eSceneName::TRUE_ENDING);
		}
		else
		{
			SceneManager::GetInstance().ChangeSceneWithObject(eSceneName::TRUE_ENDING, ga);
		}
	}


	//KILL OBJECT
	if (InputManager::GetInstance().IsKeyDown(VK_F9))
	{
		Scene* sc = SceneManager::GetInstance().GetCurScene();
		GameObject* ga = sc->FindObjectInScene(eObjectName::PLAYER);
		if (ga != nullptr)
		{
			sc->RemoveObject(ga);
		}
	}

	
}

void GameManager::Render()
{

}

void GameManager::PushStatue(eObjectName objName)
{
	m_seqStack.push(objName);
}

eObjectName GameManager::TopStatue()
{
	if (m_seqStack.empty())
	{
		return eObjectName::NONE;
	}

	return m_seqStack.top();
}

GameManager::GameManager()
{

}

GameManager::~GameManager()
{

}

void GameManager::FadeIn()
{
	Vec2 prePosition = Vec2(960, 540);
	prePosition = Camera::GeInstance().CameraToWorldPOINT(prePosition);
	Transform transform(prePosition, 0.0f, Vec2(1, 1));
	RenderSystem::GetInstance().DrawGIF(GIF_FADEIN, &transform);
}

void GameManager::FadeOut()
{
	Vec2 prePosition = Vec2(960, 540);
	prePosition = Camera::GeInstance().CameraToWorldPOINT(prePosition);
	Transform transform(prePosition, 0.0f, Vec2(1, 1));
	RenderSystem::GetInstance().DrawGIF(GIF_FADEOUT, &transform);
}