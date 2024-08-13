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

	//bool NotePage1 = false;	// ��Ʈ ������Ʈ�� �Ծ�����
	//bool NotePage2 = false;
	//bool NotePage3 = false;

	// ��Ʈ ������Ʈ�� �Ծ�����
	int m_NotePage = 0;

	//���� �ν�Ʈ�ǰ� ����?
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

	int m_boostCount;				// �ν��� Ƚ�� üũ
	float m_boostTimeCount;			// �ν��� �����϶� ���� �ν��� �ð�	
	bool m_boostCoolTime;			// �ν��� ���� ������ üũ
	float m_boostCoolTimeCount;		// �ν��� ��Ÿ�� üũ
	bool m_gracePeriod;				// ����

	float m_startPiece_1;
	float m_startPiece_2;
	float m_startPiece_3;

	//RECT m_hitbox;				// ��Ʈ�ڽ�
	//int m_hitboxHeightRadius;		// ��Ʈ�ڽ� ����
	//int m_hitboxWidthRadius;		// ��Ʈ�ڽ� �ʺ�

	void Move();					// Ű �Է� �޾� �����̱�
	void Boost();					// �ν���
	void MoveAt(Vec2 direction);	// �����̴� ����
	bool FollowCamera();			// ī�޶� ���� ��ġ ����

	bool whenKeyUp = false;

	//��� �������� �ִ� ���� ����ϴ� �뵵.
	//������ ��ǲ�� �����̾�����.
	bool lastDirIsLeft = false;

	int boostInnerCount;

	void ProjectileRenderText(); //���� ����׿�, ���� ���忡 ���ԵǸ� �ȵ�.

	//����Ÿ�� ��� �뵵.
	std::chrono::steady_clock::time_point invinStartTime;
	std::chrono::steady_clock::time_point invinRecordTime;
	bool isInvinc = false;
};

