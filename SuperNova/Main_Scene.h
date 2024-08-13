#pragma once
#include "Scene.h"

class Main_Scene : public Scene
{
public:
	Main_Scene(eSceneName sceneName);
	~Main_Scene();
	
	virtual void Update() override;
	//virtual void Render() override;
	virtual void LateUpdate();
private:
	bool m_isNowScene;
	bool m_isMusicStart;
};

