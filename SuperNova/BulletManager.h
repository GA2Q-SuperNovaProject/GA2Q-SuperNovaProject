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
		//시간을 초기화한다.
	void StartBulletManager(eSceneName scene);

	//실제로는 윤제 형의 Object Pool에서 오브젝트들을 가져오는 방식이다.
	//일단은 별똥별 하나만 스폰하게.
	
	//한가지 Bullet만 날려보내는 전략. (탄막 위치 / 지속 시간)
	void SpawnBullet(Scene* scene, const Vec2& bulletLocation, eBulletType bulletType, int durationTime); 

	// 일정한 영역 안에 랜덤한 값을 산출해서 그 안에 해당 개수만큼의 일만.
	// 특정한 영역 Rect 안에 랜덤하게 분포되어 스폰.
	void SpawnBulletsInArea(Scene* scene, eBulletType bulletType, int durationTime, int bulletCount);

	void ReturnToObjectPool(Bullet* gameObject);

	//BulletManager에서 Update에 갖다놓으면 작동함.
	void UpdateManager(eBulletDiff diff, Scene* scene);

	bool m_EveryFive = false; //이거 True일때만 발동하면 됨.
	bool m_EveryEight = false;
private:
	BulletManager();
	~BulletManager();

	int bulletCntNow = 0; //현재 스크린에 있는 탄막의 개수. 

	//bulletCntNow를 직접 가져다 쓰기 보다는, 내부적으로 Clamp를 사용한다. (2-5)
	int GetClampedBulletCnt();

	//위 함수, 하지만 4개로 제한을 둔 버전. (2-4) 
	int GetClampedBulletCntFour();

	//얘가 실질적으로 갖다 써야 할 애. 
	void BulletMechanics(eBulletDiff diff, Scene* scene);
	
	std::chrono::steady_clock::time_point prevSpawnFive;
	std::chrono::steady_clock::time_point nowSpawnFive;

	std::chrono::steady_clock::time_point prevSpawnEight;
	std::chrono::steady_clock::time_point nowSpawnEight;

	std::chrono::duration<double, std::milli> elapsedFive;
	std::chrono::duration<double, std::milli> elapsedEight;

	//얘는 실질적으로 Coroutine을 Update하는 친구.
	void UpdateTimeBoolean();
	
	//얘는 현재 CameraRect 안에 있는 것을 체크.
	void CaptureBulletCntInGame();

	//현재 씬에 있는 BulletCount를 클리어함.
	void ClearBulletCntInGame();



	Scene* currentScene;

	//임시로 담고 뺄 Bullet들의 Vector.
	std::vector<GameObject*> m_bulletVector;
};
