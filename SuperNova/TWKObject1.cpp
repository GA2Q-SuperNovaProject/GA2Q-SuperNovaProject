#include "TWKObject1.h"
#include "RenderSystem.h"
#include "InputManager.h"
#include "Debug.h"
#include "GameObject.h"
#include "Scene.h"

TWKObject1::TWKObject1(eObjectTag tag, eObjectName name, Transform transform, int imageIndex)
	: GameObject(tag, name, transform, imageIndex)
{

}

TWKObject1::~TWKObject1()
{

}

void TWKObject1::Start()
{
	twkTwo = belongScene->FindObjectByTagInScene(eObjectTag::TWK_OBJECT_TWO);
}
void TWKObject1::Update()
{
	//GameObject* twkTwo = belongScene->FindObjectInScene(DEBUG_)
	
}

void TWKObject1::Render()
{
	RenderSystem::GetInstance().DrawSprite(DEBUG_BRICK, m_pTransform->GetPosition().x, m_pTransform->GetPosition().y, m_pTransform);

}
