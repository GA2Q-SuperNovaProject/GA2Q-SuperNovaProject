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

	//��Ȧ(���� ��¦ ���ϰ�) �÷��̾ �������.
	void MeasurePlayerDistance();
	void GravitationalPull();
	void PlanetCrashEvent();
	float m_distPlayerPow;

	//�÷��̾ ���� ���� Ÿ�� ���.
	std::chrono::steady_clock::time_point invinStartTime;
	std::chrono::steady_clock::time_point invinRecordTime;

	bool isInvinc = false;

	Player* playerPointer = nullptr;
	

	bool hardToggle = false;

	bool part1 = false;
	bool part2 = false;
	bool part3 = false;
};

