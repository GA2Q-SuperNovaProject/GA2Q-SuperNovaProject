#pragma once
#include <vector>
#include <chrono>
#include "IUpdatable.h"
#include "EnumDefine.h"

/// <summary>
/// 각 Scene들의 부모클래스
/// 2023.02.08 [nadong]
/// </summary>


class GameObject;

class Scene : public IUpdatable
{
	friend class SceneManager;
	friend class BulletManager;
	friend class Player;

public:
	Scene(eSceneName sceneName);
	~Scene();

	std::vector<GameObject*> FrontRenderArray;
	virtual void Initialize();

	virtual void Render() override;
	virtual void Update() override;

	//얘는 자체로 실행될 것이다. 개별적인 씬들이 이를 오버라이드받아서 실행하면 안됨.
	virtual void ManageCollisions();
	//자체 실행, 오버라이드 금지.

	void LateUpdate(); //물리 반영 로직 판단용

	virtual void ManagePhysics(); //(얘는 나중으로 올라가야 함)

	virtual void AddObject(GameObject* pObject);
	virtual void RemoveObject(GameObject* pObject);
	virtual void ActuallyActBuffers();
	virtual void ClearBuffers();

	virtual void Finalize();

	bool GetActive() const { return m_IsActive; }
	void SetActive(bool val) { m_IsActive = val; }

	eSceneName GetName() const { return m_name; }
	void SetName(eSceneName val) { m_name = val; }

	GameObject* FindObjectInScene(eObjectName objectName);

	GameObject* FindObjectByTagInScene(eObjectTag objecttag);

	void FadeIn(); // 이 함수를 어디서 불러야할까?
	void FadeOut(); // 이 함수를 어디서 불러야할까?

	void UpdatePlayerObject(eSceneName sceneName);
	// int GetIndex() const { return m_Index; }
	// void SetIndex(int val) { m_Index = val; }
protected:
	// 해당 씬에 가져올 오브젝트
	std::vector<GameObject*> m_arrobj;

	std::vector<GameObject*> m_AddBuffer;
	std::vector<GameObject*> m_RemoveBuffer;

	// 씬들의 이름
	eSceneName m_name;

	bool m_SceneStartFlag = false;



private:
	int m_Index;
	// 생성자로 이름만 받아야한다. 씬들을 받을수록 인덱스가 늘어난다.
	static int s_m_SceneCount;
	bool m_IsActive = false; ///TW: 활성화되었는지를 나타냄. 루프가 돌아가는지를 구별.

	
	
};