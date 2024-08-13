#include "Force.h"
#include <algorithm>
#include "GameObject.h"
#include "Camera.h"
#include "Transform.h"
//Body가 돌고 나면 사라지는 경우...? => 원인 찾아내야 한다.


Vec2 Force::AddDragForce(GameObject* gameObject, float k)
{
	return AddDragForceWithBody(gameObject->GetPBody(), gameObject->GetPTransform(),k);
} 

Vec2 Force::AddFrictionForce(GameObject* gameObject, float k)
{
	return AddFrictionForceWithBody((gameObject->GetPBody()), gameObject->GetPTransform(), k);
}

//왼쪽 -> 오른쪽 힘 적용.
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

//실제로 적용하는 일 => Transform은 Position으로. 
//

Vec2 Force::AddDragForceWithBody(const Body* body, Transform* bodyTransform, float k)
{
	Vec2 dragForce = Vec2(0, 0);
	if ((body->velocity).MagnitudeSquared() > 0)
	{
		//Drag Direction 계산 (속도 단위 벡터의 역)
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

//[TW] 일단은 호환가능하게 수정. 문제 발생시 본 로직 확대 필요.
Vec2 Force::AddGravityForceWithBody(const Body* a, Vec2 aPos, const Body* b, Vec2 bPos, float G, float minDistance, float maxDistance)
{
	Vec2 d = (bPos - aPos);
	float distanceSquared = d.MagnitudeSquared();

	//시각적 효과를 위한 Clamp, C++ 17 필요.
	distanceSquared = std::clamp(distanceSquared, minDistance, maxDistance);

	Vec2 attractionDirection = d.UnitVector();
	float attractionMagnitude = G * (a->mass) * (b->mass) / distanceSquared; //이 Distance Squared를 Clamp해서 사용할 수 있는 것!
	//distance squared로 나누고 있다! 
	//현실에는 맞을지 모르나, 게임적 한계를 뚫어야.
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

