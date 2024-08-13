#pragma once
#include <vector>
#include <string>
#include "EnumDefine.h"
#include "FixedQueue.h"
/// <summary>
/// 씬들을 분류하는 씬매니저
/// Scene과 상속관계가 아니다!!!! 생각 잘해라!!!!
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

	// Scene 단위의 Update 와 Render와 AddBuffer, RemoveBuffer를 묶는다.
	void SceneLoop();


	//씬 이름을 string으로 넣고, enum class로 씬의 종류 (Scene 상속)을 받는다.
	Scene* CreateScene(eSceneName name);

	void PutObjectInScene(Scene* scene, GameObject* obj); //Scene에 Object를 넣는다.


	void ChangeScene(eSceneName sceneName); //씬을 바꾸는 용도, 첫번째로 씬을 설정할 때는 사용 금지.
	void ChangeSceneWithObject(eSceneName sceneName, GameObject* gameObject); //특정 오브젝트와 함께 씬 이동.

	Scene* GetCurScene(); // 파라미터로 받은 씬을 현재 씬으로 설정.
	void SetCurScene(Scene* scene); // 파라미터로 받은 씬을 현재 씬으로 설정.
	void SetSceneActive(Scene* scene, bool _bool); //Bool 값에 따라서 씬의 활성화 여부 입력

	Scene* FindSceneByName(eSceneName name);

	//void FadeInAndOut();	// 페이드아웃-씬전환-페이드인 일련의 과정을 하나로

	void FadeIn();
	void FadeOut();
	void ActuallyChangeScene(eSceneName sceneName);

	FixedQueue<eSceneName> sceneHistory;
private:
	/// 씬 단위, SceneLoop에 쓰일 애들.
	void ActBuffers(); //씬 단위 버퍼 관리 
	void ClearBuffers(); // 씬 단위 버퍼 클리어.
	void Update(); //씬 단위 업뎃  (여기다가는 물리를 가하는 것은 ㄱㅊ)
	void ManageCollisions(); //SceneManager 안에서 Collision을 관리.
	void LateUpdate(); //물리 반영 후 로직 판단.
	void ManagePhysics(); //SceneManager 안에서 Collision을 관리.

	void Render();//씬 단위 렌더.


	std::vector<Scene*> m_SceneList;

	Scene* m_pCurScene;

	SceneManager();
	~SceneManager();

	void ActuallyChangeSceneWithObject(eSceneName sceneName, GameObject* gameObject);
	void CheckForSceneChange(); //프레임이 꼬이는 문제를 막기 위해서.

	eSceneName toChangeScene = eSceneName::NONE; //얘는
	GameObject* gameObjectToAddNext = nullptr;

	void UpdatePlayerObject(eSceneName sceneName);

	

};