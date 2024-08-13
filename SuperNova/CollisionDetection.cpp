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

/// [TW] CollisionDetection�� �� ������ �ͺ���,
/// �� ��ũ�� ũ�� ���ο� �����ϴ� ������Ʈ�� üũ�ϴ°� ��~�� ����.
/// �ݵ�� �߰��ؾ� �� ���.

void CollisionDetection::UpdateCollisionStates(GameObject* object)
{
	object->GetPCollider()->UpdateCollider(); //�Լ� ��ü�� For�� �ۿ��� ����Ǹ鼭 ���ư� ����.
}

bool CollisionDetection::DetectCollision(GameObject* baseObject, GameObject* otherObject)
{
	if (!(baseObject->GetColState()) || !(otherObject->GetColState()) ||
		baseObject->GetColType() == eColType::NONE || otherObject->GetColType() == eColType::NONE)
	{
		return false; //�ݶ��̴� ��� ���̶� ���� ������ ��� �� �ʿ�X.
	}
	else //�Ѵ� �ݶ��̴��� ���� �ִ� ���.
	{
		if (baseObject->GetColType() == eColType::BOX &&
			otherObject->GetColType() == eColType::BOX) //�� �� �ڽ�
		{
			if (fabs(baseObject->GetPTransform()->GetRotation()) < Math::Epsilon() &&
				fabs(otherObject->GetPTransform()->GetRotation()) < Math::Epsilon()) //������ �� �־�����..?
			{
				//Debug::Trace("AABB LOGIC");
				return DetectAABB(baseObject, otherObject); //AABB //[TW] ��ħ.
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
				return DetectCircleRectangle(baseObject, otherObject); //��-���簢��
			}
			else
			{
				return DetectCircleRectangle(otherObject, baseObject); //��-���簢��, ������ ������ ����
			}
		}
	}
}

bool CollisionDetection::DetectOBB(GameObject* baseObject, GameObject* otherObject)
{
	//�Ѵ� BOX
	BoxCollider* baseCollider = static_cast<BoxCollider*>(baseObject->GetPCollider());
	BoxCollider* otherCollider = static_cast<BoxCollider*>(otherObject->GetPCollider());

	Vec2Rect baseRect = baseCollider->GetWorldRect();
	Vec2Rect otherRect = otherCollider->GetWorldRect(); //���� �޾ƿ�.

	//Ʈ������ ��ȯ �ϵ��ڵ�
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
	//�Ѵ� BOX.
	BoxCollider* baseCollider = static_cast<BoxCollider*>(baseObject->GetPCollider());
	BoxCollider* otherCollider = static_cast<BoxCollider*>(otherObject->GetPCollider());

	Vec2Rect baseRect = baseCollider->GetWorldRect();
	Vec2Rect otherRect = otherCollider->GetWorldRect();

	//Ʈ������ ��ȯ �ϵ��ڵ�
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
	//�Ѵ� CIRCLE.
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

//��-���簢�� ����.
bool CollisionDetection::DetectCircleRectangle(GameObject* circleObject, GameObject* rectObject)
{
	//����Ʈ���� ���� �ٸ� �ݶ��̴��� ������ �ִ�. �����صѰ�. [TW]
	//�ϳ��� BOX, �ϳ��� CIRCLE.
	CircleCollider* circleCollider = static_cast<CircleCollider*>(circleObject->GetPCollider());
	BoxCollider* boxCollider = static_cast<BoxCollider*>(rectObject->GetPCollider());

	Vec2Circle baseCircle = circleCollider->GetWorldCircle();
	Vec2Rect otherRect = boxCollider->GetWorldRect();

	//Ʈ������ ��ȯ �ϵ��ڵ�
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
//���� OBB Rectangle ���� �浹 ���� �켱, �� �Ŀ� �ø��� ������.

//Dot Product�� ���� -> ������ ���� (������) ���簢�� �ȿ� ���� �ִ��� üũ�� �� �ִ�.
//���⼭ ���� ���簢�� ��? => �浹.

//���� ���� ���簢�� ��?
//���簢���� �� ���� �������� ����,
//�� ���к��� ���� �������� �Ÿ��� ���Ѵ�.
//���� ª�� �Ÿ��� ���� ���� ��������, �ش� ���а� ���������� �Ÿ� <= �������̸�, �浹.
//�ƴϸ� �浹 �ƴ�.

//���� Line Segment(����) ������ ���� ª�� �Ÿ��� �˾Ƴ�����?
//���� ���� ���̸� ���� ��(���� ����), ���� ������ ���� �ȿ� �ִ��� üũ. 
//���� �ȿ� ���� �ִ� ��� -> �� �������� ���� �Ÿ��� ���� ª�� �Ÿ�
//���� �ȿ� ���� ���� �ʴ� ��� -> ������ �� ������ ��, �� ���� ����� ���ܿ��� �������� �Ÿ��� ���� ª�� �Ÿ��̴�.
