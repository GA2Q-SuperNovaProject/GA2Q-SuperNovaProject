#include "Force.h"
#include <algorithm>
#include "GameObject.h"
#include "Camera.h"
#include "Transform.h"
//Body�� ���� ���� ������� ���...? => ���� ã�Ƴ��� �Ѵ�.


Vec2 Force::AddDragForce(GameObject* gameObject, float k)
{
	return AddDragForceWithBody(gameObject->GetPBody(), gameObject->GetPTransform(),k);
} 

Vec2 Force::AddFrictionForce(GameObject* gameObject, float k)
{
	return AddFrictionForceWithBody((gameObject->GetPBody()), gameObject->GetPTransform(), k);
}

//���� -> ������ �� ����.
Vec2 Force::AddGravityForce(GameObject* gameObject, GameObject* otherObject, float G, float minDistance, float maxDistance)
{
	Vec2 gameObjPos = gameObject->GetPTransform()->GetPosition();
	Vec2 otherObjPos = otherObject->GetPTransform()->GetPosition();
	
	if (gameObject->GetName() == eObjectName::PLAYER)
	{
		gameObjPos = Camera::GeInstance().CameraToWorldPOINT(gameObjPos);
	}
	
	if (otherObject->GetName() == eObjectName::PLAYER)
	{
		otherObjPos = Camera::GeInstance().CameraToWorldPOINT(otherObjPos);
	}

	return AddGravityForceWithBody((gameObject->GetPBody()), gameObjPos, (otherObject->GetPBody()), otherObjPos, G, minDistance, maxDistance);
}

Vec2 Force::AddSpringForce(GameObject* gameObject, const Vec2& anchor, float restLength, float k)
{
	return AddSpringForceWithBody((gameObject->GetPBody()), gameObject->GetPTransform(), anchor, restLength, k);
}

//������ �����ϴ� �� => Transform�� Position����. 
//

Vec2 Force::AddDragForceWithBody(const Body* body, Transform* bodyTransform, float k)
{
	Vec2 dragForce = Vec2(0, 0);
	if ((body->velocity).MagnitudeSquared() > 0)
	{
		//Drag Direction ��� (�ӵ� ���� ������ ��)
		Vec2 dragDirection = body->velocity.UnitVector() * (-1.0);
		float dragMagnitude = k * body->velocity.MagnitudeSquared();
		dragForce = dragDirection * dragMagnitude;
	}
	return dragForce;
}
Vec2 Force::AddFrictionForceWithBody(const Body* body, Transform* bodyTransform, float k)
{
	Vec2 frictionForce = Vec2(0, 0);
	Vec2 frictionDirection = body->velocity.UnitVector() * -1.0;
	float frictionMagnitude = k;
	frictionForce = frictionDirection * frictionMagnitude;
	return frictionForce;
}

//[TW] �ϴ��� ȣȯ�����ϰ� ����. ���� �߻��� �� ���� Ȯ�� �ʿ�.
Vec2 Force::AddGravityForceWithBody(const Body* a, Vec2 aPos, const Body* b, Vec2 bPos, float G, float minDistance, float maxDistance)
{
	Vec2 d = (bPos - aPos);
	float distanceSquared = d.MagnitudeSquared();

	//�ð��� ȿ���� ���� Clamp, C++ 17 �ʿ�.
	distanceSquared = std::clamp(distanceSquared, minDistance, maxDistance);

	Vec2 attractionDirection = d.UnitVector();
	float attractionMagnitude = G * (a->mass) * (b->mass) / distanceSquared; //�� Distance Squared�� Clamp�ؼ� ����� �� �ִ� ��!
	//distance squared�� ������ �ִ�! 
	//���ǿ��� ������ �𸣳�, ������ �Ѱ踦 �վ��.
	Vec2 attractionForce = attractionDirection * attractionMagnitude;
	return attractionForce;
}

Vec2 Force::AddSpringForceWithBody(const Body* p, Transform* bodyTransform, const Vec2& anchor, float restLength, float k)
{
	Vec2 dist = bodyTransform->GetPosition() - anchor;
	float displacement = dist.Magnitude() - restLength;
	Vec2 springDir = dist.UnitVector();
	float springMag = -k * displacement;
	Vec2 springForce = springDir * springMag;
	return springForce;
}

