#pragma once
#include <chrono>
#include "GameObject.h"
#include "Transform.h"

class Player;

class Planet : public GameObject
{
public:
	Planet(eObjectTag tag, eObjectName name, Transform transform);
	~Planet();

	virtual void Start() override;
	virtual void Update() override;
	virtual void Render() override;

private:
	Vec2 m_beginPos;
	void Sortation();
	GameObject* playerObject;

	//블랙홀(보다 살짝 약하게) 플레이어를 끌어당긴다.
	void MeasurePlayerDistance();
	void GravitationalPull();
	void PlanetCrashEvent();
	float m_distPlayerPow;

	//플레이어를 위한 무적 타임 계산.
	std::chrono::steady_clock::time_point invinStartTime;
	std::chrono::steady_clock::time_point invinRecordTime;

	bool isInvinc = false;

	Player* playerPointer = nullptr;
	

	bool hardToggle = false;

	bool part1 = false;
	bool part2 = false;
	bool part3 = false;
};

