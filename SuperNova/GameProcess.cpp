#include "GameProcess.h"
#include "D2DEngine.h"
#include "InputManager.h"
#include "MouseInputManager.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "GameSetting.h"	//230210 수정 {TW}
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

	//  용도: 창 클래스를 등록합니다.
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

	// 윈도우 클래스 등록
	RegisterClass(&wc);
	// 애플리케이션 초기화를 수행합니다. 
	// 윈도우를 생성합니다.
	m_hWnd = CreateWindowW(
		CLASS_NAME,
		CLASS_NAME,
		WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_SYSMENU |
		WS_EX_TOPMOST | WS_POPUP,
		0, 0, m_ScreenWidth, m_ScreenHeight,
		NULL, NULL, hInstance, NULL);

	// TimeManager Init
	TimeManager::GetInstance().Initialize();
	ObjectPool<Bullet>::GetInstance().Initialize(eObjectTag::BULLET, eObjectName::SHOOTHING_STAR, 100); //나중에 쓰일 일이 생기면 개별적 처리하는 것으로!
	ObjectPool<Bullet>::GetInstance().Initialize(eObjectTag::BULLET, eObjectName::SATELLITE, 100); //나중에 쓰일 일이 생기면 개별적 처리하는 것으로!
	ObjectPool<Bullet>::GetInstance().Initialize(eObjectTag::BULLET, eObjectName::SHOOTHING_STAR_TAIL, 100); //나중에 쓰일 일이 생기면 개별적 처리하는 것으로!
	Camera::GeInstance().Initialize();
	PhysicsManager::GetInstance().Initialize();
	CollisionManager::GetInstance().Initialize();

	// D2D엔진 포인터로 받아옴
	m_pDrawEngine = new D2DEngine;
	m_pDrawEngine->Initalize(hInstance, m_hWnd);
	RenderSystem::GetInstance().SetEnginePointer(m_pDrawEngine);

	GameSetting::ReadyAllScene(); ///씬 별 내용을 준비하는 곳. [TW]

	if (!m_hWnd) { return S_FALSE; }

	// 생성된 윈도우를 화면에 표시
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
			///[TW] 이 사이에 리소스가 현재 제대로 만들어져서 쓰이고 있는지 확인할 필요가 있다.
			/// 나중에 문제가 생기면, 여기서 디바이스 독립적/종속적 리소스들 구분해서 HRESULT에 따라 리로드해주는 것도
			/// 해결책 중 하나가 될 수 있다.
			InputManager::GetInstance().Update(); // 인풋 업데이트.
			MouseInputManager::GetInstance().Update(); // 마우스 인풋 업데이트.
			SceneObjectLoop(); ///실제 씬 단위로 오브젝트를 관리/렌더 함수 호출 [TW]
			TimeManager::GetInstance().StartCheckTime();
		}
	}
}

/// 일단, 현재 구조에서는 SceneManager가 Update를 총괄하고 있음.
/// 오브젝트 단위로 Update를 돌리는 것보다, 활성화되어 있는 씬들을 파악하고,
/// 활성화되었을시, 그냥 업데이트해주는 것이 맞아보임. (옵젝 위주 -> 씬 위주) [TW]
/// 따라서, GameProcess는 자체적으로 위와 같은 기능 필요 X, 하나로 묶어서 실행해줘도 될 것.
/// 
void GameProcess::SceneObjectLoop()
{
	SceneManager::GetInstance().SceneLoop(); ///SceneLoop를 돌린다.
}


void GameProcess::Finalize()
{

}

LRESULT GameProcess::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		//case WM_CREATE:
		//	SetTimer(hWnd, 1, 1000, NULL);  //1초 간격 타이머
		//	SetTimer(hWnd, 2, 5000, NULL);  //5초 간격 타이머
		//	SetTimer(hWnd, 3, 10000, NULL); //10초 간격 타이머
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		//case WM_TIMER:
		//	////망나니 st 하드코딩. 아무것도 안해도 갖다쓰기.
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


