#pragma once
#include <chrono>
#include <stack>
#include "EnumDefine.h"

class GameManager //일단은 만들어놨다. 뭐랄까... 근데, 당연히 이 형태로 가면 힘들수도.
{
public:
	// fadein / out을 위한 bool 변수 
	bool m_ChangeSceneOn = false;
	std::chrono::steady_clock::time_point transitionStartTime;
	std::chrono::steady_clock::time_point countTime;
	std::chrono::steady_clock::time_point tmpCntTime;

	static GameManager& GetInstance()
	{
		static GameManager inst;
		return inst;
	}

	bool m_isOptionClick = false;
	void Update(); //게임 전역에 영향을 미칠 것이다.

	void FadeIn();
	void FadeOut();
	void Render();
	
	void PushStatue(eObjectName objName);
	eObjectName TopStatue();

private:
	GameManager();
	~GameManager();

	std::stack<eObjectName> m_seqStack;		// 바다씬 별자리 순서지정
};