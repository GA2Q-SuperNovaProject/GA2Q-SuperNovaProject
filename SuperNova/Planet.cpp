#include "Planet.h"
#include "RenderSystem.h"
#include "EnumDefine.h"
#include "InputManager.h"
#include "Camera.h"
#include "Scene.h"
#include "Collider.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "CollisionManager.h"	
#include "SceneManager.h"	
#include "Force.h"
#include "Body.h"
#include "Player.h"

using namespace std;

//Layer3이 가장 멀고, Layer1이 가장 가까움.
const int LAYER3_DISTANCE = 1000000;
const int LAYER2_DISTANCE = 500000;
const int LAYER1_DISTANCE = 250000;

const int LAYER3_PULLPOWER = 300;
const int LAYER2_PULLPOWER = 500;
const int LAYER1_PULLPOWER = 1000;

Planet::Planet(eObjectTag tag, eObjectName name, Transform transform)
	: GameObject(tag, name, transform), m_beginPos(transform.GetPosition())
{
	Sortation();
}

Planet::~Planet()
{

}

void Planet::Start()
{
	if (fixedPlayerObject == nullptr)
	{
		fixedPlayerObject = belongScene->FindObjectInScene(eObjectName::PLAYER);
	}
}

void Planet::Update()
{
	if (belongScene->GetName() == eSceneName::STAGE1 ||
		belongScene->GetName() == eSceneName::STAGE2)
	{
		MeasurePlayerDistance();
		GravitationalPull();
		PlanetCrashEvent();
	}


	switch (belongScene->GetName())
	{
		case eSceneName::SNAKE_PLANET:
		case eSceneName::STORY_PLANET:
			if (InputManager::GetInstance().IsKeyPress('D'))
			{
				m_pTransform->m_Rotation -= 1.0f;
			}
			break;

		default:
			m_pTransform->SetPosition(Camera::GeInstance().WorldToCameraPOINT(m_beginPos));
			break;
	}


}

void Planet::Render()
{
	RenderSystem::GetInstance().DrawSprite(m_imageIndex, m_pTransform->GetPosition().x, m_pTransform->GetPosition().y, this->GetPTransform());

	if (belongScene->GetName() == eSceneName::SNAKE_PLANET ||
		belongScene->GetName() == eSceneName::STORY_PLANET)
	{
		part1 = false;
		part2 = false;
		part3 = false;
		hardToggle = false;
		if (m_pTransform->GetRotation() > -20)
		{
			RenderSystem::GetInstance().DrawSprite(IMAGE_STAR_PIECE1, 1200, 400, this->GetPTransform());
			part1 = false;
		}
		else
		{
			part1 = true;
		}

		if (m_pTransform->GetRotation() > -45)
		{
			RenderSystem::GetInstance().DrawSprite(IMAGE_STAR_PIECE2, 1500, 700, this->GetPTransform());
			part2 = false;
		}
		else
		{
			part2 = true;
		}

		if (m_pTransform->GetRotation() > -75)
		{
			RenderSystem::GetInstance().DrawSprite(IMAGE_STAR_PIECE3, 1600, 900, this->GetPTransform());
			part3 = false;
		}
		else
		{
			part3 = true;
		}

		playerPointer = static_cast<Player*>(fixedPlayerObject);

		if (m_pTransform->GetRotation() > -100)
		{
			RenderSystem::GetInstance().DrawSprite(IMAGE_GLASS_BOTTLE, 1750, 1200, this->GetPTransform());
		}

		if (part1 && part2 && part3)
		{
			eSceneName tmp = SceneManager::GetInstance().sceneHistory.ContentOfIndex(1);
			SceneManager::GetInstance().ChangeScene(tmp);
			Scene* actScene = SceneManager::GetInstance().FindSceneByName(tmp);
			GameObject* go = actScene->FindObjectInScene(eObjectName::PLAYER);
			Player* pl = static_cast<Player*>(go);
			pl->m_StarPiece1count1++;
			pl->m_StarPiece1count2++;
			pl->m_StarPiece1count3++;

			go->GetPTransform()->m_Position.x += 500.0f;
			go->GetPTransform()->m_Position.y += 500.0f;

			RenderSystem::GetInstance().DrawSprite(IMAGE_PORTAL, -80, 500, this->GetPTransform());
		}
	}
	//BoxCollider* boxCol = static_cast<BoxCollider*>(m_pCollider);
	//RenderSystem::GetInstance().DrawDebugRect(boxCol->GetWorldRect(), eDebugBrush::EDB_RED);
}

void Planet::Sortation()
{
	switch (m_name)
	{
		case eObjectName::ICE_PLANET:
			m_imageIndex = IMAGE_ICE_PLANET;
			break;

		case eObjectName::LAVA_PLANET:
			m_imageIndex = IMAGE_LAVA_PLANET;
			break;

		case eObjectName::SNAKE_PLANET:
			m_imageIndex = IMAGE_SNAKE_PLANET;
			break;

		case eObjectName::STORY_PLANET:
			m_imageIndex = IMAGE_STORY_PLANET;
			break;
	}
}

void Planet::GravitationalPull()
{

	//2이니, MagnitudeSquared를 환산해서 계산해보자.
	//40000 // 160000 // 360000
	if (m_distPlayerPow < LAYER3_DISTANCE && m_distPlayerPow >= LAYER2_DISTANCE)
	{
		//Vec2 pullForce = Force::AddGravityForce(m_pPlayer, this, 5, 10, 40);
		Vec2 playerPrePos = (fixedPlayerObject->GetPTransform()->GetPosition());
		Vec2 planetPrePos = (this->GetPTransform()->GetPosition());
		planetPrePos = Camera::GeInstance().CameraToWorldPOINT(planetPrePos);
		Vec2 pullDir = planetPrePos - playerPrePos;
		pullDir.Normalize();
		fixedPlayerObject->AddForce(pullDir * LAYER3_PULLPOWER);
	}
	else if (m_distPlayerPow < LAYER2_DISTANCE && m_distPlayerPow >= LAYER1_DISTANCE)
	{
		//Vec2 pullForce = Force::AddGravityForce(m_pPlayer, this, 5, 10, 40);
		Vec2 playerPrePos = (fixedPlayerObject->GetPTransform()->GetPosition());
		Vec2 planetPrePos = (this->GetPTransform()->GetPosition());
		planetPrePos = Camera::GeInstance().CameraToWorldPOINT(planetPrePos);
		Vec2 pullDir = planetPrePos - playerPrePos;
		pullDir.Normalize();
		fixedPlayerObject->AddForce(pullDir * LAYER2_PULLPOWER);
	}
	else if (m_distPlayerPow < LAYER1_DISTANCE)
	{
		//Vec2 pullForce = Force::AddGravityForce(m_pPlayer, this, 5, 10, 40);
		Vec2 playerPrePos = (fixedPlayerObject->GetPTransform()->GetPosition());
		Vec2 planetPrePos = (this->GetPTransform()->GetPosition());
		planetPrePos = Camera::GeInstance().CameraToWorldPOINT(planetPrePos);
		Vec2 pullDir = planetPrePos - playerPrePos;
		pullDir.Normalize();
		fixedPlayerObject->AddForce(pullDir * LAYER1_PULLPOWER);
	}
}

void Planet::PlanetCrashEvent()
{
	if (CollisionManager::GetInstance().CheckCollision(this))
	{
		if (m_pCollider->GetOtherCollidedObject() == fixedPlayerObject)
		{
			if (isInvinc == false)
			{
				Player* tmpPlayer = static_cast<Player*>(fixedPlayerObject);
				tmpPlayer->m_hpCount--;
				invinStartTime = std::chrono::steady_clock::now();
				isInvinc = true;
				//Debug::Trace("INVIS START");
			}

		}
	}

	if (isInvinc == true)
	{
		invinRecordTime = std::chrono::steady_clock::now();
		std::chrono::duration<double, std::milli> dura = invinRecordTime - invinStartTime;

		//무적 타임 세팅.
		if (dura.count() >= 2000)
		{
			isInvinc = false;
			//Debug::Trace("INVIS END");
		}
	}
}

void Planet::MeasurePlayerDistance()
{
	Vec2 planetPrePos = (this->GetPTransform()->GetPosition());
	planetPrePos = Camera::GeInstance().CameraToWorldPOINT(planetPrePos);
	Vec2 distPlayer = (fixedPlayerObject->GetPTransform()->GetPosition()) - planetPrePos;
	m_distPlayerPow = distPlayer.MagnitudeSquared();
}

//curActivationTime = steady_clock::now();
//std::chrono::duration<double, std::milli> elapsedTime = curActivationTime - pastActivationTime;
//std::chrono::duration<double, std::milli> sinceStartTime = curActivationTime - trueBeganTime;



