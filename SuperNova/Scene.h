#pragma once
#include <vector>
#include <chrono>
#include "IUpdatable.h"
#include "EnumDefine.h"

/// <summary>
/// �� Scene���� �θ�Ŭ����
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

	//��� ��ü�� ����� ���̴�. �������� ������ �̸� �������̵�޾Ƽ� �����ϸ� �ȵ�.
	virtual void ManageCollisions();
	//��ü ����, �������̵� ����.

	void LateUpdate(); //���� �ݿ� ���� �Ǵܿ�

	virtual void ManagePhysics(); //(��� �������� �ö󰡾� ��)

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

	void FadeIn(); // �� �Լ��� ��� �ҷ����ұ�?
	void FadeOut(); // �� �Լ��� ��� �ҷ����ұ�?

	void UpdatePlayerObject(eSceneName sceneName);
	// int GetIndex() const { return m_Index; }
	// void SetIndex(int val) { m_Index = val; }
protected:
	// �ش� ���� ������ ������Ʈ
	std::vector<GameObject*> m_arrobj;

	std::vector<GameObject*> m_AddBuffer;
	std::vector<GameObject*> m_RemoveBuffer;

	// ������ �̸�
	eSceneName m_name;

	bool m_SceneStartFlag = false;



private:
	int m_Index;
	// �����ڷ� �̸��� �޾ƾ��Ѵ�. ������ �������� �ε����� �þ��.
	static int s_m_SceneCount;
	bool m_IsActive = false; ///TW: Ȱ��ȭ�Ǿ������� ��Ÿ��. ������ ���ư������� ����.

	
	
};