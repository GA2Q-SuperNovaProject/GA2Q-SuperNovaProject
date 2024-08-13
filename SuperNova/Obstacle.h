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

	bool PlayerTouch(); // 플레이어랑 부딪혔는지 체크하는 함수

private:
	Vec2 m_beginPos;
	void Sortation();

	void BlackHolePull(); //블랙홀로 끌어당긴다. (거리에 따라서)
	void BlackHoleEvent();
	void MeasurePlayerDistance(); //플레이어와 블랙홀 사이의 거리 계속 업데이트.
	bool m_checkhit;	// 플레이어랑 부딪혔는지

	//Rect2D m_hitbox;
	int m_meteorhitboxHeightRadius;
	int m_meteorhitboxWidthRadius;


	///[TW] 멤버 변수, 인 게임 로직에 사용될 애들.
	GameObject* m_pPlayer;
	float m_distPlayerPow;

};

