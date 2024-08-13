#include "Camera.h"
#include "GameObject.h"
#include "Transform.h"
#include "Debug.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Player.h"

Camera::Camera()
	:m_width(0.f), m_height(0.f), m_leftTopPos(), m_centerPos(), m_pPlayer()
{
}

Camera::~Camera()
{
}

void Camera::Initialize()
{
	m_width = 1920;
	m_height = 1080;

	m_centerPos.x = m_width / 2;
	m_centerPos.y = m_height / 2;

	m_leftTopPos.x = m_centerPos.x - m_width / 2;
	m_leftTopPos.y = m_centerPos.y - m_height / 2;
	
}

void Camera::PlayerInit()
{
	//플레이어 객체 포인터를 못찾는걸 파인드 오브젝트라는 것을 통해서 넣어줌 오류 해결
	m_pPlayer = SceneManager::GetInstance().GetCurScene()->FindObjectInScene(eObjectName::PLAYER);

	if (m_pPlayer != NULL)
	{
		m_centerPos.x = m_pPlayer->GetPTransform()->GetPosition().x;
		m_centerPos.y = m_pPlayer->GetPTransform()->GetPosition().y;
	}

	m_beginLeftTopPos.x = m_centerPos.x - m_width / 2;
	m_beginLeftTopPos.y = m_centerPos.y - m_height / 2;
}

void Camera::Update()
{
	/// 카메라 이미지 벗어나지 않도록
	if (m_centerPos.x <= m_width / 2)
	{
		m_centerPos.x = m_width / 2;
	}

	if (m_centerPos.y <= m_height / 2)
	{
		m_centerPos.y = m_height / 2;
	}

	if (SceneManager::GetInstance().GetCurScene()->GetName() == eSceneName::STAGE3)
	{
		if (m_centerPos.x >= 5.2 * m_width - m_width / 2)
		{
			m_centerPos.x = 5.2 * m_width - m_width / 2;
		}

		if (m_centerPos.y >= 1.3 * m_height - m_height / 2)
		{
			m_centerPos.y = 1.3 * m_height - m_height / 2;
		}
	}
	else
	{
		if (m_centerPos.x >= 2.5 * m_width - m_width / 2)
		{
			m_centerPos.x = 2.5 * m_width - m_width / 2;
		}

		if (m_centerPos.y >= 6.6 * m_height - m_height / 2)
		{
			m_centerPos.y = 6.6 * m_height - m_height / 2;
		}
	}
	m_leftTopPos.x = m_centerPos.x - m_width / 2;
	m_leftTopPos.y = m_centerPos.y - m_height / 2;	

	//Debug::Trace("Camera", m_centerPos.x, m_centerPos.y);
	//Debug::Trace("Camera", m_leftTopPos.x, m_leftTopPos.y);
	//Debug::Trace("Camera", m_leftTopPos.x, m_leftTopPos.y);
}

void Camera::FollowPlayer(Vec2 moveAt, GameObject* playerObj)
{
	Player* tmpPlayer = static_cast<Player*>(playerObj);

	if (tmpPlayer->GetIsBoost() == true)
	{
		if (m_pPlayer != NULL)
		{
			m_centerPos.x = m_pPlayer->GetPTransform()->GetPosition().x;
			m_centerPos.y = m_pPlayer->GetPTransform()->GetPosition().y;
		}
		m_beginLeftTopPos.x = m_centerPos.x - m_width / 2;
		m_beginLeftTopPos.y = m_centerPos.y - m_height / 2;
	}
	else
	{
		/// 서서히 카메라의 중점이 캐릭터가 되도록
		if (m_centerPos.x < playerObj->GetPTransform()->GetPosition().x)			// 버그 = 스테이지 1 얼음행성 웜홀 탈시
		{
			m_centerPos.x += 3.f;
		}

		if (m_centerPos.y < playerObj->GetPTransform()->GetPosition().y)
		{
			m_centerPos.y += 3.f;
		}

		if (m_centerPos.x > playerObj->GetPTransform()->GetPosition().x)
		{
			m_centerPos.x -= 3.f;
		}

		if (m_centerPos.y > playerObj->GetPTransform()->GetPosition().y)
		{
			m_centerPos.y -= 3.f;
		}

		m_centerPos += moveAt;

		m_leftTopPos.x = m_centerPos.x - m_width / 2;
		m_leftTopPos.y = m_centerPos.y - m_height / 2;
	}

		
}

//Rect2D Camera::PlayerMoveSection()
//{
//	Rect2D rect;
//
//	rect.left	= (m_width / 2) - (m_moveSectionX / 2);
//	rect.top	= (m_height / 2) - (m_moveSectiony / 2);
//	rect.right	= (m_width / 2) + (m_moveSectionX / 2);
//	rect.bottom = (m_height / 2) + (m_moveSectiony / 2);
//
//	return rect;
//}

Vec2 Camera::WorldToCameraPOINT(Vec2 worldPOINT)
{
	Vec2 localPOINT;
	localPOINT = worldPOINT - m_leftTopPos;
	return localPOINT;
}

Vec2 Camera::WorldToCameraPOINT_UI(Vec2 worldPOINT)
{
	Vec2 localPOINT;
	localPOINT = worldPOINT - m_beginLeftTopPos;
	return localPOINT;
}

Vec2 Camera::CameraToWorldPOINT(Vec2 cameraPoint)
{
	Vec2 localPOINT;
	localPOINT = cameraPoint + m_leftTopPos;
	return localPOINT;
}

Vec2 Camera::RelativeSpawnPOINT(Vec2 spawnPOINT)
{
	Vec2 localPOINT;
	localPOINT = m_leftTopPos + spawnPOINT;
	return localPOINT;
}

void Camera::Vec2RectToCameraPOINT(Vec2Rect& worldRect)
{
	worldRect.topLeft = WorldToCameraPOINT(worldRect.topLeft);
	worldRect.topRight = WorldToCameraPOINT(worldRect.topRight);
	worldRect.bottomLeft = WorldToCameraPOINT(worldRect.bottomLeft);
	worldRect.bottomRight = WorldToCameraPOINT(worldRect.bottomRight);
}

void Camera::Vec2CircleToCameraPOINT(Vec2Circle& worldCircle)
{
	worldCircle.position = WorldToCameraPOINT(worldCircle.position);
}

Rect2D Camera::GetCameraRect() const
{
	Rect2D rect;
	rect.left = m_centerPos.x - (m_width / 2) - 100.f;
	rect.top = m_centerPos.y - (m_height / 2) - 100.f;
	rect.right = m_centerPos.x + (m_width / 2) + 100.f;
	rect.bottom = m_centerPos.y + (m_height / 2) + 100.f;

	return rect;
}
