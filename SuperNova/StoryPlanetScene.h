#pragma once
#include "Scene.h"

class StoryPlanetScene : public Scene
{
public:
	StoryPlanetScene(eSceneName sceneName);
	~StoryPlanetScene();

	virtual void Update() override;
private:
	bool m_isNowScene;
	bool m_isMusicStart;
};

