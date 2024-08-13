#pragma once
#include "StructDefine.h"
/// 충돌 체크용 모듈. [TW]
class GameObject;

class CollisionDetection
{
public:
	//본격적인 게임 루프에서 이 함수들을 Nested-For 돌리면서 알아내야 한다.
	static void UpdateCollisionStates(GameObject* object);
	static bool DetectCollision(GameObject* baseObject, GameObject* otherObject);

private:
	static bool DetectOBB(GameObject* baseObject, GameObject* otherObject);
	static bool DetectAABB(GameObject* baseObject, GameObject* otherObject);
	static bool DetectCC(GameObject* baseObject, GameObject* otherObject);
	static bool DetectCircleRectangle(GameObject* circleObject, GameObject* rectObject);

	
};

// 총 세 가지 경우가 나올 수 있다. 
// Circle-Circle, Box-Box, Circle-Box.

//이 중에서도, Box-Box의 경우 Transform에 회전이 거의 들어가지 않았으면 AABB도 가능하다.
//아닌 경우에는 OBB를 수행해야.
