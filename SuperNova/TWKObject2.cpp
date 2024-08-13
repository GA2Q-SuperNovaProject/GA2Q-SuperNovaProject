#include "TWKObject2.h"
#include "RenderSystem.h"
#include "InputManager.h"
#include "CollisionManager.h"
#include "Debug.h"
#include "EnumDefine.h"
#include "Scene.h"

TWKObject2::TWKObject2(eObjectTag tag, eObjectName name, Transform transform, int imageIndex)
	: GameObject(tag, name, transform, imageIndex)
{

}

TWKObject2::~TWKObject2()
{

}

void TWKObject2::Update()
{
	if (yetToStart)
	{
		twkOne = belongScene->FindObjectByTagInScene(eObjectTag::TWK_OBJECT_ONE);
	}

	if (InputManager::GetInstance().IsKeyPress(VK_W))
	{
		m_pTransform->m_Position.y -= 10.0f;
	}
	if (InputManager::GetInstance().IsKeyPress(VK_S))
	{
		m_pTransform->m_Position.y += 10.0f;
	}

	if (InputManager::GetInstance().IsKeyPress(VK_A))
	{
		m_pTransform->m_Position.x -= 10.0f;
	}
	if (InputManager::GetInstance().IsKeyPress(VK_D))
	{
		m_pTransform->m_Position.x += 10.0f;
	}

	/// Force -> 만드는 예시!
	if (InputManager::GetInstance().IsKeyPress('K'))
	{
		Vec2 tmpForce = Force::AddGravityForce(twkOne, this, 50, 10, 40);
		Vec2 tmpFrictionForce = Force::AddFrictionForce(twkOne, 5);
		AddForce(tmpForce);
		AddForce(tmpFrictionForce);
	}

	
}

void TWKObject2::Render()
{
	RenderSystem::GetInstance().DrawSprite(DEBUG_WOOD, m_pTransform->GetPosition().x, m_pTransform->GetPosition().y, m_pTransform);
	////RenderSystem::GetInstance()
	//RenderSystem::GetInstance().DrawGIF(this->GetImageIndex(), m_pTransform);
}
