#include "Body.h"
#include <iostream>
#include "Transform.h"
#include "TimeManager.h"
#include "Debug.h"

Body::Body(float mass, Transform* transform)
{
	//Ʈ������ 
	bodyTransform = transform;

	this->velocity = Vec2(0, 0);
	this->acceleration = Vec2(0, 0);

	this->sumForces = Vec2(0, 0);

	//mass-invMass �����ϱ�
	this->mass = mass;
	if (mass != 0.0) 
	{
		this->invMass = 1.0 / mass;
	}
	else 
	{
		this->invMass = 0.0;
	}
	//Debug::Trace("Body Made");
}

Body::~Body()
{
	//Debug::Trace("Body Destroyed");
}

void Body::AddForce(const Vec2& force)
{
	sumForces += force;
}

void Body::ClearForces() 
{
	sumForces = Vec2(0.0, 0.0);
}

void Body::Integrate(Transform* transform) {
	
	acceleration = sumForces * invMass;

	velocity += acceleration * FIXED_FPS;

	//���⼭ �츮�� Transform�� ������ �޾Ƽ� �����ؾ� �Ѵ�. 
	//Position�� �ű⼭ �޾ƿ��� ��.

	transform->m_Position += velocity * FIXED_FPS;

	ClearForces();
}

