#include "GameProcess.h"
#include "D2DEngine.h"
#include "InputManager.h"
#include "MouseInputManager.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "GameSetting.h"	//230210 ���� {TW}
#include "ObjectPool.h"
#include "RenderSystem.h"
#include "Camera.h"
#include "Debug.h"
#include "CollisionManager.h"
#include "PhysicsManager.h"
#include "Timer.h"
#include "Bullet.h"
#include "EnumDefine.h"
#include "GameManager.h"

using namespace std;

GameProcess::GameProcess()
	:m_hWnd(NULL),
	m_msg(),
	m_ScreenWidth(1920),
	m_ScreenHeight(1080),
	m_pDrawEngine(nullptr)
{
	//Debug::Trace("DebugView Activated");
}

GameProcess::~GameProcess()
{

}

HRESULT GameProcess::Initialize(HINSTANCE hInstance)
{
	const wchar_t CLASS_NAME[] = L"SUPER NOVA";
	WNDCLASS wc;

	//  �뵵: â Ŭ������ ����մϴ�.
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = GameProcess::WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = MAKEINTRESOURCEW(IDC_ARROW);
	wc.lpszClassName = CLASS_NAME;

	// ������ Ŭ���� ���
	RegisterClass(&wc);
	// ���ø����̼� �ʱ�ȭ�� �����մϴ�. 
	// �����츦 �����մϴ�.
	m_hWnd = CreateWindowW(
		CLASS_NAME,
		CLASS_NAME,
		WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_SYSMENU |
		WS_EX_TOPMOST | WS_POPUP,
		0, 0, m_ScreenWidth, m_ScreenHeight,
		NULL, NULL, hInstance, NULL);

	// TimeManager Init
	TimeManager::GetInstance().Initialize();
	ObjectPool<Bullet>::GetInstance().Initialize(eObjectTag::BULLET, eObjectName::SHOOTHING_STAR, 100); //���߿� ���� ���� ����� ������ ó���ϴ� ������!
	ObjectPool<Bullet>::GetInstance().Initialize(eObjectTag::BULLET, eObjectName::SATELLITE, 100); //���߿� ���� ���� ����� ������ ó���ϴ� ������!
	ObjectPool<Bullet>::GetInstance().Initialize(eObjectTag::BULLET, eObjectName::SHOOTHING_STAR_TAIL, 100); //���߿� ���� ���� ����� ������ ó���ϴ� ������!
	Camera::GeInstance().Initialize();
	PhysicsManager::GetInstance().Initialize();
	CollisionManager::GetInstance().Initialize();

	// D2D���� �����ͷ� �޾ƿ�
	m_pDrawEngine = new D2DEngine;
	m_pDrawEngine->Initalize(hInstance, m_hWnd);
	RenderSystem::GetInstance().SetEnginePointer(m_pDrawEngine);

	GameSetting::ReadyAllScene(); ///�� �� ������ �غ��ϴ� ��. [TW]

	if (!m_hWnd) { return S_FALSE; }

	// ������ �����츦 ȭ�鿡 ǥ��
	ShowWindow(m_hWnd, SW_SHOWNORMAL);
	UpdateWindow(m_hWnd);

	//SoundManager::SystemInitialize();
	//SoundManager::CreateSound("Test.wav", eSoundChannel::BackGround, true);

	Debug::Trace("DebugView Is Working");

	return S_OK;
}


void GameProcess::Loop()
{
	while (m_msg.message != WM_QUIT)
	{
		if (PeekMessage(&m_msg, NULL, 0, 0, PM_REMOVE))
		{
			DispatchMessage(&m_msg);
		}
		else
		{
			GameManager::GetInstance().Update();
			TimeManager::GetInstance().EndCheckTime();
			//Debug::Trace("------------------------------");
			///[TW] �� ���̿� ���ҽ��� ���� ����� ��������� ���̰� �ִ��� Ȯ���� �ʿ䰡 �ִ�.
			/// ���߿� ������ �����, ���⼭ ����̽� ������/������ ���ҽ��� �����ؼ� HRESULT�� ���� ���ε����ִ� �͵�
			/// �ذ�å �� �ϳ��� �� �� �ִ�.
			InputManager::GetInstance().Update(); // ��ǲ ������Ʈ.
			MouseInputManager::GetInstance().Update(); // ���콺 ��ǲ ������Ʈ.
			SceneObjectLoop(); ///���� �� ������ ������Ʈ�� ����/���� �Լ� ȣ�� [TW]
			TimeManager::GetInstance().StartCheckTime();
		}
	}
}

/// �ϴ�, ���� ���������� SceneManager�� Update�� �Ѱ��ϰ� ����.
/// ������Ʈ ������ Update�� ������ �ͺ���, Ȱ��ȭ�Ǿ� �ִ� ������ �ľ��ϰ�,
/// Ȱ��ȭ�Ǿ�����, �׳� ������Ʈ���ִ� ���� �¾ƺ���. (���� ���� -> �� ����) [TW]
/// ����, GameProcess�� ��ü������ ���� ���� ��� �ʿ� X, �ϳ��� ��� �������൵ �� ��.
/// 
void GameProcess::SceneObjectLoop()
{
	SceneManager::GetInstance().SceneLoop(); ///SceneLoop�� ������.
}


void GameProcess::Finalize()
{

}

LRESULT GameProcess::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		//case WM_CREATE:
		//	SetTimer(hWnd, 1, 1000, NULL);  //1�� ���� Ÿ�̸�
		//	SetTimer(hWnd, 2, 5000, NULL);  //5�� ���� Ÿ�̸�
		//	SetTimer(hWnd, 3, 10000, NULL); //10�� ���� Ÿ�̸�
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		//case WM_TIMER:
		//	////������ st �ϵ��ڵ�. �ƹ��͵� ���ص� ���پ���.
		//	//switch (wParam)
		//	//{
		//	//	case 1:
		//	//		Timer::GetInstance().counterOne++;
		//	//		break;
		//	//	case 2:
		//	//		Timer::GetInstance().counterFive++;
		//	//		break;
		//	//	case 3:
		//	//		Timer::GetInstance().counterTen++;
		//	//		break;
		//	//}
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
			break;
	}
	return 0;
}


