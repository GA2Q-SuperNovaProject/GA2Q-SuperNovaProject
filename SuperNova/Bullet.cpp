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
			//5�ʸ��� ������� ����ź Mode.
			//Millisecond ���� ī����.

			m_bulletDirVec.Normalize(); //����ȭ

			m_nowPos.x += m_bulletDirVec.x * m_ShootingStarSpeed;
			m_nowPos.y += m_bulletDirVec.y * m_ShootingStarSpeed;

			////�ٽ� Ÿ�̸� ����.
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

			//5�ʸ��� ������� ����ź Mode.
			//Millisecond ���� ī����.

			m_bulletDirVec.Normalize(); //����ȭ

			m_nowPos.x += m_bulletDirVec.x * m_ShootingStarTailSpeed;
			m_nowPos.y += m_bulletDirVec.y * m_ShootingStarTailSpeed;
		}
		break;

		case eObjectName::SATELLITE:
		{
			//PlayerObject�� �޾Ƽ� Ư���� �Ÿ��� ������ ��?
			//����. ������ ��ó�� �ֱ⿡, 3.5�� ������ ��������.

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
	//[TW] ���� -> m_beginPos�� �ٲ����ν� ������Ʈ ��Ʈ���� �Ǵ°�?

	//���� ���ο��� ���̴� ������Ʈ�̴�, �̴� �翬�� ��.
	m_pTransform->SetPosition(Camera::GeInstance().WorldToCameraPOINT(m_nowPos));

	////�÷��̾�� ������ ���� ��ġ ���� ���� ���.

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
	//C++17�� Ư��!
	durationTime = time;
}

void Bullet::Sortation()
{
	//�̷��� �ϰ� ���߿� ������Ʈ Ǯ�� �ڵ� ����.
	//Enum�� �ް� �ϸ� �ȴ�.
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
	// �ۿ� �÷��̾�� �浹 �ߴٴ� ������ �ʿ�	
	//if (CollisionManager::GetInstance().CheckCollision(this))
	//{
	//	if (m_pCollider->GetOtherCollidedObject() == playerObject)
	//	{
	//		TurnOffCollider();
	//	}
	//}

}