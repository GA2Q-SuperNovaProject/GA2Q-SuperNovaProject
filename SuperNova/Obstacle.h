#pragma once
#include "GameObject.h"
#include "StructDefine.h"

class Obstacle : public GameObject
{
public:
	Obstacle(eObjectTag tag, eObjectName name, Transform transform);
	~Obstacle();	
	
	virtual void Start() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

	bool PlayerTouch(); // �÷��̾�� �ε������� üũ�ϴ� �Լ�

private:
	Vec2 m_beginPos;
	void Sortation();

	void BlackHolePull(); //��Ȧ�� �������. (�Ÿ��� ����)
	void BlackHoleEvent();
	void MeasurePlayerDistance(); //�÷��̾�� ��Ȧ ������ �Ÿ� ��� ������Ʈ.
	bool m_checkhit;	// �÷��̾�� �ε�������

	//Rect2D m_hitbox;
	int m_meteorhitboxHeightRadius;
	int m_meteorhitboxWidthRadius;


	///[TW] ��� ����, �� ���� ������ ���� �ֵ�.
	GameObject* m_pPlayer;
	float m_distPlayerPow;

};

