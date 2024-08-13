#pragma	once
#include "Vec2.h" //�� .�� ������ �ұ�..
#include "Body.h"

class Transform;
class GameObject;

//Force���� ����, 
struct Force
{ 
public:
	//����: ���� �� Local/World �ٸ��� �������� ���ƾ� �Ѵ�!!!
	static Vec2 AddDragForce(GameObject* gameObject, float k); //�׷�
	//����: ���� �� Local/World �ٸ��� �������� ���ƾ� �Ѵ�!!!
	static Vec2 AddFrictionForce(GameObject* gameObject, float k); //������
	//����: ���� �� Local/World �ٸ��� �������� ���ƾ� �Ѵ�!!!
	//otherObject �������� ��������!
	static Vec2 AddGravityForce(GameObject* gameObject, GameObject* otherObject, float G, float minDistance, float maxDistance); //Gravitational, �׳� �߷�X.
	//����: ���� �� Local/World �ٸ��� �������� ���ƾ� �Ѵ�!!!
	static Vec2 AddSpringForce(GameObject* gameObject, const Vec2& anchor, float restLength, float k);

private:
	//����: ���� �� Local/World �ٸ��� �������� ���ƾ� �Ѵ�!!!
	static Vec2 AddDragForceWithBody(const Body* body, Transform* bodyTransform, float k);
	//����: ���� �� Local/World �ٸ��� �������� ���ƾ� �Ѵ�!!!
	static Vec2 AddFrictionForceWithBody(const Body* body, Transform* bodyTransform, float k);
	//����: ���� �� Local/World �ٸ��� �������� ���ƾ� �Ѵ�!!!
	static Vec2 AddGravityForceWithBody(const Body* a, Vec2 aPos, const Body* b, Vec2 bPos, float G, float minDistance, float maxDistance);
	//����: ���� �� Local/World �ٸ��� �������� ���ƾ� �Ѵ�!!!
	static Vec2 AddSpringForceWithBody(const Body* p, Transform* bodyTransform, const Vec2& anchor, float restLength, float k);
};

