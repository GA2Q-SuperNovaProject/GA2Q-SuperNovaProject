#pragma once
#include <chrono>
#include "GameObject.h"
#include "StructDefine.h"

class Player;

class Bullet : public GameObject
{
public:
	Bullet(eObjectTag tag, eObjectName name, Transform transform);
	~Bullet();

	virtual void Start() override;
	virtual void Update() override;
	virtual void LateUpdate() override; //Collision Detection
	virtual void Render() override;

	void SetDurationTime(unsigned int time);

private:
	void Sortation();

	void BulletEvent();
	Rect2D m_Screen;

	Vec2 m_nowPos; //총알이니 어쨌든 이동해야 한다.
	Vec2 m_bulletDirVec;

	//EASY
	int m_EasyShootingStarTailSpeed = 7;
	int m_EasyShootingStarSpeed = 12;

	//HARD
	int m_ShootingStarTailSpeed = 10;
	int m_ShootingStarSpeed = 16;
	int m_SatelliteSpeed = 8; //너무 빠르면 게임 플레이 불가.

	bool m_nowStarting = true;

	GameObject* playerObject = nullptr;
	Player* m_pRealPlayer = nullptr;

	//Millisecond 단위로 저장. I.E: 5000 = 5초
	int durationTime = 30000; //디폴트 

	std::chrono::steady_clock::time_point trueBeganTime; //실제로 생성 후부터 지나간 시간.
	std::chrono::steady_clock::time_point pastActivationTime;
	std::chrono::steady_clock::time_point curActivationTime;

	bool yetToStart = true;

	bool playerLocated = false;
	
};