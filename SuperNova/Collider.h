#pragma once
#include "Vec2.h"
#include "FixedQueue.h"

class Transform;
class GameObject;

class Collider 
{
public:
	Collider(const Transform& transform, int imageIndex); //무조건 Transform을 받아서 생성.
	virtual ~Collider();

	virtual void UpdateCollider() = 0; //순수 가상.

	//Position은 실시간으로 계산되어야 한다. 행렬을 활용해서.
	//실시간으로 포지션을 안 다음에, 어떻게 해야 되는가?
	//그 다음에는 CollisionDetection이라는 다른 클래스로 이동되어, 
	//Collider가 대령되어 계산된다. 
	//과감히 상속 구조를 버릴까..? 
	//Box의 경우는, Width와 Height이 필요하고,
	//Circle의 경우는, Radius에 기초한 판단이 필요한 상황이다.
	//아니다. 이 경우, 자료형이 확실하니, 형변환을 통해 사용하면 된다.
	//GetWidth/Height/Radius / Rect 등등.. 
	//Collider*로 인식된 애들을 GameObject*에서 GetColType으로 비교하고,
	//다운캐스팅하면 되는 문제 (문제없음, 원체 파생 타입 -> 업캐스팅 -> 다운캐스팅)
	//GetPosition은 전체 Collider 분류에 포함. [TW]

	void SetOtherCollidedObject(GameObject* other); // 충돌한 자신 말고 다른 오브젝트를 세팅.
	GameObject* GetOtherCollidedObject(); // 충돌한 자신 말고 다른 오브젝트를 게팅.

protected:
	const Transform* m_pTransform; //여기서 변화시키는 일은 없다. 값만 가져올 뿐.
	int m_imageIndex; 

	//임의로, 충돌한 애를 반환해주는 친구이다.
	//CollisionManager가 해주는 일. 
	GameObject* otherCollidedObject; 
	//Rp
	//Width/Height 판별 위해. 개인적으로 잘못된 위치라고 생각들지만,
	//일은 충분히 해낼 것이다.

	
};

