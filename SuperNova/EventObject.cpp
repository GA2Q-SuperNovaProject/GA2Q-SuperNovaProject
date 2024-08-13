#include "EventObject.h"
#include "Transform.h"
#include "RenderSystem.h"
#include "Scene.h"
#include "SceneManager.h"
#include "ObjectManager.h"
#include "Camera.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "CollisionManager.h"
#include "Player.h"
#include "GameUI.h"
#include "MouseInputManager.h"
#include "Debug.h"
#include "Transform.h"
#include "GameManager.h"
#include "SoundManager.h"

#include <windows.h>

using namespace std;

EventObject::EventObject(eObjectTag tag, eObjectName name, Transform transform)
	:GameObject(tag, name, transform), m_beginPos(transform.GetPosition()), m_isMusicStart(true), m_isMusicStarted(false)
{
	Sortation();
}

EventObject::~EventObject()
{	
}

void EventObject::Start()
{
	fixedPlayerObject = belongScene->FindObjectInScene(eObjectName::PLAYER);
	
	GameObject* star = belongScene->FindObjectInScene(eObjectName::STAR_PIECE1);
	m_StarPiece1 = static_cast<GameUI*>(star);

	star = belongScene->FindObjectInScene(eObjectName::STAR_PIECE2);
	m_StarPiece2 = static_cast<GameUI*>(star);

	star = belongScene->FindObjectInScene(eObjectName::STAR_PIECE3);
 	m_StarPiece3 = static_cast<GameUI*>(star);
	
	if (m_pCollider != nullptr)
	{
		m_boxCol = static_cast<BoxCollider*>(m_pCollider);
	}
	//m_starList.assign(6, Vec2(0, 0));
}

void EventObject::Update()
{
	if (alreadyStarted)
	{
		m_IceTemp = ObjectManager::GetInstance().FindObjectByName(eObjectName::ICE_PLANET)->GetPTransform()->GetPosition();
		alreadyStarted = false;
	}

	m_pTransform->SetPosition(Camera::GeInstance().WorldToCameraPOINT(m_beginPos));

	PortalEvent();
	StatueEvent();
}

void EventObject::Render()
{
	if (m_DrawGIF)
	{
		switch (m_name)
		{
		case eObjectName::BEAR_STATUE:
			RenderSystem::GetInstance().DrawGIFWithPos(GIF_BEAR_STATUE, m_pTransform->GetPosition().x, m_pTransform->GetPosition().y, this->GetPTransform());
			GameManager::GetInstance().PushStatue(m_name);
			break;

		case eObjectName::BIRD_STATUE:
			RenderSystem::GetInstance().DrawGIFWithPos(GIF_BIRD_STATUE, m_pTransform->GetPosition().x, m_pTransform->GetPosition().y, this->GetPTransform());	
			GameManager::GetInstance().PushStatue(m_name);
			break;

		case eObjectName::DEAR_STATUE:
			RenderSystem::GetInstance().DrawGIFWithPos(GIF_DEAR_STATUE, m_pTransform->GetPosition().x, m_pTransform->GetPosition().y, this->GetPTransform());	
			GameManager::GetInstance().PushStatue(m_name);
			break;

		case eObjectName::WHALE_STATUE:
			RenderSystem::GetInstance().DrawGIFWithPos(GIF_WHALE_STATUE, m_pTransform->GetPosition().x, m_pTransform->GetPosition().y, this->GetPTransform());		
			GameManager::GetInstance().PushStatue(m_name);
			break;

		case eObjectName::GRANDPA_STATUE:
			RenderSystem::GetInstance().DrawGIFWithPos(GIF_GRANDPA_STATUE, m_pTransform->GetPosition().x, m_pTransform->GetPosition().y, this->GetPTransform());
			break;		
		}
	}
	else
	{
		RenderSystem::GetInstance().DrawSprite(m_imageIndex, m_pTransform->GetPosition().x, m_pTransform->GetPosition().y, this->GetPTransform());
		
		if (m_boxCol != nullptr)
		{
			RenderSystem::GetInstance().DrawDebugRect(m_boxCol->GetWorldRect(), eDebugBrush::EDB_RED);
		}
	}

	if (m_starDraw)
	{
		for (int i = 0; i < m_star1Count; i++)
		{
			Transform transStar = Transform(Camera::GeInstance().WorldToCameraPOINT(m_star1List[i]), 0.f, Vec2(0.4f, 0.4f));
			RenderSystem::GetInstance().DrawSprite(IMAGE_STAR_PIECE1, transStar.GetPosition().x, transStar.GetPosition().y, &transStar);
		}		
		
		for (int i = 0; i < m_star2Count; i++)
		{
			Transform transStar = Transform(Camera::GeInstance().WorldToCameraPOINT(m_star2List[i]), 0.f, Vec2(0.4f, 0.4f));
			RenderSystem::GetInstance().DrawSprite(IMAGE_STAR_PIECE2, transStar.GetPosition().x, transStar.GetPosition().y, &transStar);
		}
		
		for (int i = 0; i < m_star3Count; i++)
		{
			Transform transStar = Transform(Camera::GeInstance().WorldToCameraPOINT(m_star3List[i]), 0.f, Vec2(0.4f, 0.4f));
			RenderSystem::GetInstance().DrawSprite(IMAGE_STAR_PIECE3, transStar.GetPosition().x, transStar.GetPosition().y, &transStar);
		}
	}
}

void EventObject::Sortation()
{
	switch (m_name)
	{
	case eObjectName::PORTAL:
		m_imageIndex = IMAGE_PORTAL;
		break;

	case eObjectName::BEAR_STATUE:
		m_imageIndex = IMAGE_BEAR_STATUE;
		break;	
	
	case eObjectName::BIRD_STATUE:
		m_imageIndex = IMAGE_BIRD_STATUE;
		break;	
	
	case eObjectName::DEAR_STATUE:
		m_imageIndex = IMAGE_DEAR_STATUE;
		break;	
	
	case eObjectName::GRANDPA_STATUE:
		m_imageIndex = IMAGE_GRANDPA_STATUE;
		break;	
	
	case eObjectName::WHALE_STATUE:
			m_imageIndex = IMAGE_WHALE_STATUE;
		break;	
	
	case eObjectName::UNDER_STATUE:
		m_imageIndex = IMAGE_UNDER_STATUE;
		break;
	}
}

void EventObject::PortalEvent()
{
	// 밖에 플레이어와 충돌 했다는 조건이 필요	
	if (CollisionManager::GetInstance().CheckCollision(this))
	{
		if (m_pCollider->GetOtherCollidedObject() == fixedPlayerObject)
		{
			switch (belongScene->GetName())
			{
				case eSceneName::STAGE1:
					SceneManager::GetInstance().ChangeScene(eSceneName::SNAKE_PLANET);
					break;

				case eSceneName::STAGE2:
					{
						Vec2 StoryTemp = ObjectManager::GetInstance().FindObjectByName(eObjectName::STORY_PLANET)->GetPTransform()->GetPosition();
						if (StoryTemp.y - m_pTransform->GetPosition().y < 0)
						{
							SceneManager::GetInstance().ChangeScene(eSceneName::STORY_PLANET);
						}
						else
						{
							if (m_isMusicStart)
							{
								SoundManager::PlaySounds(SOUND_PORTAL_TO_SEA);
							}
							SceneManager::GetInstance().ChangeScene(eSceneName::STAGE3);
						}
					}
					break;

				case eSceneName::SNAKE_PLANET:
					SceneManager::GetInstance().ChangeScene(eSceneName::STAGE2);
					break;

				case eSceneName::STORY_PLANET:
					SceneManager::GetInstance().ChangeScene(eSceneName::STAGE2);
					break;
			}
		}
	}
}

void EventObject::StatueEvent()
{
	m_mousePos.x = 0.f;
	m_mousePos.y = 0.f;

	switch (m_name)
	{
		case eObjectName::BEAR_STATUE:
		{		
			if (GameManager::GetInstance().TopStatue() == eObjectName::NONE)
			{
				if (m_EventStart)
				{
					m_star1List.push_back(Vec2(3202, 918));

					m_star2List.push_back(Vec2(3165, 965));
					m_star2List.push_back(Vec2(3245, 855));

					m_star3List.push_back(Vec2(3195, 800));

					m_EventStart = false;
				}

				DragStars();

				if (m_boxCol->GetWorldRect().topLeft.x <= m_mousePos.x && m_boxCol->GetWorldRect().bottomRight.x >= m_mousePos.x
					&& m_boxCol->GetWorldRect().topLeft.y <= m_mousePos.y && m_boxCol->GetWorldRect().bottomRight.y >= m_mousePos.y)
				{
					m_isMusicStart = true;

					switch (m_starImage)
					{
					case IMAGE_STAR_PIECE1:
						m_star1Count++;
						if (m_star1Count >= 1)
						{
							m_star1Count = 1;
						}
						break;

					case IMAGE_STAR_PIECE2:
						m_star2Count++;
						if (m_star2Count >= 2)
						{
							m_star2Count = 2;
						}
						break;

					case IMAGE_STAR_PIECE3:
						m_star3Count++;
						if (m_star3Count >= 1)
						{
							m_star3Count = 1;
						}
						break;
					}
					StarEffectSound(m_starImage);
				}
				else
				{
					m_isMusicStarted = false;
				}

				if (m_star1Count + m_star2Count + m_star3Count >= 4)
				{
					m_starDraw = false;
					m_DrawGIF = true;
				}
			}
		}
		if (m_star1Count + m_star2Count + m_star3Count >= 4)
		{
			m_starDraw = false;
			m_DrawGIF = true;
			m_BearEvent = true;
		}
		break;

		case eObjectName::BIRD_STATUE:
		{
			if (GameManager::GetInstance().TopStatue() == eObjectName::BEAR_STATUE)
			{
				if (TestTime <= 0.f)
				{
					if (belongScene->FindObjectInScene(eObjectName::BEAR_STATUE) != NULL) 
					{
						belongScene->RemoveObject(belongScene->FindObjectInScene(eObjectName::BEAR_STATUE));
					}
				}
				else
				{
					TestTime -= 0.05f;
				}

				if (m_EventStart)
				{
					m_star1List.push_back(Vec2(4818, 425));

					m_star2List.push_back(Vec2(4515, 470));

					m_star3List.push_back(Vec2(4603, 663));
					m_star3List.push_back(Vec2(4780, 708));

					m_EventStart = false;
				}

				DragStars();

				if (m_boxCol->GetWorldRect().topLeft.x <= m_mousePos.x && m_boxCol->GetWorldRect().bottomRight.x >= m_mousePos.x
					&& m_boxCol->GetWorldRect().topLeft.y <= m_mousePos.y && m_boxCol->GetWorldRect().bottomRight.y >= m_mousePos.y)
				{
					m_isMusicStart = true;
					switch (m_starImage)
					{
					case IMAGE_STAR_PIECE1:
						m_star1Count++;
						if (m_star1Count >= 1)
						{
							m_star1Count = 1;
						}
						break;

					case IMAGE_STAR_PIECE2:
						m_star2Count++;
						if (m_star2Count >= 1)
						{
							m_star2Count = 1;
						}
						break;

					case IMAGE_STAR_PIECE3:
						m_star3Count++;
						if (m_star3Count >= 2)
						{
							m_star3Count = 2;
						}
						break;
					}
					StarEffectSound(m_starImage);
				}
				else
				{
					m_isMusicStarted = false;
				}

				if (m_star1Count + m_star2Count + m_star3Count >= 4)
				{
					m_starDraw = false;
					m_DrawGIF = true;
				}
			}
		}
		break;	
		case eObjectName::DEAR_STATUE:
		{
			if (GameManager::GetInstance().TopStatue() == eObjectName::BIRD_STATUE)
			{
				if (TestTime <= 0.f)
				{
					if (belongScene->FindObjectInScene(eObjectName::BIRD_STATUE) != NULL)
					{
						belongScene->RemoveObject(belongScene->FindObjectInScene(eObjectName::BIRD_STATUE));
					}
				}
				else
				{
					TestTime -= 0.069f;
				}

				if (m_EventStart)
				{
					m_star1List.push_back(Vec2(5827, 655));
					m_star1List.push_back(Vec2(5983, 785));

					m_star2List.push_back(Vec2(5820, 855));
					m_star2List.push_back(Vec2(6105, 860));

					m_star3List.push_back(Vec2(5905, 895));

					m_EventStart = false;
				}

				DragStars();

				if (m_boxCol->GetWorldRect().topLeft.x <= m_mousePos.x && m_boxCol->GetWorldRect().bottomRight.x >= m_mousePos.x
					&& m_boxCol->GetWorldRect().topLeft.y <= m_mousePos.y && m_boxCol->GetWorldRect().bottomRight.y >= m_mousePos.y)
				{
					m_isMusicStart = true;
					switch (m_starImage)
					{
					case IMAGE_STAR_PIECE1:
						m_star1Count++;
						if (m_star1Count >= 2)
						{
							m_star1Count = 2;
						}
						break;

					case IMAGE_STAR_PIECE2:
						m_star2Count++;
						if (m_star2Count >= 2)
						{
							m_star2Count = 2;
						}
						break;

					case IMAGE_STAR_PIECE3:
						m_star3Count++;
						if (m_star3Count >= 1)
						{
							m_star3Count = 1;
						}
						break;
					}

					StarEffectSound(m_starImage);
				}
				else
				{
					m_isMusicStarted = false;
				}

				if (m_star1Count + m_star2Count + m_star3Count >= 5)
				{
					m_starDraw = false;
					m_DrawGIF = true;
				}
			}
		}
		if (m_star1Count + m_star2Count + m_star3Count >= 5)
		{
			m_starDraw = false;
			m_DrawGIF = true;
			m_DeerEvent = true;
		}
		break;
		case eObjectName::WHALE_STATUE:
		{
			if (GameManager::GetInstance().TopStatue() == eObjectName::DEAR_STATUE)
			{
				if (TestTime <= 0.f)
				{
					if (belongScene->FindObjectInScene(eObjectName::DEAR_STATUE) != NULL)
					{
						belongScene->RemoveObject(belongScene->FindObjectInScene(eObjectName::DEAR_STATUE));
					}
				}
				else
				{
					TestTime -= 0.075f;
				}

				if (m_EventStart)
				{
					m_star1List.push_back(Vec2(7179, 613));
					m_star1List.push_back(Vec2(7426, 763));

					m_star2List.push_back(Vec2(7250, 555));
					m_star2List.push_back(Vec2(7586, 728));

					m_star3List.push_back(Vec2(7306, 653));
					m_star3List.push_back(Vec2(7426, 763));

					m_EventStart = false;
				}

				DragStars();

				if (m_boxCol->GetWorldRect().topLeft.x <= m_mousePos.x && m_boxCol->GetWorldRect().bottomRight.x >= m_mousePos.x
					&& m_boxCol->GetWorldRect().topLeft.y <= m_mousePos.y && m_boxCol->GetWorldRect().bottomRight.y >= m_mousePos.y)
				{
					m_isMusicStart = true;
					switch (m_starImage)
					{
					case IMAGE_STAR_PIECE1:
						m_star1Count++;
						if (m_star1Count >= 2)
						{
							m_star1Count = 2;
						}
						break;

					case IMAGE_STAR_PIECE2:
						m_star2Count++;
						if (m_star2Count >= 2)
						{
							m_star2Count = 2;
						}
						break;

					case IMAGE_STAR_PIECE3:
						m_star3Count++;
						if (m_star3Count >= 2)
						{
							m_star3Count = 2;
						}
						break;
					}
					StarEffectSound(m_starImage);
				}
				else
				{
					m_isMusicStarted = false;
				}

				if (m_star1Count + m_star2Count + m_star3Count >= 6)
				{
					m_starDraw = false;
					m_DrawGIF = true;
				}
			}
		}
		if (m_star1Count + m_star2Count + m_star3Count >= 6)
		{
			m_starDraw = false;
			m_DrawGIF = true;
			m_WhaleEvent = true;
		}
		break;
		case eObjectName::GRANDPA_STATUE:
		{
			if (GameManager::GetInstance().TopStatue() == eObjectName::WHALE_STATUE)
			{
				if (TestTime <= 0.f)
				{
					if (belongScene->FindObjectInScene(eObjectName::WHALE_STATUE) != NULL)
					{
						belongScene->RemoveObject(belongScene->FindObjectInScene(eObjectName::WHALE_STATUE));
					}
				}
				else
				{
					TestTime -= 0.075f;
				}
				if (m_EventStart)
				{
					m_star1List.push_back(Vec2(8760, 802));
					m_star2List.push_back(Vec2(9143, 844));
					m_star3List.push_back(Vec2(8957, 880));

					m_EventStart = false;
				}

				DragStars();

				if (m_boxCol->GetWorldRect().topLeft.x <= m_mousePos.x && m_boxCol->GetWorldRect().bottomRight.x >= m_mousePos.x
					&& m_boxCol->GetWorldRect().topLeft.y <= m_mousePos.y && m_boxCol->GetWorldRect().bottomRight.y >= m_mousePos.y)
				{
					m_isMusicStart = true;
					switch (m_starImage)
					{
					case IMAGE_STAR_PIECE1:
						m_star1Count++;
						if (m_star1Count >= 1)
						{
							m_star1Count = 1;
						}
						break;

					case IMAGE_STAR_PIECE2:
						m_star2Count++;
						if (m_star2Count >= 1)
						{
							m_star2Count = 1;
						}
						break;

					case IMAGE_STAR_PIECE3:
						m_star3Count++;
						if (m_star3Count >= 1)
						{
							m_star3Count = 1;
						}
						break;
					}
					StarEffectSound(m_starImage);
				}
				else
				{
					m_isMusicStarted = false;
				}

				if (m_star1Count + m_star2Count + m_star3Count >= 3)
				{
					m_starDraw = false;
					m_DrawGIF = true;
				}
			}
		}
		if (m_star1Count + m_star2Count + m_star3Count >= 3)
		{
			m_starDraw = false;
			m_DrawGIF = true;
			m_GrandpaEvent = true;
		}
		break;
	}
}


void EventObject::DragStars()
{
	if (m_StarPiece1->GetStartPiece(eObjectName::STAR_PIECE1))
	{
		m_mousePos = MouseInputManager::GetInstance().GetPos();
		m_starImage = IMAGE_STAR_PIECE1;
		m_starDraw = true;
	}

	if (m_StarPiece2->GetStartPiece(eObjectName::STAR_PIECE2))
	{
		m_mousePos = MouseInputManager::GetInstance().GetPos();
		m_starImage = IMAGE_STAR_PIECE2;
		m_starDraw = true;
	}

	if (m_StarPiece3->GetStartPiece(eObjectName::STAR_PIECE3))
	{
		m_mousePos = MouseInputManager::GetInstance().GetPos();
		m_starImage = IMAGE_STAR_PIECE3;
		m_starDraw = true;
	}
}

void EventObject::StarEffectSound(int starImage)
{
	if (!m_isMusicStarted && m_isMusicStart)
	{
		m_isMusicStarted = true;
		switch (starImage)
		{
			case IMAGE_STAR_PIECE1:
				SoundManager::PlaySounds(SOUND_STAR_PIECE_1);
				m_isMusicStart = false;
				break;

			case IMAGE_STAR_PIECE2:
				SoundManager::PlaySounds(SOUND_STAR_PIECE_2);
				m_isMusicStart = false;
				break;

			case IMAGE_STAR_PIECE3:
				SoundManager::PlaySounds(SOUND_STAR_PIECE_3);
				m_isMusicStart = false;
				break;
		}

	}
}
