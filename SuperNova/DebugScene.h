#pragma once
#include "Scene.h"

class DebugScene : public Scene
{
public:
	DebugScene(eSceneName sceneName);
	~DebugScene();

	virtual void Update() override;

private:

};

