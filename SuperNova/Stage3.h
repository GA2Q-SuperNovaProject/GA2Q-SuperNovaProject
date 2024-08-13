#pragma once
#include "Scene.h"
#include "EnumDefine.h"

class Stage3 : public Scene
{
public:
	Stage3(eSceneName sceneName);
	~Stage3();

	virtual void Update() override;
	virtual void LateUpdate();

private:
	GameObject* playerObject = nullptr;
	bool m_isMusicStart;
	bool m_isNowScene;
};

