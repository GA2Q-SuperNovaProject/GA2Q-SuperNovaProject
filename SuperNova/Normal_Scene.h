#pragma once
#include "Scene.h"

class Normal_Scene : public Scene
{
public:
	Normal_Scene(eSceneName sceneName);
	~Normal_Scene();

	virtual void Update() override;

private:
	bool m_isNowScene;
	bool m_isMusicStart;
};

