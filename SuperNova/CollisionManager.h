#pragma once
#include <vector>
/// [TW] ����, �浹�� �������� �� �ִ� �Ŵ���. �׳� �ۿ��� �ϳ����� ��ü�� �����Ͽ� �� ���̴�.
class GameObject;

class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();

	static CollisionManager& GetInstance()
	{
		static CollisionManager inst;
		return inst;
	}

	//�Լ� �ۿ���, �Ű������� ���� �浹�� �� �ִ� ������Ʈ�� �� ������ ����. [TW]
	//�ܺο��� �ϴ� ����� �ϴ� ���̴�.


	void Initialize();

	void TakeInCollidableObjects(GameObject* gameObject); 
	//CollisionDetection������ 
	void UpdateColliders(); 
	void CompareColliders(); //���� CollideObjectList����, ���������� ���ϸ鼭 ����.
	void ClearColliderList(); //ColliderList�� �� ���� ������ų ��.

	bool CheckCollision(GameObject* obj); //�ݸ��� üũ.
	//[TW] �� ������ ���Գ�, �����ǳ�, �� �����°�?
	///�̰Ŵ� ������Ʈ�� ����� �� �ְ� ���� ���̴�.
	//bool OnCollisionEnter(GameObject* gameObject);


private:
	std::vector<GameObject*> m_CollideObjectList;
};

