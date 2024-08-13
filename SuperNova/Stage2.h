#pragma once
#include "Scene.h"

class Stage2 : public Scene
{
public:
	Stage2(eSceneName sceneName);
	~Stage2();

	virtual void Update() override;

private:
	bool m_isNowScene;
	bool m_isMusicStart;
};

