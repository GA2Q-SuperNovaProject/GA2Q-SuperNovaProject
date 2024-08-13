#pragma once
#include "Scene.h"

class True_Scene : public Scene
{
public:
	True_Scene(eSceneName sceneName);
	~True_Scene();

	virtual void Update() override;
private:
	bool m_isNowScene;
	bool m_isMusicStart;
};

