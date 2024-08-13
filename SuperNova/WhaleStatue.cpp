#include "WhaleStatue.h"
#include "RenderSystem.h"
#include "Debug.h"
#include "EnumDefine.h"
#include "InputManager.h"
#include "Camera.h"
#include "ObjectManager.h"

using namespace std;

WhaleStatue::WhaleStatue(eObjectTag tag, eObjectName name, Transform transform)
	: GameObject(tag, name, transform), temp(transform.GetPosition())
{
	m_starpiece1 = nullptr;
	m_starpiece2 = nullptr;
	m_starpiece3 = nullptr;
}

WhaleStatue::~WhaleStatue()
{

}

void WhaleStatue::Start()
{
	if (m_starpiece1 == nullptr)
	{
		m_starpiece1 = ObjectManager::GetInstance().FindObjectByName(eObjectName::STAR_PIECE1);
	}
	if (m_starpiece2 == nullptr)
	{
		m_starpiece2 = ObjectManager::GetInstance().FindObjectByName(eObjectName::STAR_PIECE2);
	}
	if (m_starpiece3 == nullptr)
	{
		m_starpiece3 = ObjectManager::GetInstance().FindObjectByName(eObjectName::STAR_PIECE3);
	}
}

void WhaleStatue::Update()
{
	m_pTransform->SetPosition(Camera::GeInstance().WorldToCameraPOINT(temp));

}

void WhaleStatue::Render()
{
	RenderSystem::GetInstance().DrawSprite(m_imageIndex, m_pTransform->GetPosition().x, m_pTransform->GetPosition().y, this->GetPTransform());
}

