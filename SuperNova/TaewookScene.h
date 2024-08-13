#pragma once
#include "Scene.h"

class TaewookScene : public Scene
{
public:
	TaewookScene(eSceneName sceneName);
	~TaewookScene();

	virtual void Update() override;
	virtual void LateUpdate();
};
