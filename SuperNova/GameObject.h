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

// GameObject���� �θ�Ŭ����
class GameObject : public IUpdatable
{
	friend class CollisionDetection; //�浹 üũ ������ ���� Friend�� �ȴ�! ��� ���� include �ʿ�X.
	friend class CollisionManager; 
	friend class PhysicsManager;
public:
	///[TW] �� �̻��� ������ �ʴ´�. �������� Vec2 Position�� ��ġ���� Transform�� �־��!
	/// ����, ��Ź... �浹ó���Ǵ� ������Ʈ����, �����ϸ� Scale Vector�� (1,1)�� �������ּ���.
	GameObject(eObjectTag tag, eObjectName name, Transform transform, int imageIndex);
	GameObject(eObjectTag tag, eObjectName name, Transform transform);
	virtual ~GameObject();

	//Start �Լ� ���� ���� �¿��̹ٺ�(Scene ����/���� �� �ѹ��� ����ȴ�.)
	virtual void Start();

	// ��ü ���� ���� ������Ʈ
	// ���� ���� �� ���� ���� �ʿ�
	virtual void Update() override;

	//�������� �浹 ���� ������ �ʿ��ϸ�, LateUpdate()���� �����ؾ� �Ѵ�.
	virtual void LateUpdate();

	//[TW] ���� ���� ������ ������ �� �ִ�. ������ �������̵尡 �Ǿ�� �Ѵ�.
	//ex. ���� �����ؼ� �ٸ� �ֵ����� ���� ���ϰ� �ʹ�? ������ �긦 ���ؼ�.
	
	
	//���� ���̾�
	bool isfrontRender = false;

	// ��ü ���� 
	virtual void Render() override;



	virtual Transform* GetPTransform(); //pTransform�� ��ȯ���ִ� �Լ�.
	virtual Collider* GetPCollider(); //pCollider�� ��ȯ���ִ� �Լ�.
	virtual Body* GetPBody(); //m_pBody�� �������ִ� �Լ�.
	//������ Collision����� ���� ó���ؾ� �Ѵ�.
	
	//��� ã�Ƽ� �������ִ� ģ��, (���������� fixedPlayerObject�� �Ҵ�)
	GameObject* FetchPlayerObject();

	//��� Update�� �ھƵֵ� ���ϾȰɸ�. fixedPlayerObject�� nullptr�϶��� ã�´�.
	// �߿�: ���Ŀ� SceneChange�ÿ� fixedPlayerObject�� nullptr�� ����°� �߿�.
	//�̴�, ��ȣ ������ üũ�� �ϰ� �ٲܰ�.
	void FixPlayerSafeInUpdate();
	

	eObjectTag GetTag() const { return m_tag; }
	void SetTag(eObjectTag val) { m_tag = val; }

	eObjectName GetName() const { return m_name; }
	void SetName(eObjectName val) { m_name = val; }

	int GetImageIndex() const { return m_imageIndex; }
	void SetImageIndex(int val) { m_imageIndex = val; }

	//[TW] �ݶ��̴��� ������ ����. ����Ʈ�δ� ���� ����. �Լ� �ߵ��� �ڵ����� ����.
	//�̹��� �ε����� �����ϴ� ����? => Width/Height/Radius�� �޾Ƽ� Collider ���� ���� ����!
	virtual void PutCollider(eColType colliderType, int imageIndex);

	//(�浹 ó�� ����X) ���� ��Ģ�� ������ ���� �������� �����ϴ� ģ��
	//SetPhysics�� True�� ���, new�� ���� Body�� ����� �������ش�.
	///[TW] ������~! ��� ���� ���� �߿� �Դٰ��� �ϸ� �ȵ�. ReadyScene���ٰ��� �ؾ�.
	virtual void PutBody(int mass);

	bool GetColState(); //�ݶ��̴��� ���¸� �����´�!
	void SetColState(bool state); //�ݶ��̴� ų�� ����

	eColType GetColType(); //�ݶ��̴��� �з��� �����´�!


	//��� �Ϲ������� ������Ʈ���� ����ϸ� �ȵȴ�.
	bool GetIsCollided() const { return isCollided; }

	//��� �Ϲ������� ������Ʈ���� ����ϸ� �ȵȴ�.
	void SetIsCollided(bool val) { isCollided = val; }

	//�̰� Ʈ���� �ؾ� ������ ��. ������ ����Ǵ� �����̴�.
	void SetPhysicsState(bool state);

	//������ ���� �ִ��� ��ȯ�� ���ش�.
	bool GetPhysicsState();

	Scene* belongScene; //�ڽ��� ���� �ִ� Scene.

	//Setter�� Ready Scene ���� ���� ��ȭ�� ���� ����.

	//Getter�� �ݴ��, �̸� ������ Collider���� ����� �ϰ� �ȴ�. 

	///Force�� �߰������� ����� ��, AddForce�� ����Ѵ�.
	//AddForce�� ���� ����� �� �ְ�.
	void AddForce(Vec2 force);
	void TurnOffCollider();

	GameObject* fixedPlayerObject = nullptr;

protected:
	eObjectTag m_tag;
	eObjectName m_name;
	int m_imageIndex;
	Transform* m_pTransform;
	eColType m_ColliderType;
	bool m_CanCollide = false; //[TW] �ݶ��̴��� �ε�������. ����.
	Collider* m_pCollider;
	Body* m_pBody = nullptr;
	bool isCollided = false; //��� �⺻������ ���� �ڽ��� ������Ʈ�� �浹�ߴ��� �ƴ����� ����.

	bool isPhysicsOn = false;
	
	//�츮�� �⺻������
	//ī�޶� : Local Space. (���� ������ �ʿ䰡 ����)
	//UI : Local Space.  
	//�༺, ź��, etc. :: ���� �����̽�. `

	//WorldToCameraPOINT. (���� -> ����)

};

