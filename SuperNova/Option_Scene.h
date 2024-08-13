#pragma once
#include "Scene.h"

class Option_Scene : public Scene
{
public:
	Option_Scene(eSceneName sceneName);
	~Option_Scene();

	virtual void Update() override;
	virtual void LateUpdate();
};

