#include "Body.h"
#include <iostream>
#include "Transform.h"
#include "TimeManager.h"
#include "Debug.h"

Body::Body(float mass, Transform* transform)
{
	//트랜스폼 
	bodyTransform = transform;

	this->velocity = Vec2(0, 0);
	this->acceleration = Vec2(0, 0);

	this->sumForces = Vec2(0, 0);

	//mass-invMass 설정하기
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

	//여기서 우리가 Transform을 실제로 받아서 실행해야 한다. 
	//Position을 거기서 받아오는 것.

	transform->m_Position += velocity * FIXED_FPS;

	ClearForces();
}

