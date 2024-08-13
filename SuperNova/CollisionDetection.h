#pragma once
#include "StructDefine.h"
/// �浹 üũ�� ���. [TW]
class GameObject;

class CollisionDetection
{
public:
	//�������� ���� �������� �� �Լ����� Nested-For �����鼭 �˾Ƴ��� �Ѵ�.
	static void UpdateCollisionStates(GameObject* object);
	static bool DetectCollision(GameObject* baseObject, GameObject* otherObject);

private:
	static bool DetectOBB(GameObject* baseObject, GameObject* otherObject);
	static bool DetectAABB(GameObject* baseObject, GameObject* otherObject);
	static bool DetectCC(GameObject* baseObject, GameObject* otherObject);
	static bool DetectCircleRectangle(GameObject* circleObject, GameObject* rectObject);

	
};

// �� �� ���� ��찡 ���� �� �ִ�. 
// Circle-Circle, Box-Box, Circle-Box.

//�� �߿�����, Box-Box�� ��� Transform�� ȸ���� ���� ���� �ʾ����� AABB�� �����ϴ�.
//�ƴ� ��쿡�� OBB�� �����ؾ�.
