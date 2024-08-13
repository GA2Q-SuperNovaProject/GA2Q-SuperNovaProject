#pragma once
#include <vector>
/// [TW] 드디어, 충돌을 감지해줄 수 있는 매니저. 그냥 밖에서 하나만의 객체를 선언하여 할 것이다.
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

	//함수 밖에서, 매개변수를 통해 충돌할 수 있는 오브젝트를 매 프레임 전달. [TW]
	//외부에서 일단 해줘야 하는 것이다.


	void Initialize();

	void TakeInCollidableObjects(GameObject* gameObject); 
	//CollisionDetection에서의 
	void UpdateColliders(); 
	void CompareColliders(); //들어온 CollideObjectList에서, 내부적으로 비교하면서 진행.
	void ClearColliderList(); //ColliderList는 매 순간 삭제시킬 것.

	bool CheckCollision(GameObject* obj); //콜리젼 체크.
	//[TW] 막 옵젝이 들어왔나, 유지되나, 막 끝났는가?
	///이거는 오브젝트가 사용할 수 있게 만들 것이다.
	//bool OnCollisionEnter(GameObject* gameObject);


private:
	std::vector<GameObject*> m_CollideObjectList;
};

