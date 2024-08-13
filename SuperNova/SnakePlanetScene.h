#pragma once
#include "Scene.h"

class SnakePlanetScene : public Scene
{
public:
	SnakePlanetScene(eSceneName sceneName);
	~SnakePlanetScene();

	virtual void Update() override;
private:
	bool m_isNowScene;
	bool m_isMusicStart;
};

