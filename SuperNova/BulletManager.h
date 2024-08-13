#pragma once
#include <chrono>
#include <vector>
#include "Vec2.h"
#include "StructDefine.h"
#include "EnumDefine.h"

class Bullet;
class Scene;
class GameObject;

const int MAXIMUM_BULLET_SCREEN = 5;

class BulletManager
{
public:
	static BulletManager& GetInstance()
	{
		static BulletManager inst;
		return inst;
	}
		//�ð��� �ʱ�ȭ�Ѵ�.
	void StartBulletManager(eSceneName scene);

	//�����δ� ���� ���� Object Pool���� ������Ʈ���� �������� ����̴�.
	//�ϴ��� ���˺� �ϳ��� �����ϰ�.
	
	//�Ѱ��� Bullet�� ���������� ����. (ź�� ��ġ / ���� �ð�)
	void SpawnBullet(Scene* scene, const Vec2& bulletLocation, eBulletType bulletType, int durationTime); 

	// ������ ���� �ȿ� ������ ���� �����ؼ� �� �ȿ� �ش� ������ŭ�� �ϸ�.
	// Ư���� ���� Rect �ȿ� �����ϰ� �����Ǿ� ����.
	void SpawnBulletsInArea(Scene* scene, eBulletType bulletType, int durationTime, int bulletCount);

	void ReturnToObjectPool(Bullet* gameObject);

	//BulletManager���� Update�� ���ٳ����� �۵���.
	void UpdateManager(eBulletDiff diff, Scene* scene);

	bool m_EveryFive = false; //�̰� True�϶��� �ߵ��ϸ� ��.
	bool m_EveryEight = false;
private:
	BulletManager();
	~BulletManager();

	int bulletCntNow = 0; //���� ��ũ���� �ִ� ź���� ����. 

	//bulletCntNow�� ���� ������ ���� ���ٴ�, ���������� Clamp�� ����Ѵ�. (2-5)
	int GetClampedBulletCnt();

	//�� �Լ�, ������ 4���� ������ �� ����. (2-4) 
	int GetClampedBulletCntFour();

	//�갡 ���������� ���� ��� �� ��. 
	void BulletMechanics(eBulletDiff diff, Scene* scene);
	
	std::chrono::steady_clock::time_point prevSpawnFive;
	std::chrono::steady_clock::time_point nowSpawnFive;

	std::chrono::steady_clock::time_point prevSpawnEight;
	std::chrono::steady_clock::time_point nowSpawnEight;

	std::chrono::duration<double, std::milli> elapsedFive;
	std::chrono::duration<double, std::milli> elapsedEight;

	//��� ���������� Coroutine�� Update�ϴ� ģ��.
	void UpdateTimeBoolean();
	
	//��� ���� CameraRect �ȿ� �ִ� ���� üũ.
	void CaptureBulletCntInGame();

	//���� ���� �ִ� BulletCount�� Ŭ������.
	void ClearBulletCntInGame();



	Scene* currentScene;

	//�ӽ÷� ��� �� Bullet���� Vector.
	std::vector<GameObject*> m_bulletVector;
};
