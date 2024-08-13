#pragma once
#include <chrono>
#include "GameObject.h"
#include "Transform.h"
#include "Camera.h"

class Item;

class Player : public GameObject
{

	friend class GameUI;

public:
	Player(eObjectTag tag, eObjectName name, Transform transform, int imageIndex);
	~Player();

	virtual void Start();

	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

	bool GetPlayerIsDead()
	{
		return m_isDead;
	}

	bool m_PlayerMoveOn = true;
	int m_hpCount;

	int m_StarPiece1count1 = 0;
	int m_StarPiece1count2 = 0;
	int m_StarPiece1count3 = 0;

	//bool NotePage1 = false;	// 노트 오브젝트를 먹었는지
	//bool NotePage2 = false;
	//bool NotePage3 = false;

	// 노트 오브젝트를 먹었는지
	int m_NotePage = 0;

	//현재 부스트되고 있음?
	bool GetIsBoost()
	{
		return m_gracePeriod;
	}

private:
	bool m_isMusicStart;

	Vec2 temp;
	float m_boostSpeed = 150.0f;

	Vec2 m_UP = { 0.f, -1.f };
	Vec2 m_DOWN = { 0.f, 1.f };
	Vec2 m_LEFT = { -1.f, 0.f };
	Vec2 m_RIGHT = { 1.f, 0.f };

	Item* m_ItemObject;

	bool m_isDead;

	int m_boostCount;				// 부스터 횟수 체크
	float m_boostTimeCount;			// 부스터 상태일때 남은 부스터 시간	
	bool m_boostCoolTime;			// 부스터 장전 중인지 체크
	float m_boostCoolTimeCount;		// 부스터 쿨타임 체크
	bool m_gracePeriod;				// 무적

	float m_startPiece_1;
	float m_startPiece_2;
	float m_startPiece_3;

	//RECT m_hitbox;				// 히트박스
	//int m_hitboxHeightRadius;		// 히트박스 높이
	//int m_hitboxWidthRadius;		// 히트박스 너비

	void Move();					// 키 입력 받아 움직이기
	void Boost();					// 부스터
	void MoveAt(Vec2 direction);	// 움직이는 방향
	bool FollowCamera();			// 카메라 무빙 위치 지정

	bool whenKeyUp = false;

	//얘는 마지막에 있는 방향 기록하는 용도.
	//마지막 인풋이 왼쪽이었는지.
	bool lastDirIsLeft = false;

	int boostInnerCount;

	void ProjectileRenderText(); //개인 디버그용, 실제 빌드에 포함되면 안됨.

	//무적타임 재는 용도.
	std::chrono::steady_clock::time_point invinStartTime;
	std::chrono::steady_clock::time_point invinRecordTime;
	bool isInvinc = false;
};

