#include "Bullet.h"
#include "Transform.h"
#include "RenderSystem.h"
#include "Camera.h"
#include "ObjectManager.h"
#include "SceneManager.h"
#include "Debug.h"
#include "Scene.h"
#include "CollisionManager.h"
#include "TimeManager.h"
#include "Collider.h"
#include "Random.h"
#include "Player.h"
#include "CircleCollider.h"
#include "BoxCollider.h"

using namespace std;
using namespace std::chrono;


Bullet::Bullet(eObjectTag tag, eObjectName name, Transform transform)
	:GameObject(tag, name, transform), m_nowPos(transform.GetPosition())
{
	isfrontRender = true;
}

Bullet::~Bullet()
{

}

void Bullet::Start()
{
	trueBeganTime = steady_clock::now();
	pastActivationTime = trueBeganTime;
}

void Bullet::Update()
{

	if (m_nowStarting)
	{
		Sortation();
		trueBeganTime = steady_clock::now();
		pastActivationTime = trueBeganTime;
		m_nowStarting = false;
		playerObject = belongScene->FindObjectInScene(eObjectName::PLAYER);
		m_pRealPlayer = static_cast<Player*>(playerObject);

		if (m_pCollider == nullptr)
		{
			switch (m_imageIndex)
			{
				case IMAGE_SHOOTING_STAR:
					this->PutCollider(eColType::BOX, IMAGE_SHOOTING_STAR);
					break;

				case IMAGE_SHOOTING_STAR_TAIL:
					this->PutCollider(eColType::BOX, IMAGE_SHOOTING_STAR_TAIL);
					break;

				case IMAGE_SATELLITE:
					this->PutCollider(eColType::BOX, IMAGE_SATELLITE);
					break;

			}
			
		}
	}

	if (m_nowPos.x <= 0.f && m_nowPos.y <= 0.f)
	{
		m_nowPos = m_pTransform->GetPosition();
	}

	if (playerObject == nullptr)
	{
		playerObject = belongScene->FindObjectInScene(eObjectName::PLAYER);
		m_pRealPlayer = static_cast<Player*>(playerObject);
	}
	curActivationTime = steady_clock::now();
	std::chrono::duration<double, std::milli> elapsedTime = curActivationTime - pastActivationTime;
	std::chrono::duration<double, std::milli> sinceStartTime = curActivationTime - trueBeganTime;
	switch (m_name)
	{
		case eObjectName::SHOOTHING_STAR:
		{
			if (playerLocated == false)
			{
				m_bulletDirVec = (playerObject->GetPTransform()->GetPosition() - m_nowPos);
				playerLocated = true;
			}
			//5초마다 따라오는 유도탄 Mode.
			//Millisecond 단위 카운팅.

			m_bulletDirVec.Normalize(); //정규화

			m_nowPos.x += m_bulletDirVec.x * m_ShootingStarSpeed;
			m_nowPos.y += m_bulletDirVec.y * m_ShootingStarSpeed;

			////다시 타이머 리셋.
			//if (elapsedTime.count() >= 10000)
			//{
			//	pastActivationTime = curActivationTime;
			//}
		}
		break;

		case eObjectName::SHOOTHING_STAR_TAIL:
		{
			if (playerLocated == false)
			{
				m_bulletDirVec = (playerObject->GetPTransform()->GetPosition() - m_nowPos);
				playerLocated = true;
			}

			//5초마다 따라오는 유도탄 Mode.
			//Millisecond 단위 카운팅.

			m_bulletDirVec.Normalize(); //정규화

			m_nowPos.x += m_bulletDirVec.x * m_ShootingStarTailSpeed;
			m_nowPos.y += m_bulletDirVec.y * m_ShootingStarTailSpeed;
		}
		break;

		case eObjectName::SATELLITE:
		{
			//PlayerObject를 받아서 특정한 거리에 들어왔을 때?
			//ㄴㄴ. 어차피 근처에 있기에, 3.5초 정도로 세팅하자.

			if (elapsedTime.count() <= 2000)
			{
				m_bulletDirVec = (playerObject->GetPTransform()->GetPosition() - m_nowPos);
			}
			m_bulletDirVec.Normalize();
			m_nowPos.x += m_bulletDirVec.x * m_SatelliteSpeed;
			m_nowPos.y += m_bulletDirVec.y * m_SatelliteSpeed;
		}
		break;
	}
	//[TW] 시험 -> m_beginPos를 바꿈으로써 오브젝트 컨트롤이 되는가?

	//월드 내부에서 쓰이는 오브젝트이니, 이는 당연한 것.
	m_pTransform->SetPosition(Camera::GeInstance().WorldToCameraPOINT(m_nowPos));

	////플레이어와 본인의 현재 위치 사이 벡터 계산.

	m_Screen.SetTL(Camera::GeInstance().WorldToCameraPOINT(Camera::GeInstance().GetCameraRect().GetTL()));
	m_Screen.SetBR(Camera::GeInstance().WorldToCameraPOINT(Camera::GeInstance().GetCameraRect().GetBR()));

	BulletEvent();

	if (m_Screen.GetTL().y >= m_pTransform->GetPosition().y || m_Screen.GetBR().y < m_pTransform->GetPosition().y
		//|| m_Screen.GetTL().y > m_pTransform->GetPosition().y || m_Screen.GetBR().y < m_pTransform->GetPosition().y)
		|| m_Screen.GetTL().x > m_pTransform->GetPosition().x || m_Screen.GetBR().x < m_pTransform->GetPosition().x)
	{
		//Debug::Trace("", m_Screen.GetTL().y, m_pTransform->GetPosition().y);

		belongScene->RemoveObject(this);
		//BulletManager::GetInstance().ReturnToObjectPool(this); 
		//Return To Object Pool
	}


	if (sinceStartTime.count() >= durationTime)
	{
		belongScene->RemoveObject(this);
	}
}

void Bullet::LateUpdate()
{
	
}

void Bullet::Render()
{
	//m_pTransform->SetPosition(Camera::GeInstance().WorldToCameraPOINT(m_pTransform->GetPosition()));
	RenderSystem::GetInstance().DrawSprite(m_imageIndex, m_pTransform->GetPosition().x, m_pTransform->GetPosition().y, this->GetPTransform());
	
	//Vec2 tmpPos = Vec2(m_pTransform->GetPosition().x, m_pTransform->GetPosition().y);
	//tmpCirc.position = tmpPos;
	//tmpCirc.radius = 50.0f;
	////RenderSystem::GetInstance().DrawDebugCircle(tmpCirc, eDebugBrush::EDB_RED);
	
	BoxCollider* boxCol = static_cast<BoxCollider*>(m_pCollider);
	Vec2Rect rect = boxCol->GetWorldRect();
	RenderSystem::GetInstance().DrawDebugRect(rect, eDebugBrush::EDB_BLUE);

	/*Debug::Trace("Bullet Pos : ", tmpPos.x, tmpPos.y);
	tmpPos = Camera::GeInstance().CameraToWorldPOINT(tmpPos);
	Debug::Trace("Bullet World Pos : ", tmpPos.x, tmpPos.y);*/
}

void Bullet::SetDurationTime(unsigned int time)
{
	//C++17의 특권!
	durationTime = time;
}

void Bullet::Sortation()
{
	//이렇게 하고 나중에 오브젝트 풀링 코드 수정.
	//Enum을 받게 하면 된다.
	switch (m_name)
	{
		case eObjectName::SHOOTHING_STAR:
			m_imageIndex = IMAGE_SHOOTING_STAR;
			break;
		case eObjectName::SHOOTHING_STAR_TAIL:
			m_imageIndex = IMAGE_SHOOTING_STAR_TAIL;
			break;
		case eObjectName::SATELLITE:
			m_imageIndex = IMAGE_SATELLITE;
			break;
	}

}

void Bullet::BulletEvent()
{
	// 밖에 플레이어와 충돌 했다는 조건이 필요	
	//if (CollisionManager::GetInstance().CheckCollision(this))
	//{
	//	if (m_pCollider->GetOtherCollidedObject() == playerObject)
	//	{
	//		TurnOffCollider();
	//	}
	//}

}