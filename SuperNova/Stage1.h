#pragma once
#include "Scene.h"

using namespace std;

class GameObject;

class Stage1 : public Scene
{
public:
	Stage1(eSceneName sceneName);
	~Stage1();
	
	virtual void Update() override;
	virtual void LateUpdate();


private:
	GameObject* playerObject = nullptr;
	bool m_isMusicStart;
	bool m_isNowScene;
};

