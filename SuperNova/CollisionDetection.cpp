#include "CollisionDetection.h"
#include "GameObject.h"
#include "StructDefine.h"
#include "EnumDefine.h"
#include "Transform.h"
#include "Math.h"
#include "Collider.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include <limits>
#include <algorithm>
#include "Debug.h"
#include "CollideInfoMap.h"
#include "Camera.h"


constexpr float FLOATMAX = std::numeric_limits<float>::max();
constexpr float FLOATMIN= std::numeric_limits<float>::min();

/// [TW] CollisionDetection을 다 돌리는 것보다,
/// 현 스크린 크기 내부에 존재하는 오브젝트만 체크하는게 훨~씬 낫다.
/// 반드시 추가해야 할 기능.

void CollisionDetection::UpdateCollisionStates(GameObject* object)
{
	object->GetPCollider()->UpdateCollider(); //함수 자체가 For문 밖에서 실행되면서 돌아갈 예정.
}

bool CollisionDetection::DetectCollision(GameObject* baseObject, GameObject* otherObject)
{
	if (!(baseObject->GetColState()) || !(otherObject->GetColState()) ||
		baseObject->GetColType() == eColType::NONE || otherObject->GetColType() == eColType::NONE)
	{
		return false; //콜라이더 어느 것이라도 꺼져 있으면 계산 할 필요X.
	}
	else //둘다 콜라이더가 켜져 있는 경우.
	{
		if (baseObject->GetColType() == eColType::BOX &&
			otherObject->GetColType() == eColType::BOX) //둘 다 박스
		{
			if (fabs(baseObject->GetPTransform()->GetRotation()) < Math::Epsilon() &&
				fabs(otherObject->GetPTransform()->GetRotation()) < Math::Epsilon()) //각도가 안 휘어졌다..?
			{
				//Debug::Trace("AABB LOGIC");
				return DetectAABB(baseObject, otherObject); //AABB //[TW] 고침.
			}
			else
			{
				//Debug::Trace("OBB LOGIC");
				return DetectOBB(baseObject, otherObject); //OBB
			}
		}
		else if (baseObject->GetColType() == eColType::CIRCLE &&
			otherObject->GetColType() == eColType::CIRCLE)
		{
			//Debug::Trace("CC LOGIC");
			return DetectCC(baseObject, otherObject); //CC
		}
		else
		{
			//Debug::Trace("CircleRect LOGIC");
			if (baseObject->GetColType() == eColType::CIRCLE &&
				otherObject->GetColType() == eColType::BOX)
			{
				return DetectCircleRectangle(baseObject, otherObject); //원-직사각형
			}
			else
			{
				return DetectCircleRectangle(otherObject, baseObject); //원-직사각형, 하지만 뒤집힌 형태
			}
		}
	}
}

bool CollisionDetection::DetectOBB(GameObject* baseObject, GameObject* otherObject)
{
	//둘다 BOX
	BoxCollider* baseCollider = static_cast<BoxCollider*>(baseObject->GetPCollider());
	BoxCollider* otherCollider = static_cast<BoxCollider*>(otherObject->GetPCollider());

	Vec2Rect baseRect = baseCollider->GetWorldRect();
	Vec2Rect otherRect = otherCollider->GetWorldRect(); //값을 받아옴.

	//트랜스폼 변환 하드코딩
	if (baseObject->GetTag() == eObjectTag::PLAYER /*||
		baseObject->GetTag() == eObjectTag::BULLET*/)
	{
		Camera::GeInstance().Vec2RectToCameraPOINT(baseRect);
	}

	if (otherObject->GetTag() == eObjectTag::PLAYER/* ||
		otherObject->GetTag() == eObjectTag::BULLET*/)
	{
		Camera::GeInstance().Vec2RectToCameraPOINT(otherRect);
	}

	Vec2 basePosArray[4] = { baseRect.topLeft, baseRect.topRight, baseRect.bottomRight, baseRect.bottomLeft };
	Vec2 otherPosArray[4] = { otherRect.topLeft, otherRect.topRight, otherRect.bottomRight, otherRect.bottomLeft };

	Vec2 dirArray[8];
	for (int i = 0; i < 8; ++i)
	{
		if (i < 4)
			dirArray[i] = basePosArray[i % 4] - basePosArray[(i + 1) % 4];
		else
			dirArray[i] = otherPosArray[i % 4] - otherPosArray[(i + 1) % 4];
	}

	//float b_tlDot = a_tr_br.Dot(otherRect.topLeft);
	//float b_trDot = a_tr_br.Dot(otherRect.topRight);
	//float b_brDot = a_tr_br.Dot(otherRect.bottomLeft);
	//float b_blDot = a_tr_br.Dot(otherRect.bottomRight);

	float dotListBase[4];
	float dotListOther[4];
	float baseRectMax;
	float baseRectMin;
	float otherRectMax;
	float otherRectMin;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			dotListBase[j] = dirArray[i].Dot(basePosArray[j]);
		}

		for (int j = 0; j < 4; j++)
		{
			dotListOther[j] = dirArray[i].Dot(otherPosArray[j]);
		}

		otherRectMin = FLOATMAX;
		otherRectMax = FLOATMIN;

		baseRectMin = FLOATMAX;
		baseRectMax = FLOATMIN;

		for (int j = 0; j < 4; j++)
		{
			if (otherRectMin > dotListOther[j])
			{							   
				otherRectMin = dotListOther[j];
			}
		}

		for (int j = 0; j < 4; j++)
		{
			if (otherRectMax < dotListOther[j])
			{
				otherRectMax = dotListOther[j];
			}
		}

		for (int j = 0; j < 4; j++)
		{
			if (baseRectMin > dotListBase[j])
			{
				baseRectMin = dotListBase[j];
			}
		}

		for (int j = 0; j < 4; j++)
		{
			if (baseRectMax < dotListBase[j])
			{
				baseRectMax = dotListBase[j];
			}
		}

		if (baseRectMax < otherRectMin || baseRectMin > otherRectMax)
		{
			return false;
		}
	}

	return true;
}

bool CollisionDetection::DetectAABB(GameObject* baseObject, GameObject* otherObject)
{
	//둘다 BOX.
	BoxCollider* baseCollider = static_cast<BoxCollider*>(baseObject->GetPCollider());
	BoxCollider* otherCollider = static_cast<BoxCollider*>(otherObject->GetPCollider());

	Vec2Rect baseRect = baseCollider->GetWorldRect();
	Vec2Rect otherRect = otherCollider->GetWorldRect();

	//트랜스폼 변환 하드코딩
	if (baseObject->GetTag() == eObjectTag::PLAYER/* ||
		baseObject->GetTag() == eObjectTag::BULLET*/)
	{
		Camera::GeInstance().Vec2RectToCameraPOINT(baseRect);
	}

	if (otherObject->GetTag() == eObjectTag::PLAYER/* ||
		otherObject->GetTag() == eObjectTag::BULLET*/)
	{
		Camera::GeInstance().Vec2RectToCameraPOINT(otherRect);
	}

	float baseWidth = fabs(baseRect.topRight.x - baseRect.topLeft.x);
	float baseHeight = fabs(baseRect.topRight.y - baseRect.bottomRight.y);
	//Vec2 basePos((baseRect.topLeft.x + baseRect.topRight.x) / 2.0f, (baseRect.topRight.y + baseRect.bottomRight.y) / 2.0f);
	Vec2 basePos = baseRect.topLeft;
	float otherWidth = fabs(otherRect.topRight.x - otherRect.topLeft.x);
	float otherHeight = fabs(otherRect.topRight.y - otherRect.bottomRight.y);
	Vec2 otherPos = otherRect.topLeft;

	if (basePos.x < otherPos.x + otherWidth &&
		basePos.x + baseWidth > otherPos.x &&
		basePos.y < otherPos.y + otherHeight &&
		basePos.y + baseHeight > otherPos.y)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CollisionDetection::DetectCC(GameObject* baseObject, GameObject* otherObject)
{
	//둘다 CIRCLE.
	CircleCollider* baseCollider = static_cast<CircleCollider*>(baseObject->GetPCollider());
	CircleCollider* otherCollider = static_cast<CircleCollider*>(otherObject->GetPCollider());

	Vec2Circle baseCircle = baseCollider->GetWorldCircle();
	Vec2Circle otherCircle = otherCollider->GetWorldCircle();

	if (baseObject->GetTag() == eObjectTag::PLAYER /*||
		baseObject->GetTag() == eObjectTag::BULLET*/)
	{
		Camera::GeInstance().Vec2CircleToCameraPOINT(baseCircle);
	}

	if (otherObject->GetTag() == eObjectTag::PLAYER /*||
		otherObject->GetTag() == eObjectTag::BULLET*/)
	{
		Camera::GeInstance().Vec2CircleToCameraPOINT(otherCircle);
	}

	float distanceBetweenPow = pow(baseCircle.position.x - otherCircle.position.x, 2) + pow(baseCircle.position.y - otherCircle.position.y, 2);
	float addedRadiusPow = pow(baseCircle.radius, 2) + pow(otherCircle.radius, 2);

	if (addedRadiusPow >= distanceBetweenPow)
	{
		return true;

	}
	else
	{
		return false;
	}
}

//원-직사각형 순서.
bool CollisionDetection::DetectCircleRectangle(GameObject* circleObject, GameObject* rectObject)
{
	//옵젝트들은 서로 다른 콜라이더를 가지고 있다. 유념해둘것. [TW]
	//하나는 BOX, 하나는 CIRCLE.
	CircleCollider* circleCollider = static_cast<CircleCollider*>(circleObject->GetPCollider());
	BoxCollider* boxCollider = static_cast<BoxCollider*>(rectObject->GetPCollider());

	Vec2Circle baseCircle = circleCollider->GetWorldCircle();
	Vec2Rect otherRect = boxCollider->GetWorldRect();

	//트랜스폼 변환 하드코딩
	if (circleObject->GetTag() == eObjectTag::PLAYER /*||
		circleObject->GetTag() == eObjectTag::BULLET*/)
	{
		Camera::GeInstance().Vec2CircleToCameraPOINT(baseCircle);
	}

	if (rectObject->GetTag() == eObjectTag::PLAYER /*||
		rectObject->GetTag() == eObjectTag::BULLET*/)
	{
		Camera::GeInstance().Vec2RectToCameraPOINT(otherRect);
	}

	bool isInner = Math::PointInOBBRectangle(otherRect, baseCircle.position);

	if (isInner)
	{
		return true;
	}
	else
	{
		double tmp = Math::DistancePointToLineSegment(otherRect.topLeft, otherRect.topRight, baseCircle.position);
		double tmp2 = Math::DistancePointToLineSegment(otherRect.topRight, otherRect.bottomRight, baseCircle.position);
		double tmp3 = Math::DistancePointToLineSegment(otherRect.bottomRight, otherRect.bottomLeft, baseCircle.position);
		double tmp4 = Math::DistancePointToLineSegment(otherRect.bottomLeft, otherRect.topLeft, baseCircle.position);

		std::initializer_list<double> init{ tmp,tmp2,tmp3,tmp4 };
		double minDist = std::min<double>(init);

		if (minDist <= baseCircle.radius)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}


// [TW] Circle - Rectangle? 
//점과 OBB Rectangle 사이 충돌 여부 우선, 그 후에 늘리는 것으로.

//Dot Product를 쓰면 -> 내적을 통해 (기울어진) 직사각형 안에 점이 있는지 체크할 수 있다.
//여기서 점이 직사각형 안? => 충돌.

//점이 만약 직사각형 밖?
//직사각형을 네 개의 선분으로 보고,
//각 선분별로 원의 원점과의 거리를 구한다.
//가장 짧은 거리를 가진 선분 기준으로, 해당 선분과 원점사이의 거리 <= 반지름이면, 충돌.
//아니면 충돌 아님.

//점과 Line Segment(선분) 사이의 가장 짧은 거리를 알아내려면?
//점과 직선 사이를 구한 후(수직 접점), 접선 지점이 선분 안에 있는지 체크. 
//선분 안에 속해 있는 경우 -> 그 수직으로 가는 거리가 가장 짧은 거리
//선분 안에 속해 있지 않는 경우 -> 선분의 양 끝단을 비교, 더 점과 가까운 끝단에서 점까지의 거리가 가장 짧은 거리이다.
