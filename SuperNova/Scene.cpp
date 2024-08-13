#include "Scene.h"
#include "GameObject.h"
#include "Debug.h"
#include "RenderSystem.h"
#include "CollisionManager.h" //콜리젼 담당
#include "PhysicsManager.h"
#include "GameManager.h"
#include "Camera.h"
#include "TimeManager.h"
#include <algorithm>
using namespace std;

int Scene::s_m_SceneCount = 0;

Scene::Scene(eSceneName sceneName) : m_name(sceneName)
{
	// 문제 찾기
	// this->m_Index(s_m_SceneCount);
	m_Index = s_m_SceneCount;
	s_m_SceneCount++;

	FrontRenderArray.reserve(100);
}

Scene::~Scene()
{

}

void Scene::Initialize()
{

}

void Scene::Update()
{
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

void Scene::LateUpdate()
{
	//콜리젼 처리를 위해 늦게 확인해서 체크하는 로직이 필요하다.
	for (size_t i = 0; i < m_arrobj.size(); i++)
	{
		m_arrobj[i]->LateUpdate();
	}
}


void Scene::ManageCollisions()
{
	//충돌 가능한 애들만 분리해서 넣어놓는다.
	for (size_t i = 0; i < m_arrobj.size(); i++)
	{
		if ((m_arrobj[i]->GetPCollider() != nullptr) && (m_arrobj[i]->GetColState() == true))
		{
			///[TW] 여기에 나중에 최적화용으로 현 CameraRect안에 있는지를 확인해야
			/// 민서가 여기다가 CameraRect 주면 내가 할 것: {중요}
			/// Collision 가능한 오브젝트가 있는데, CameraRect에 나갔다고 하자. 
			/// 그렇다면, m_ColQueue는 그대로 유지됨, 나중에 큰 오차가 발생한다. 
			/// Reset을 강요하는 느낌의 FixedQueue -> CameraRect에 속해있지 않는데, Collider 켜짐?
			/// 그렇다면 False를 EnQueue 하기.

			CollisionManager::GetInstance().TakeInCollidableObjects(m_arrobj[i]);
		}
	}

	//콜라이더를 업데이트 시킨다.
	CollisionManager::GetInstance().UpdateColliders();

	//콜라이더를 서로 비교한다.
	CollisionManager::GetInstance().CompareColliders(); //다만, 여기 내부 로직에서 판단해야.

	//콜라이더를 서로 클리어한다.
	CollisionManager::GetInstance().ClearColliderList();

	//잠깐만, 충돌이 되어 있는 상황으로 생각을 한다면, 해당 상태가 계속 유지되고 있으면 어떡함?
	//콜리젼 디텍션을 했을 때, 원래 켜져 있었는데 꺼지면 내부 상태를 리셋하게 해주면 될 것.
	//FixedQueue에서 2개를 밀어넣기. (false로)
}

void Scene::ManagePhysics()
{
	for (size_t i = 0; i < m_arrobj.size(); i++)
	{
		if ((m_arrobj[i]->GetPBody() != nullptr) && (m_arrobj[i]->GetPhysicsState() == true))
		{
			//이제 Body의 내부 로직을 설정. 
			PhysicsManager::GetInstance().TakeInBodies(m_arrobj[i]);
		}
	}
	PhysicsManager::GetInstance().ApplyForceToBodies();
	PhysicsManager::GetInstance().ClearBodiesInVector();
}

void Scene::Render()
{
	// Range-Based for
	RenderSystem::GetInstance().BeginRender();
	for (GameObject* pObject : m_arrobj)
	{
		if (pObject->isfrontRender == true)
		{
			FrontRenderArray.push_back(pObject);
		}
		else
		{
			pObject->Render();
		}
	}
	for (auto it : FrontRenderArray)
	{
		it->Render();
	}
	FrontRenderArray.clear();

	RenderSystem::GetInstance().EndRender();

}

void Scene::AddObject(GameObject* pObject) //개별적으로 옵젝이 호출 가능.
{
	this->m_AddBuffer.push_back(pObject);
}

void Scene::RemoveObject(GameObject* pObject) //개별적으로 옵젝이 제거시킬 수 있음.
{
	this->m_RemoveBuffer.push_back(pObject);
}

void Scene::ActuallyActBuffers()
{
	// AddObject 와 RemoveObject에 들어있는것들을 행한다.
	for (auto it : m_AddBuffer)
	{
		m_arrobj.push_back(it);
	}

	for (auto itter : m_arrobj)
	{
		for (auto it : m_RemoveBuffer)
		{
			if (itter->GetName() == it->GetName())
			{
				auto ex = std::find(m_arrobj.begin(), m_arrobj.end(), itter);
				if (ex != m_arrobj.end())
				{
					m_arrobj.erase(ex);
				}
			}
		}
	}
}

void Scene::ClearBuffers()
{
	m_AddBuffer.clear();
	m_RemoveBuffer.clear();
}

void Scene::Finalize()
{
	//
}

GameObject* Scene::FindObjectInScene(eObjectName objectName)
{
	GameObject* tmp = nullptr;
	for (auto it : m_arrobj)
	{
		if (it->GetName() == objectName)
		{
			tmp = it;
			break;
		}
	}
	return tmp;
}

GameObject* Scene::FindObjectByTagInScene(eObjectTag objecttag)
{
	GameObject* tmp = nullptr;
	for (auto it : m_arrobj)
	{
		if (it->GetTag() == objecttag)
		{
			tmp = it;
			break;
		}
	}
	return tmp;
}

void Scene::FadeIn()
{
	Vec2 prePosition = Vec2(960, 540);
	//prePosition = Camera::GeInstance().CameraToWorldPOINT(prePosition);
	Transform transform(prePosition, 0.0f, Vec2(1, 1));
	RenderSystem::GetInstance().DrawGIF(GIF_FADEIN, &transform);
}

void Scene::FadeOut()
{
	Vec2 prePosition = Vec2(960, 540);
	//prePosition = Camera::GeInstance().CameraToWorldPOINT(prePosition);
	Transform transform(prePosition, 0.0f, Vec2(1, 1));
	RenderSystem::GetInstance().DrawGIF(GIF_FADEOUT, &transform);
}

void Scene::UpdatePlayerObject(eSceneName sceneName)
{
	GameObject* playerObject = nullptr;
	for (auto it : m_arrobj)
	{
		it->fixedPlayerObject = nullptr;
	}
	if (this->FindObjectInScene(eObjectName::PLAYER) != nullptr)
	{
		playerObject = this->FindObjectInScene(eObjectName::PLAYER);
		if (playerObject->GetPBody() == nullptr)
		{
			playerObject->PutBody(3); //플레이어에 물리력이 작용될 수 있게.
			playerObject->SetPhysicsState(true);
		}
		if (playerObject->GetPCollider() == nullptr)
		{
			playerObject->PutCollider(eColType::BOX, IMAGE_PLAYER); //콜라이더 넣은 거임
			playerObject->SetColState(true);
		}
	}

	if (playerObject != nullptr)
	{
		if (playerObject->GetPBody() != nullptr)
		{
			playerObject->GetPBody()->velocity = Vec2(0, 0);
			playerObject->GetPBody()->acceleration = Vec2(0, 0);
		}
	}

	for (auto it : m_arrobj)
	{
		it->fixedPlayerObject = playerObject;
	}
}

// 각 씬들이 오브젝트들을 추가할 때 사용하자
// void Scene::AddObject(GameObject* pObject)
// {
// 	m_arrobj.push_back(pObject);
// }

