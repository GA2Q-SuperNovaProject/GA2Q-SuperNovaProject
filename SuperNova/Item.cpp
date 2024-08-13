#include "Item.h"
#include "Transform.h"
#include "Scene.h"
#include "RenderSystem.h"
#include "ObjectManager.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "CollisionManager.h"
#include "SoundManager.h"
#include "Camera.h"
#include "Player.h"
#include "GameUI.h"


Item::Item(eObjectTag tag, eObjectName name, Transform transform)
	:GameObject(tag, name, transform), m_beginPos(transform.GetPosition()), m_isMusicStart(true)
{
	Sortation();
}

Item::~Item()
{
}

void Item::Start()
{
	m_pPlayer = belongScene->FindObjectInScene(eObjectName::PLAYER);
}

void Item::Update()
{
	//m_PotionTemp = ObjectManager::GetInstance().FindObjectByName(eObjectName::POTION)->GetPTransform()->GetPosition();

	m_pTransform->SetPosition(Camera::GeInstance().WorldToCameraPOINT(m_beginPos));
	m_pRealPlayer = static_cast<Player*>(m_pPlayer);
	if (m_CanCollide == true)
	{
		ItemEvent();
	}
}

void Item::Render()
{
	switch (m_name)
	{
		case eObjectName::STAR_PIECE1:
			if (m_isChecked == false)
			{
				RenderSystem::GetInstance().DrawSprite(m_imageIndex, m_pTransform->GetPosition().x, m_pTransform->GetPosition().y, this->GetPTransform());
			}
			break;

		case eObjectName::STAR_PIECE2:
			if (m_isChecked == false)
			{
				RenderSystem::GetInstance().DrawSprite(m_imageIndex, m_pTransform->GetPosition().x, m_pTransform->GetPosition().y, this->GetPTransform());
			}
			break;

		case eObjectName::STAR_PIECE3:
			if (m_isChecked == false)
			{
				RenderSystem::GetInstance().DrawSprite(m_imageIndex, m_pTransform->GetPosition().x, m_pTransform->GetPosition().y, this->GetPTransform());
			}
			break;

		case eObjectName::GLASS_BOTTLE:
			if (m_isChecked == false)
			{
				RenderSystem::GetInstance().DrawSprite(m_imageIndex, m_pTransform->GetPosition().x, m_pTransform->GetPosition().y, this->GetPTransform());
			}
			break;

		case eObjectName::POTION:
			if (m_isChecked == false)
			{
				RenderSystem::GetInstance().DrawSprite(m_imageIndex, m_pTransform->GetPosition().x, m_pTransform->GetPosition().y, this->GetPTransform());
			}
			break;

		default:
			RenderSystem::GetInstance().DrawSprite(m_imageIndex, m_pTransform->GetPosition().x, m_pTransform->GetPosition().y, this->GetPTransform());
			break;
	}

	//if (m_pCollider != nullptr && m_CanCollide == true)
	//{
	//	BoxCollider* boxCol = static_cast<BoxCollider*>(m_pCollider);
	//	RenderSystem::GetInstance().DrawDebugRect(boxCol->GetWorldRect(), eDebugBrush::EDB_RED);
	//}
}

void Item::Sortation()
{
	switch (m_name)
	{
		case eObjectName::STAR_PIECE1:
			m_imageIndex = IMAGE_STAR_PIECE1;
			break;

		case eObjectName::STAR_PIECE2:
			m_imageIndex = IMAGE_STAR_PIECE2;
			break;

		case eObjectName::STAR_PIECE3:
			m_imageIndex = IMAGE_STAR_PIECE3;
			break;

		case eObjectName::GLASS_BOTTLE:
			m_imageIndex = IMAGE_GLASS_BOTTLE;
			break;

		case eObjectName::POTION:
			m_imageIndex = IMAGE_POTION;
			break;
	}
}

void Item::ItemEvent()
{
	if (CollisionManager::GetInstance().CheckCollision(this))
	{
		if (m_pCollider->GetOtherCollidedObject() == m_pPlayer)
		{
			m_isChecked = true;
			switch (m_name)
			{
				case eObjectName::POTION:
					m_pRealPlayer->m_hpCount++;
					TurnOffCollider();
					break;

				case eObjectName::STAR_PIECE1:
					m_pRealPlayer->m_StarPiece1count1++;
					TurnOffCollider();
					break;

				case eObjectName::STAR_PIECE2:
					m_pRealPlayer->m_StarPiece1count2++;
					TurnOffCollider();
					break;

				case eObjectName::STAR_PIECE3:
					m_pRealPlayer->m_StarPiece1count3++;
					TurnOffCollider();
					break;

				case eObjectName::GLASS_BOTTLE:
					m_pRealPlayer->m_NotePage++;
					TurnOffCollider();
					break;

				default:
					break;
			}
			EffectSound();
		}
	}
}

void Item::EffectSound()
{
	if (m_isMusicStart)
	{
		SoundManager::PlaySounds(SOUND_GET_ITEM);
	}
}

