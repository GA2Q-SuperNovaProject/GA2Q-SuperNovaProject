#pragma once
#include "Scene.h"

class MouseScene : public Scene
{
public:
	MouseScene(eSceneName sceneName);
	~MouseScene();

	virtual void Update() override;

private:

};

