#include "BulletManager.h"
#include "ObjectPool.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Bullet.h"
#include "ObjectPool.h"
#include "Random.h"
#include "Camera.h"
#include "Debug.h"
#include <chrono>
#include <algorithm>
#include "GameObject.h"

using namespace std::chrono;

BulletManager::BulletManager()
{
	m_bulletVector.reserve(50);
}

BulletManager::~BulletManager()
{

}



void BulletManager::StartBulletManager(eSceneName scene)
{
	prevSpawnFive = steady_clock::now();
	nowSpawnFive = prevSpawnFive;

	prevSpawnEight = steady_clock::now();
	nowSpawnEight = prevSpawnEight;

	currentScene = SceneManager::GetInstance().FindSceneByName(scene);
}

//Duration Time�� Millisecond ������ �Ǿ�� -> 
void BulletManager::SpawnBullet(Scene* scene, const Vec2& bulletLocation, eBulletType bulletType, int durationTime)
{
	Bullet* tmpBullet = ObjectPool<Bullet>::GetInstance().BorrowFromObjectPool(bulletType);
	tmpBullet->GetPTransform()->SetPosition(bulletLocation);
	tmpBullet->SetDurationTime(durationTime);
	SceneManager::GetInstance().PutObjectInScene(scene, tmpBullet);
}

void BulletManager::SpawnBulletsInArea(Scene* scene, eBulletType bulletType, int durationTime, int bulletCount)
{
	for (int i = 0; i < bulletCount; i++)
	{
		/*int randomX = Random::RandomRangeInt(static_cast<int>(Camera::GeInstance().GetCameraRect().left),
			static_cast<int>(Camera::GeInstance().GetCameraRect().right));
		int randomY = Random::RandomRangeInt(static_cast<int>(Camera::GeInstance().GetCameraRect().top),
			static_cast<int>(Camera::GeInstance().GetCameraRect().bottom));*/

		int randomX = 0;
		int boolChoice = Random::RandomRangeInt(0, 1);
		if (boolChoice == 0)
		{
			randomX = static_cast<int>(Camera::GeInstance().GetCameraRect().left);
		}
		else
		{
			randomX = static_cast<int>(Camera::GeInstance().GetCameraRect().right);
		}

		int randomY = Random::RandomRangeInt(static_cast<int>(Camera::GeInstance().GetCameraRect().top),
			static_cast<int>(Camera::GeInstance().GetCameraRect().bottom));

		Vec2 target(randomX, randomY);
		SpawnBullet(scene, target, bulletType, durationTime);
	}
}

void BulletManager::ReturnToObjectPool(Bullet* bullet)
{
	if (bullet != nullptr)
	{
		ObjectPool<Bullet>::GetInstance().ReturnToObjectPool(bullet); //������ ������� ���� ����.
	}
}

//Update �ȿ� �ҼӵǾ�, �۵��Ǵ� ����.
void BulletManager::UpdateTimeBoolean()
{
	//�ʱ�ȭ
	m_EveryFive = false;
	m_EveryEight = false;

	//���� �ð� ����.
	nowSpawnFive = steady_clock::now();
	nowSpawnEight = steady_clock::now();

	//���� �ð� ����.
	elapsedFive = nowSpawnFive - prevSpawnFive;
	elapsedEight = nowSpawnEight - prevSpawnEight;

	if (elapsedFive.count() >= 5000)
	{
		prevSpawnFive = nowSpawnFive;
		m_EveryFive = true;
		//Debug::Trace("FIVE");
	}

	if (elapsedEight.count() >= 8000)
	{
		prevSpawnEight = nowSpawnEight;
		m_EveryEight = true;
		//Debug::Trace("EIGHT");
	}
}



//Update �ȿ� �ҼӵǾ�, �۵��Ǵ� ����.
void BulletManager::BulletMechanics(eBulletDiff diff, Scene* scene)
{
	if (diff == eBulletDiff::EASY)
	{
		//N1~N2�ʸ� ��ٸ��� ����� �Ǵ� ����.
		if (m_EveryFive)
		{
			int luckyBall = Random::RandomRangeInt(0, 5); // 1���� 100���� RNG. Uniform Int.
			SpawnBulletsInArea(scene, eBulletType::FAST_TAIL, 8000, 5 - luckyBall);
			SpawnBulletsInArea(scene, eBulletType::LINEAR, 8000, luckyBall);
		}
	}
	else if (diff == eBulletDiff::HARD)
	{
		int luckyBall = 0;
		int allRemains = 0;
		int remainsBall = 0;

		//1-2�� ����.
		if (m_EveryEight)
		{
			luckyBall = 1;
			SpawnBulletsInArea(scene, eBulletType::FOLLOW, 8000, luckyBall);
		}

		if (m_EveryFive)
		{
			allRemains = 5 - luckyBall;
			remainsBall = Random::RandomRangeInt(0, allRemains);

			SpawnBulletsInArea(scene, eBulletType::FAST_TAIL, 8000, remainsBall);
			SpawnBulletsInArea(scene, eBulletType::LINEAR, 8000, allRemains - remainsBall);
		}
	}
}

void BulletManager::UpdateManager(eBulletDiff diff, Scene* scene)
{
	CaptureBulletCntInGame();
	UpdateTimeBoolean();
	BulletMechanics(diff, scene);
	ClearBulletCntInGame();
}

//���ο� Clamping.
int BulletManager::GetClampedBulletCnt()
{
	return std::clamp(bulletCntNow, 2, 5);
}

int BulletManager::GetClampedBulletCntFour()
{
	return std::clamp(bulletCntNow, 2, 4);
}

void BulletManager::CaptureBulletCntInGame()
{
	auto rect = Camera::GeInstance().GetCameraRect();

	//�ϴ� Bullet Manager�� Vector�� ����.
	for (auto it : currentScene->m_arrobj)
	{
		if (it->GetTag() == eObjectTag::BULLET)
		{
			m_bulletVector.push_back(it);
		}
	}

	for (auto it : m_bulletVector)
	{
		if (it->GetPTransform()->GetPosition().x <= rect.right &&
			it->GetPTransform()->GetPosition().x >= rect.left &&
			it->GetPTransform()->GetPosition().y <= rect.bottom &&
			it->GetPTransform()->GetPosition().y >= rect.top)
		{
			bulletCntNow++;
		}
	}
}

void BulletManager::ClearBulletCntInGame()
{
	bulletCntNow = 0;
	m_bulletVector.clear();
}
