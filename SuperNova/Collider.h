#pragma once
#include "Vec2.h"
#include "FixedQueue.h"

class Transform;
class GameObject;

class Collider 
{
public:
	Collider(const Transform& transform, int imageIndex); //������ Transform�� �޾Ƽ� ����.
	virtual ~Collider();

	virtual void UpdateCollider() = 0; //���� ����.

	//Position�� �ǽð����� ���Ǿ�� �Ѵ�. ����� Ȱ���ؼ�.
	//�ǽð����� �������� �� ������, ��� �ؾ� �Ǵ°�?
	//�� �������� CollisionDetection�̶�� �ٸ� Ŭ������ �̵��Ǿ�, 
	//Collider�� ��ɵǾ� ���ȴ�. 
	//������ ��� ������ ������..? 
	//Box�� ����, Width�� Height�� �ʿ��ϰ�,
	//Circle�� ����, Radius�� ������ �Ǵ��� �ʿ��� ��Ȳ�̴�.
	//�ƴϴ�. �� ���, �ڷ����� Ȯ���ϴ�, ����ȯ�� ���� ����ϸ� �ȴ�.
	//GetWidth/Height/Radius / Rect ���.. 
	//Collider*�� �νĵ� �ֵ��� GameObject*���� GetColType���� ���ϰ�,
	//�ٿ�ĳ�����ϸ� �Ǵ� ���� (��������, ��ü �Ļ� Ÿ�� -> ��ĳ���� -> �ٿ�ĳ����)
	//GetPosition�� ��ü Collider �з��� ����. [TW]

	void SetOtherCollidedObject(GameObject* other); // �浹�� �ڽ� ���� �ٸ� ������Ʈ�� ����.
	GameObject* GetOtherCollidedObject(); // �浹�� �ڽ� ���� �ٸ� ������Ʈ�� ����.

protected:
	const Transform* m_pTransform; //���⼭ ��ȭ��Ű�� ���� ����. ���� ������ ��.
	int m_imageIndex; 

	//���Ƿ�, �浹�� �ָ� ��ȯ���ִ� ģ���̴�.
	//CollisionManager�� ���ִ� ��. 
	GameObject* otherCollidedObject; 
	//Rp
	//Width/Height �Ǻ� ����. ���������� �߸��� ��ġ��� ����������,
	//���� ����� �س� ���̴�.

	
};

