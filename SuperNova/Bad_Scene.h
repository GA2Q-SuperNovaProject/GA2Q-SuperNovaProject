#pragma once
#include "Scene.h"

class Bad_Scene : public Scene
{
public:
	Bad_Scene(eSceneName sceneName);
	~Bad_Scene();

	virtual void Update() override;

private:
	bool m_isNowScene;
	bool m_isMusicStart;
};

