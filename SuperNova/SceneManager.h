#pragma once
#include <vector>
#include <string>
#include "EnumDefine.h"
#include "FixedQueue.h"
/// <summary>
/// ������ �з��ϴ� ���Ŵ���
/// Scene�� ��Ӱ��谡 �ƴϴ�!!!! ���� ���ض�!!!!
/// 2023.02.08 [nadong]
/// </summary>

class Scene;
class GameObject;

class SceneManager
{
public:
	static SceneManager& GetInstance()
	{
		static SceneManager inst;
		return inst;
	}

	void GameSetup();

	// Scene ������ Update �� Render�� AddBuffer, RemoveBuffer�� ���´�.
	void SceneLoop();


	//�� �̸��� string���� �ְ�, enum class�� ���� ���� (Scene ���)�� �޴´�.
	Scene* CreateScene(eSceneName name);

	void PutObjectInScene(Scene* scene, GameObject* obj); //Scene�� Object�� �ִ´�.


	void ChangeScene(eSceneName sceneName); //���� �ٲٴ� �뵵, ù��°�� ���� ������ ���� ��� ����.
	void ChangeSceneWithObject(eSceneName sceneName, GameObject* gameObject); //Ư�� ������Ʈ�� �Բ� �� �̵�.

	Scene* GetCurScene(); // �Ķ���ͷ� ���� ���� ���� ������ ����.
	void SetCurScene(Scene* scene); // �Ķ���ͷ� ���� ���� ���� ������ ����.
	void SetSceneActive(Scene* scene, bool _bool); //Bool ���� ���� ���� Ȱ��ȭ ���� �Է�

	Scene* FindSceneByName(eSceneName name);

	//void FadeInAndOut();	// ���̵�ƿ�-����ȯ-���̵��� �Ϸ��� ������ �ϳ���

	void FadeIn();
	void FadeOut();
	void ActuallyChangeScene(eSceneName sceneName);

	FixedQueue<eSceneName> sceneHistory;
private:
	/// �� ����, SceneLoop�� ���� �ֵ�.
	void ActBuffers(); //�� ���� ���� ���� 
	void ClearBuffers(); // �� ���� ���� Ŭ����.
	void Update(); //�� ���� ����  (����ٰ��� ������ ���ϴ� ���� ����)
	void ManageCollisions(); //SceneManager �ȿ��� Collision�� ����.
	void LateUpdate(); //���� �ݿ� �� ���� �Ǵ�.
	void ManagePhysics(); //SceneManager �ȿ��� Collision�� ����.

	void Render();//�� ���� ����.


	std::vector<Scene*> m_SceneList;

	Scene* m_pCurScene;

	SceneManager();
	~SceneManager();

	void ActuallyChangeSceneWithObject(eSceneName sceneName, GameObject* gameObject);
	void CheckForSceneChange(); //�������� ���̴� ������ ���� ���ؼ�.

	eSceneName toChangeScene = eSceneName::NONE; //���
	GameObject* gameObjectToAddNext = nullptr;

	void UpdatePlayerObject(eSceneName sceneName);

	

};