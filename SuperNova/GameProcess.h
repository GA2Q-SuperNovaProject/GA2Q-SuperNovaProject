#pragma once
#include <windows.h>	
#include <vector>
#include "EnumDefine.h"
#include "StructDefine.h"
#pragma comment (lib, "D2DEngine.lib")

class D2DEngine;

/// <summary>
/// 2023.02.09 ���� ���� ���ؼ� �ӽñ���
/// (GameProcess �ܿ��� ObjectList  ����)
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

	void SceneObjectLoop(); ///SceneManager�� ���ؼ� ������ ��. (Update) [TW]
};

