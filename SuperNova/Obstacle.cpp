#include "Obstacle.h"
#include "Transform.h"
#include "RenderSystem.h"
#include "Camera.h"
#include "Collider.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "ObjectManager.h"
#include "SceneManager.h"
#include "EnumDefine.h"
#include "Debug.h"
#include "Scene.h"
#include "CollisionManager.h"
#include "Force.h"
#include "Body.h"
#include "Vec2.h"


//Layer3�� ���� �ְ�, Layer1�� ���� �����.
const int LAYER3_DISTANCE = 1500000;
const int LAYER2_DISTANCE = 800000;
const int LAYER1_DISTANCE = 400000;

const int LAYER3_PULLPOWER = 600;
const int LAYER2_PULLPOWER = 1000;
const int LAYER1_PULLPOWER = 2000;


Obstacle::Obstacle(eObjectTag tag, eObjectName name, Transform transform)
	:GameObject(tag, name, transform), m_beginPos(transform.GetPosition())
{
	Sortation();
}

Obstacle::~Obstacle()
{

}

void Obstacle::Start()
{
	m_pPlayer = belongScene->FindObjectInScene(eObjectName::PLAYER);
}

void Obstacle::Update()
{
	m_pTransform->SetPosition(Camera::GeInstance().WorldToCameraPOINT(m_beginPos));
	MeasurePlayerDistance(); //�÷��̾���� �Ÿ��� ���.
	BlackHolePull(); //�ȿ��� If������ üũ�Ѵ�.

	BlackHoleEvent();
}

void Obstacle::LateUpdate()
{
	if (m_imageIndex == IMAGE_BLACKHOLE)
	{
		//��Ȧ ����
		if (CollisionManager::GetInstance().CheckCollision(this))
		{
			if (this->GetPCollider()->GetOtherCollidedObject() == m_pPlayer)
			{
				this->belongScene->RemoveObject(m_pPlayer);
				Debug::Trace("REMOVING");
			}
		}
	}


}

void Obstacle::Render()
{
	RenderSystem::GetInstance().DrawSprite(m_imageIndex, m_pTransform->GetPosition().x, m_pTransform->GetPosition().y, this->GetPTransform());
	
	//�Ϲ������� �����ϴ� ���. GetWorldRect�� �޾ƾ� �Ѵ�. Obstacle�� Box�� ����ɶ��� �̾߱�, �ƴϸ� ����.

	//BoxCollider* boxCol = static_cast<BoxCollider*>(m_pCollider);
	//RenderSystem::GetInstance().DrawDebugRect(boxCol->GetWorldRect(), eDebugBrush::EDB_RED);

	//CircleCollider* tmpCircle = static_cast<CircleCollider*>(m_pCollider);
	//RenderSystem::GetInstance().DrawDebugCircle(tmpCircle->GetWorldCircle(), eDebugBrush::EDB_RED);

	/*if (m_name == eObjectName::BLACKHOLE)
	{
		std::wstring wstr = L"m_distPlayerPow : ";
		wstr += std::to_wstring(m_distPlayerPow);
		RenderSystem::GetInstance().InfoText(Vec2(100, 250), wstr);
	}*/
}

void Obstacle::Sortation()
{
	switch (m_name)
	{
		case eObjectName::BLACKHOLE:
			m_imageIndex = IMAGE_BLACKHOLE;
			break;
	}
}

void Obstacle::BlackHolePull()
{
	//�ϱ� ����, �׽�Ʈ����! (�Ÿ� �����ϱ� ����)
	if (m_imageIndex == IMAGE_BLACKHOLE)
	{
		//2�̴�, MagnitudeSquared�� ȯ���ؼ� ����غ���.
		//40000 // 160000 // 360000
		if (m_distPlayerPow < LAYER3_DISTANCE && m_distPlayerPow >= LAYER2_DISTANCE)
		{
			//Vec2 pullForce = Force::AddGravityForce(m_pPlayer, this, 5, 10, 40);
			Vec2 playerPrePos = (m_pPlayer->GetPTransform()->GetPosition());
			Vec2 blackholePrePos = (this->GetPTransform()->GetPosition());
			blackholePrePos = Camera::GeInstance().CameraToWorldPOINT(blackholePrePos);
			Vec2 pullDir = blackholePrePos - playerPrePos;
			pullDir.Normalize();
			m_pPlayer->AddForce(pullDir * LAYER3_PULLPOWER);
		}
		else if (m_distPlayerPow < LAYER2_DISTANCE && m_distPlayerPow >= LAYER1_DISTANCE)
		{
			//Vec2 pullForce = Force::AddGravityForce(m_pPlayer, this, 5, 10, 40);
			Vec2 playerPrePos = (m_pPlayer->GetPTransform()->GetPosition());
			Vec2 blackholePrePos = (this->GetPTransform()->GetPosition());
			blackholePrePos = Camera::GeInstance().CameraToWorldPOINT(blackholePrePos);
			Vec2 pullDir = blackholePrePos - playerPrePos;
			pullDir.Normalize();
			m_pPlayer->AddForce(pullDir * LAYER2_PULLPOWER);
		}
		else if (m_distPlayerPow < LAYER1_DISTANCE)
		{
			//Vec2 pullForce = Force::AddGravityForce(m_pPlayer, this, 5, 10, 40);
			Vec2 playerPrePos = (m_pPlayer->GetPTransform()->GetPosition());
			Vec2 blackholePrePos = (this->GetPTransform()->GetPosition());
			blackholePrePos = Camera::GeInstance().CameraToWorldPOINT(blackholePrePos);
			Vec2 pullDir = blackholePrePos - playerPrePos;
			pullDir.Normalize();
			m_pPlayer->AddForce(pullDir * LAYER1_PULLPOWER);
		}
	}
}

void Obstacle::BlackHoleEvent()
{
	// �ۿ� �÷��̾�� �浹 �ߴٴ� ������ �ʿ�	
	if (CollisionManager::GetInstance().CheckCollision(this))
	{
		if (m_pCollider->GetOtherCollidedObject() == m_pPlayer)
		{
			SceneManager::GetInstance().ChangeScene(eSceneName::BAD_ENDING);
		}
		if (m_pCollider->GetOtherCollidedObject()->GetName() == eObjectName::SATELLITE)
		{
			belongScene->RemoveObject(m_pCollider->GetOtherCollidedObject());
			belongScene->RemoveObject(this);
			//���Ⱑ ���� �����ϴ� ����.
		}
	}
}

void Obstacle::MeasurePlayerDistance()
{
	Vec2 blackholePrePos = (this->GetPTransform()->GetPosition());
	blackholePrePos = Camera::GeInstance().CameraToWorldPOINT(blackholePrePos);
	Vec2 distPlayer = (m_pPlayer->GetPTransform()->GetPosition()) - blackholePrePos;
	m_distPlayerPow = distPlayer.MagnitudeSquared();
}
