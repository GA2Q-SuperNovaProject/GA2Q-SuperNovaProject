#pragma once
#include <windows.h>	
#include <vector>
#include "EnumDefine.h"
#include "StructDefine.h"
#pragma comment (lib, "D2DEngine.lib")

class D2DEngine;

/// <summary>
/// 2023.02.09 엔진 데모를 위해서 임시구조
/// (GameProcess 단에서 ObjectList  관리)
/// </summary>

class GameProcess
{
public:
	GameProcess();
	~GameProcess();

	HRESULT Initialize(HINSTANCE hInstance);
	void Loop();
	void Finalize();

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
private:
	HWND m_hWnd;
	MSG m_msg;

	D2DEngine* m_pDrawEngine;

	int m_ScreenWidth = 1920;
	int m_ScreenHeight = 1080;

	void SceneObjectLoop(); ///SceneManager를 통해서 실행할 것. (Update) [TW]
};

