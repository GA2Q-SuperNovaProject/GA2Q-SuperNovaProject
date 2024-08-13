#include "Player.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "BulletManager.h"
#include "RenderSystem.h"
#include "CollisionManager.h"	
#include "SoundManager.h"
#include "EnumDefine.h"
#include "Debug.h"
#include "Collider.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "Item.h"
#include "Scene.h"
#include "Camera.h"
#include "Body.h"
#include "Force.h"
#include <string>

using namespace std;

const int HARDCODING_MINUS_COUNT = 5;
const float BOOST_COOLTIMECOUNT = 20.0f;
const int MOVE_FORCE = 2000;

Player::Player(eObjectTag tag, eObjectName name, Transform transform, int imageIndex)
	: GameObject(tag, name, transform, imageIndex),
	m_hpCount(3),
	m_isDead(false),
	m_boostCount(3),
	m_boostCoolTimeCount(BOOST_COOLTIMECOUNT),
	m_boostTimeCount(3),
	m_gracePeriod(false),
	m_isMusicStart(true)
{
}

Player::~Player()
{
}

void Player::Start()
{

}

void Player::Update()
{
	//체력이 3이상이 될시
	if (m_hpCount >= 4)
	{
		m_hpCount = 3;
	}

	if (m_pTransform->GetPosition().x < Camera::GeInstance().GetCameraRect().GetTL().x
		|| m_pTransform->GetPosition().x > Camera::GeInstance().GetCameraRect().GetBR().x
		|| m_pTransform->GetPosition().y > Camera::GeInstance().GetCameraRect().GetBR().y
		|| m_pTransform->GetPosition().y < Camera::GeInstance().GetCameraRect().GetTL().y)
	{
		m_isDead = true;
	}

	if (m_hpCount <= 0 || m_isDead == true)
	{
		m_isDead = true;
		SceneManager::GetInstance().ChangeScene(eSceneName::BAD_ENDING);
	}
	else
	{
		Boost();
		Move();

		// 부스터 횟수 초기화
		if (m_boostCount == 0 || m_boostCoolTime)
		{
			m_boostCoolTimeCount -= 0.1f;
			m_boostCoolTime = true;

			if (m_boostCount == 3)
			{
				m_boostCoolTime = false;
			}
			if (m_boostCoolTimeCount <= 0)
			{
				m_boostCount += 1;			// 부스터의 횟수가 증가해야한다
				m_boostCoolTimeCount = BOOST_COOLTIMECOUNT;// 쿨타임 또한 초기화 되어야 한다
			}
		}


		if (CollisionManager::GetInstance().CheckCollision(this))
		{
			if (this->m_pCollider->GetOtherCollidedObject()->GetTag() == eObjectTag::BULLET)
			{
				if (isInvinc == false)
				{
					this->m_hpCount--;
					invinStartTime = std::chrono::steady_clock::now();
					isInvinc = true;
					//TurnOffCollider();
					SoundManager::StopSound(SOUND_BOOSTER);
					SoundManager::PlaySounds(SOUND_SHOOTING_STAR_CRASH);
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
}

void Player::LateUpdate()
{
	//블랙홀 로직
	
}

void Player::Render()
{
	temp = Camera::GeInstance().WorldToCameraPOINT(m_pTransform->GetPosition());
	//RenderSystem::GetInstance().DrawSprite(m_imageIndex, temp.x, temp.y, m_pTransform);
	RenderSystem::GetInstance().DrawGIFWithPos(m_imageIndex, temp.x, temp.y, m_pTransform);


	////워링 화살표 체크
	//BoxCollider* rectCol = static_cast<BoxCollider*>(m_pCollider);
	//Vec2Rect rect = rectCol->GetWorldRect();
	//Camera::GeInstance().Vec2RectToCameraPOINT(rect);
	//RenderSystem::GetInstance().DrawDebugRect(rect, eDebugBrush::EDB_RED);

	//ProjectileRenderText();
}

void Player::Move()
{	
	if (SceneManager::GetInstance().GetCurScene()->GetName() == eSceneName::SNAKE_PLANET ||
		SceneManager::GetInstance().GetCurScene()->GetName() == eSceneName::STORY_PLANET)
	{
		m_PlayerMoveOn = false;
		m_pTransform->m_Position.x = 960.f;
		m_pTransform->m_Position.y = 400.f;
	}

	// PlayerMoveOn 일때만 움직임
	if (m_PlayerMoveOn == true)
	{
		// 움직임을 멈췄을 시 약간 밀려나는 느낌 구현 필요
		// 밀려나는 것을 없애려면 움직임과 반대 되는 방향키(WASD)를 눌러야 함

		if (InputManager::GetInstance().IsKeyDown('W')
			|| InputManager::GetInstance().IsKeyPress('W'))
		{
			MoveAt(m_UP);
			if (lastDirIsLeft)
			{
				m_imageIndex = GIF_LEFTUP;
			}
			else
			{
				m_imageIndex = GIF_UP;
			}	

		}

		if (InputManager::GetInstance().IsKeyDown('S')
			|| InputManager::GetInstance().IsKeyPress('S'))
		{
			MoveAt(m_DOWN);
			if (lastDirIsLeft)
			{
				m_imageIndex = GIF_LDOWN;
			}
			else
			{
				m_imageIndex = GIF_RDOWN;
			}
		}

		if (InputManager::GetInstance().IsKeyDown('A')
			|| InputManager::GetInstance().IsKeyPress('A'))
		{
			MoveAt(m_LEFT);
			m_imageIndex = GIF_LGO;
			lastDirIsLeft = true;
		}

		if (InputManager::GetInstance().IsKeyDown('D')
			|| InputManager::GetInstance().IsKeyPress('D'))
		{
			MoveAt(m_RIGHT);
			m_imageIndex = GIF_RGO;
			lastDirIsLeft = false;
		}

		if (InputManager::GetInstance().IsKeyUp('W') || InputManager::GetInstance().IsKeyUp('S'))
		{
			if (lastDirIsLeft)
			{
				m_imageIndex = GIF_LEFTSTANDING;
			}
			else
			{
				m_imageIndex = GIF_STANDING;
			}
		}
		if (InputManager::GetInstance().IsKeyUp('A'))
		{
			m_imageIndex = GIF_LEFTSIDESTANDING;
		}
		if (InputManager::GetInstance().IsKeyUp('D'))
		{
			m_imageIndex = GIF_SIDESTANDING;
		}

	}
}

void Player::Boost()
{
	eSceneName sceneName = SceneManager::GetInstance().GetCurScene()->GetName();

	if (sceneName == eSceneName::STAGE1 || sceneName == eSceneName::STAGE2
		|| sceneName == eSceneName::STAGE3)
	{
		// 부스터 사용
		if (InputManager::GetInstance().IsKeyDown(VK_SPACE) && !m_boostCoolTime)
		{
			if (m_isMusicStart)
			{
				SoundManager::PlaySounds(SOUND_BOOSTER);
				m_isMusicStart = false;
			}

			m_boostCount--;
			m_gracePeriod = true;
			boostInnerCount = HARDCODING_MINUS_COUNT;
		}
		if (m_gracePeriod)
		{
			boostInnerCount--;
			if (boostInnerCount <= 0)
			{
				m_pBody->acceleration = Vec2(0.0f, 0.0f);
				m_pBody->velocity = Vec2(0.0f, 0.0f);
				m_gracePeriod = false;
				boostInnerCount = HARDCODING_MINUS_COUNT;
			}
		}
	}

	// 남은 부스터 시간 초기화
	if (InputManager::GetInstance().IsKeyUp(VK_SPACE))
	{
		if (!m_isMusicStart)
		{
			//SoundManager::StopSound(SOUND_BOOSTER);
			m_isMusicStart = true;
		}

		m_gracePeriod = false;
	}
}

void Player::MoveAt(Vec2 direction)
{
	if (m_gracePeriod)
	{
		direction *= m_boostSpeed;
	}

	//그냥 벡터 이동 버전
	//m_pTransform->m_Position += direction;

	Vec2 actualForce = direction * MOVE_FORCE;
	AddForce(actualForce);

	Vec2 dragForce = Force::AddDragForce(this, 0.01f);
	AddForce(dragForce);

	//Camera::GeInstance().FollowPlayer(direction,fixedPlayerObject);
	if (GetIsBoost())
	{
		Camera::GeInstance().FollowPlayer(direction, fixedPlayerObject);
	}
	else
	{
		if (FollowCamera())
		{
			Camera::GeInstance().FollowPlayer(direction, fixedPlayerObject);
		}
	}
	
}

bool Player::FollowCamera()
{
	//여기에 If/Else로 제어해야 함.
	if (SceneManager::GetInstance().GetCurScene()->GetName() == eSceneName::STAGE3)
	{
		return m_pTransform->GetPosition().x > 1100.f || m_pTransform->GetPosition().x < -100.f
			|| m_pTransform->GetPosition().y > 1367.5f || m_pTransform->GetPosition().y < 682.5f;
	}
	else
	{
		return m_pTransform->GetPosition().x > 1595.f || m_pTransform->GetPosition().x < 395.f
			|| m_pTransform->GetPosition().y > 7135.5f || m_pTransform->GetPosition().y < 6450.5;
	}
}

void Player::ProjectileRenderText()
{
	static int eightCount = 0;
	static int fiveCount = 0;
	std::wstring wstr = L"(8) Projectiles : ";
	bool bulletCount8 = BulletManager::GetInstance().m_EveryEight;

	if (bulletCount8 == true)
	{   
		eightCount++;
	}   
	wstr += std::to_wstring(eightCount);
	RenderSystem::GetInstance().InfoText(Vec2(100, 100), wstr);

	bool bulletCount5 = BulletManager::GetInstance().m_EveryFive;

	if (bulletCount5 == true)
	{
		fiveCount++;
	}
	std::wstring wstr2 = L"(5) Projectiles : ";
	wstr2 += std::to_wstring(fiveCount);
	RenderSystem::GetInstance().InfoText(Vec2(100, 200), wstr2);

	std::wstring wstr3 = L"Bullets In Game Now : ";
	int bulletCnt = 0;
	for (auto it : belongScene->m_arrobj)
	{
		if (it->GetTag() == eObjectTag::BULLET)
		{
			bulletCnt++;
		}
	}
	wstr3 += std::to_wstring(bulletCnt);
	RenderSystem::GetInstance().InfoText(Vec2(100, 300), wstr3);

	//std::wstring wstr4 = L"Player Position In World : ";
	//wstr4 += std::to_wstring(this->GetPTransform()->GetPosition().x);
	//wstr4 += L", ";
	//wstr4 += std::to_wstring(this->GetPTransform()->GetPosition().y);
	//RenderSystem::GetInstance().InfoText(Vec2(100, 400), wstr4);

	std::wstring wstr5 = L"Player Health : ";
	wstr5 += std::to_wstring(m_hpCount);
	RenderSystem::GetInstance().InfoText(Vec2(100, 400), wstr5);

	std::wstring wstr6 = L"Player Invis : ";
	wstr6 += std::to_wstring(isInvinc);
	RenderSystem::GetInstance().InfoText(Vec2(100, 500), wstr6);
}

