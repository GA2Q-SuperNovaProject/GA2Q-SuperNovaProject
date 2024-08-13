#pragma once
#include "Vec2.h"
class Transform;

struct Body 
{
	Body(float mass, Transform* transform);
	~Body();

	//������ (�Ϲ�)
	Vec2 velocity;
	Vec2 acceleration;

	//�� ��.
	Vec2 sumForces;

	// �Ϲ� ����
	float mass;
	float invMass;
	Transform* bodyTransform;

	void AddForce(const Vec2& force);

	void ClearForces(); //Force Ŭ����

	void Integrate(Transform* transform); // �Ϲ� �Ÿ� ���� ���Ϸ� ����,
};

