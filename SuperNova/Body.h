#pragma once
#include "Vec2.h"
class Transform;

struct Body 
{
	Body(float mass, Transform* transform);
	~Body();

	//선형적 (일반)
	Vec2 velocity;
	Vec2 acceleration;

	//힘 합.
	Vec2 sumForces;

	// 일반 질량
	float mass;
	float invMass;
	Transform* bodyTransform;

	void AddForce(const Vec2& force);

	void ClearForces(); //Force 클리어

	void Integrate(Transform* transform); // 일반 거리 기준 오일러 적분,
};

