#pragma once
#include <chrono>
#include <stack>
#include "EnumDefine.h"

class GameManager //�ϴ��� ��������. ������... �ٵ�, �翬�� �� ���·� ���� �������.
{
public:
	// fadein / out�� ���� bool ���� 
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
	void Update(); //���� ������ ������ ��ĥ ���̴�.

	void FadeIn();
	void FadeOut();
	void Render();
	
	void PushStatue(eObjectName objName);
	eObjectName TopStatue();

private:
	GameManager();
	~GameManager();

	std::stack<eObjectName> m_seqStack;		// �ٴپ� ���ڸ� ��������
};