#pragma once
#include "Scene.h"

class Opening_Scene : public Scene
{
public:
	Opening_Scene(eSceneName sceneName);
	~Opening_Scene();

	virtual void Update() override;
};

