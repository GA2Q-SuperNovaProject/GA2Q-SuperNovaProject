#pragma once
#include <string>
#include "IUpdatable.h"
#include "Vec2.h"
#include "EnumDefine.h"
#include "FixedQueue.h"
#include "Body.h"
#include "Force.h"

class Transform;
class Collider;
class BoxCollider;
class CircleCollider;
class Scene;

// GameObject들의 부모클래스
class GameObject : public IUpdatable
{
	friend class CollisionDetection; //충돌 체크 판정을 위해 Friend가 된다! 헤더 별도 include 필요X.
	friend class CollisionManager; 
	friend class PhysicsManager;
public:
	///[TW] 더 이상은 통용되지 않는다. 이제부터 Vec2 Position의 위치에는 Transform을 넣어야!
	/// 또한, 부탁... 충돌처리되는 오브젝트들은, 웬만하면 Scale Vector를 (1,1)로 유지해주세용.
	GameObject(eObjectTag tag, eObjectName name, Transform transform, int imageIndex);
	GameObject(eObjectTag tag, eObjectName name, Transform transform);
	virtual ~GameObject();

	//Start 함수 형태 정의 태욱이바보(Scene 변경/시작 시 한번만 시행된다.)
	virtual void Start();

	// 객체 로직 관련 업데이트
	// 물리 적용 후 물리 판정 필요
	virtual void Update() override;

	//물리관련 충돌 관련 판정이 필요하면, LateUpdate()에서 실행해야 한다.
	virtual void LateUpdate();

	//[TW] 물리 실행 로직을 실행할 수 있다. 무조건 오버라이드가 되어야 한다.
	//ex. 물리 관련해서 다른 애들한테 힘을 가하고 싶다? 무조건 얘를 통해서.
	
	
	//소팅 레이어
	bool isfrontRender = false;

	// 객체 렌더 
	virtual void Render() override;



	virtual Transform* GetPTransform(); //pTransform을 변환해주는 함수.
	virtual Collider* GetPCollider(); //pCollider을 변환해주는 함수.
	virtual Body* GetPBody(); //m_pBody를 리턴해주는 함수.
	//이제는 Collision담당을 위해 처리해야 한다.
	
	//얘는 찾아서 리턴해주는 친구, (내부적으로 fixedPlayerObject에 할당)
	GameObject* FetchPlayerObject();

	//얘는 Update에 박아둬도 부하안걸림. fixedPlayerObject가 nullptr일때만 찾는다.
	// 중요: 추후에 SceneChange시에 fixedPlayerObject를 nullptr로 만드는게 중요.
	//이는, 상호 안전성 체크를 하고 바꿀것.
	void FixPlayerSafeInUpdate();
	

	eObjectTag GetTag() const { return m_tag; }
	void SetTag(eObjectTag val) { m_tag = val; }

	eObjectName GetName() const { return m_name; }
	void SetName(eObjectName val) { m_name = val; }

	int GetImageIndex() const { return m_imageIndex; }
	void SetImageIndex(int val) { m_imageIndex = val; }

	//[TW] 콜라이더를 넣을지 설정. 디폴트로는 꺼져 있음. 함수 발동시 자동으로 켜짐.
	//이미지 인덱스를 전달하는 이유? => Width/Height/Radius를 받아서 Collider 정보 전달 위함!
	virtual void PutCollider(eColType colliderType, int imageIndex);

	//(충돌 처리 관련X) 물리 원칙의 적용을 받을 것인지를 결정하는 친구
	//SetPhysics가 True일 경우, new를 통해 Body를 만들어 배정해준다.
	///[TW] 주의점~! 얘는 절대 게임 중에 왔다갔다 하면 안됨. ReadyScene에다가만 해야.
	virtual void PutBody(int mass);

	bool GetColState(); //콜라이더의 상태를 가져온다!
	void SetColState(bool state); //콜라이더 킬지 끌지

	eColType GetColType(); //콜라이더의 분류를 가져온다!


	//얘는 일반적으로 오브젝트에서 사용하면 안된다.
	bool GetIsCollided() const { return isCollided; }

	//얘는 일반적으로 오브젝트에서 사용하면 안된다.
	void SetIsCollided(bool val) { isCollided = val; }

	//이걸 트루라고 해야 적용이 됨. 물리가 적용되는 기준이다.
	void SetPhysicsState(bool state);

	//물리가 켜져 있는지 반환을 해준다.
	bool GetPhysicsState();

	Scene* belongScene; //자신이 속해 있는 Scene.

	//Setter는 Ready Scene 말고 절대 변화될 리가 없다.

	//Getter는 반대로, 이를 가지고 Collider마다 계산을 하게 된다. 

	///Force를 추가적으로 사용할 때, AddForce를 사용한다.
	//AddForce를 쉽게 사용할 수 있게.
	void AddForce(Vec2 force);
	void TurnOffCollider();

	GameObject* fixedPlayerObject = nullptr;

protected:
	eObjectTag m_tag;
	eObjectName m_name;
	int m_imageIndex;
	Transform* m_pTransform;
	eColType m_ColliderType;
	bool m_CanCollide = false; //[TW] 콜라이더로 부딪히는지. 설정.
	Collider* m_pCollider;
	Body* m_pBody = nullptr;
	bool isCollided = false; //얘는 기본적으로 현재 자신의 오브젝트가 충돌했는지 아닌지만 리턴.

	bool isPhysicsOn = false;
	
	//우리는 기본적으로
	//카메라 : Local Space. (따로 변형될 필요가 없다)
	//UI : Local Space.  
	//행성, 탄막, etc. :: 월드 스페이스. `

	//WorldToCameraPOINT. (월드 -> 로컬)

};

