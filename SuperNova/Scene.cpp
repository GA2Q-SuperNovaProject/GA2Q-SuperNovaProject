#include "Scene.h"
#include "GameObject.h"
#include "Debug.h"
#include "RenderSystem.h"
#include "CollisionManager.h" //�ݸ��� ���
#include "PhysicsManager.h"
#include "GameManager.h"
#include "Camera.h"
#include "TimeManager.h"
#include <algorithm>
using namespace std;

int Scene::s_m_SceneCount = 0;

Scene::Scene(eSceneName sceneName) : m_name(sceneName)
{
	// ���� ã��
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
	//�ݸ��� ó���� ���� �ʰ� Ȯ���ؼ� üũ�ϴ� ������ �ʿ��ϴ�.
	for (size_t i = 0; i < m_arrobj.size(); i++)
	{
		m_arrobj[i]->LateUpdate();
	}
}


void Scene::ManageCollisions()
{
	//�浹 ������ �ֵ鸸 �и��ؼ� �־���´�.
	for (size_t i = 0; i < m_arrobj.size(); i++)
	{
		if ((m_arrobj[i]->GetPCollider() != nullptr) && (m_arrobj[i]->GetColState() == true))
		{
			///[TW] ���⿡ ���߿� ����ȭ������ �� CameraRect�ȿ� �ִ����� Ȯ���ؾ�
			/// �μ��� ����ٰ� CameraRect �ָ� ���� �� ��: {�߿�}
			/// Collision ������ ������Ʈ�� �ִµ�, CameraRect�� �����ٰ� ����. 
			/// �׷��ٸ�, m_ColQueue�� �״�� ������, ���߿� ū ������ �߻��Ѵ�. 
			/// Reset�� �����ϴ� ������ FixedQueue -> CameraRect�� �������� �ʴµ�, Collider ����?
			/// �׷��ٸ� False�� EnQueue �ϱ�.

			CollisionManager::GetInstance().TakeInCollidableObjects(m_arrobj[i]);
		}
	}

	//�ݶ��̴��� ������Ʈ ��Ų��.
	CollisionManager::GetInstance().UpdateColliders();

	//�ݶ��̴��� ���� ���Ѵ�.
	CollisionManager::GetInstance().CompareColliders(); //�ٸ�, ���� ���� �������� �Ǵ��ؾ�.

	//�ݶ��̴��� ���� Ŭ�����Ѵ�.
	CollisionManager::GetInstance().ClearColliderList();

	//���, �浹�� �Ǿ� �ִ� ��Ȳ���� ������ �Ѵٸ�, �ش� ���°� ��� �����ǰ� ������ ���?
	//�ݸ��� ���ؼ��� ���� ��, ���� ���� �־��µ� ������ ���� ���¸� �����ϰ� ���ָ� �� ��.
	//FixedQueue���� 2���� �о�ֱ�. (false��)
}

void Scene::ManagePhysics()
{
	for (size_t i = 0; i < m_arrobj.size(); i++)
	{
		if ((m_arrobj[i]->GetPBody() != nullptr) && (m_arrobj[i]->GetPhysicsState() == true))
		{
			//���� Body�� ���� ������ ����. 
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

void Scene::AddObject(GameObject* pObject) //���������� ������ ȣ�� ����.
{
	this->m_AddBuffer.push_back(pObject);
}

void Scene::RemoveObject(GameObject* pObject) //���������� ������ ���Ž�ų �� ����.
{
	this->m_RemoveBuffer.push_back(pObject);
}

void Scene::ActuallyActBuffers()
{
	// AddObject �� RemoveObject�� ����ִ°͵��� ���Ѵ�.
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
			playerObject->PutBody(3); //�÷��̾ �������� �ۿ�� �� �ְ�.
			playerObject->SetPhysicsState(true);
		}
		if (playerObject->GetPCollider() == nullptr)
		{
			playerObject->PutCollider(eColType::BOX, IMAGE_PLAYER); //�ݶ��̴� ���� ����
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

// �� ������ ������Ʈ���� �߰��� �� �������
// void Scene::AddObject(GameObject* pObject)
// {
// 	m_arrobj.push_back(pObject);
// }

