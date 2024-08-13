#include "D2DEngine.h"
#include <string>

// [TW] CollideInfoMap을 Width/Height을 받아오는데 활용하기 위해 Include.
#include "../SuperNova/CollideInfoMap.h"
#include "../SuperNova/RenderSystem.h"

#include "../SuperNova/Debug.h"

using namespace std;

const FLOAT DEFAULT_DPI = 96.f;   // Default DPI, [TW]
const UINT DELAY_TIMER_ID = 1;

/// <summary>
/// 20230213	YJ
/// gif를 위해서 위쪽에서 선언
/// </summary>
/// <param name="bgcolor"></param>
inline LONG RectWidth(RECT rc) { return rc.right - rc.left; }
inline LONG RectHeight(RECT rc) { return rc.bottom - rc.top; }


/// <summary>
/// 23.02.02
/// D2DEngine 내부
/// 쓰다듬어주는 중
/// </summary>
D2DEngine::D2DEngine()
// 생성자 초기화 리스트
	: m_hWnd(nullptr),
	m_hResult(NULL),
	m_pFactory(nullptr),
	m_pRenderTarget(NULL),
	m_pImgRenderTarget(nullptr),
	m_pTempBrush(nullptr),
	m_pNowBrush(nullptr),
	m_pRedBrush(nullptr),
	m_pGreenBrush(nullptr),
	m_pBlueBrush(nullptr),
	m_pWhiteBrush(nullptr),
	m_pBlackBrush(nullptr),
	m_pDWriteFactory(nullptr),
	m_pTextFormat(nullptr),
	m_pWicFactory(nullptr),
	m_SpriteCount(0),
	m_SpriteSheetCount(0),
	m_SpritePool(),
	m_ScreenRect(),
	m_pDCRenderTarget(nullptr),
	m_backgroundColor()
{ }
//m_pFrameComposeRT(nullptr),

D2DEngine::~D2DEngine() {}


/// public
#pragma region Init, Final
void D2DEngine::Initalize(HINSTANCE hInstance, HWND hWnd)
{
	m_hResult = CoInitialize(NULL);
	// HRESULT : 32bit signed 정수형 반환형중 하나이다.
	// CoInitalize는 객체를 사용하려는 Thread가 있으면 호출해주어야 한다.
	// 그래서 이게 뭐임?

	m_hWnd = hWnd;
	// 받아온 파라미터(받아온 매개 인자)를 넣어준다.

	// m_hResult = S_OK;
	// HRESULT의 상태를 확인 할 수 있다.
	// S_OK는 Bool TRUE값을 의미 (작업이 성공했다)
	// 반대->S_FALSE 함수가 성공했다는 뜻

	GetClientRect(m_hWnd, &m_ScreenRect); // 플레이 화면의 크기를 받아온다

	CreateDeviceResources();
	CreateBrush();
	LoadImageResources();
	LoadGIFResources();
	// RenderSystem::GetInstance().m_phWnd = &m_hWnd;
}

void D2DEngine::Finalize()
{
	//매크로를 이용해서 여기서 해제
	SafeRelease(&m_pFactory);
	SafeRelease(&m_pRenderTarget);

	SafeRelease(&m_pTempBrush);
	SafeRelease(&m_pNowBrush);
	SafeRelease(&m_pRedBrush);
	SafeRelease(&m_pGreenBrush);
	SafeRelease(&m_pBlueBrush);
	SafeRelease(&m_pWhiteBrush);
	SafeRelease(&m_pBlackBrush);

	SafeRelease(&m_pWicFactory);

	//m_pFactory->Release();
	//m_pRenderTarget->Release();

	//m_pTempBrush->Release();
	//m_pNowBrush->Release();
	//m_pRedBrush->Release();
	//m_pGreenBrush->Release();
	//m_pBlueBrush->Release();
	//m_pWhiteBrush->Release();
	//m_pBlackBrush->Release();

	CoUninitialize();
}
#pragma endregion
#pragma region Begin/End Render
void D2DEngine::BeginRender(ColorF bgcolor)
{
	// D2D랜더타겟으로 그림그리기를 시작한다.
	m_pRenderTarget->BeginDraw();

	// 맨 처음 BeginDraw를 하면 검은색으로 변경되기 때문에
	// Clear를 이용하여 윈도우배경을 바꿔준다.
	m_pRenderTarget->Clear(ColorF(bgcolor));
}

void D2DEngine::EndRender()
{
	m_pRenderTarget->EndDraw();
}
#pragma endregion
#pragma region Draw Basic
void D2DEngine::DrawLine(float sposx, float sposy, float dposx, float dposy)
{
	//시작지점 x,y를 받아서 하나의 포인트로 묶음
	D2D_POINT_2F sPoint;
	sPoint.x = sposx;
	sPoint.y = sposy;
	D2D1_POINT_2F dPoint;

	dPoint.x = dposx;
	dPoint.y = dposy;

	m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Translation(0, 0));
	m_pRenderTarget->DrawLine(sPoint, dPoint, m_pRedBrush);
}

void D2DEngine::DrawRect(float cposx, float cposy, float width, float height)
{
	D2D_POINT_2F LTPos;	// 좌측 상단 점
	LTPos.x = cposx - (width / 2);
	LTPos.y = cposy - (height / 2);
	D2D1_POINT_2F RTPos;	// 우측 상단 점
	RTPos.x = cposx + (width / 2);
	RTPos.y = cposy - (height / 2);
	D2D_POINT_2F LBPos;	// 좌측 하단 점
	LBPos.x = cposx - (width / 2);
	LBPos.y = cposy + (height / 2);
	D2D1_POINT_2F RBPos;	// 우측 하단 아래
	RBPos.x = cposx + (width / 2);
	RBPos.y = cposy + (height / 2);

	m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Translation(0, 0));
	m_pRenderTarget->DrawLine(LTPos, RTPos, m_pRedBrush);	// 좌측 상단에서 우측 상단
	m_pRenderTarget->DrawLine(RTPos, RBPos, m_pRedBrush);	// 우측 상단에서 우측 하단
	m_pRenderTarget->DrawLine(RBPos, LBPos, m_pRedBrush);	// 우측 하단에서 좌측 하단
	m_pRenderTarget->DrawLine(LBPos, LTPos, m_pRedBrush);	// 좌측 하단에서 좌측 상단

	wstringstream out;
	out.precision(3);
	out << fixed << setprecision(3) << cposx; // to_wstring(cPosx);
	out << L" , ";
	out << fixed << setprecision(3) << cposy;	// 소수점 3번째 자리까지 출력
	auto temp = out.str();

	InfoText(Vec2(cposx, cposx), temp);
}

//페이드인 페이드 아웃을 위한 네모
void D2DEngine::DrawFillRectangle()
{
	D2D1_SIZE_F size = m_pRenderTarget->GetSize();
	D2D1_RECT_F rectangle = D2D1::RectF(
	size.width/2 - 1920.0f,
	size.height/2 - 1080.0f,
	size.width/2 + 1920.0f,
	size.height/2 + 1080.0f
	);

	m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Translation(0, 0));
	m_pRenderTarget->FillRectangle(rectangle,m_pBlackBrush);

}

void D2DEngine::DrawCircle(float cPosx, float cPosy, float radius)
{
	D2D1_ELLIPSE Circle;
	Circle.point.x = cPosx;	// 중점 좌표
	Circle.point.y = cPosy;
	Circle.radiusX = radius; // 반지름 길이
	Circle.radiusY = radius;
	m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Translation(0, 0));
	m_pRenderTarget->DrawEllipse(Circle, m_pRedBrush);

	//wstringstream out;
	//out.precision(3);
	//out << fixed << setprecision(3) << cPosx; // to_wstring(cPosx);
	//out << L" , ";
	//out << fixed << setprecision(3) << cPosy;	// 소수점 3번째 자리까지 출력
	//auto temp = out.str();

	//InfoText(Vec2(cPosx, cPosy - radius), temp);
}

void D2DEngine::InfoText(Vec2 writePos, wstring str)
{
	//wstring??->wide char string 이라는 뜻
	//win api 에서 텍스트를 출력할때 wchar을 자주 사용
	// L"asdasd"
	m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Translation(0, 0));
	m_pRenderTarget->DrawText
	(
		str.c_str(),	// 문자열의 수정 불가능한 표준 C 문자 배열 버전을 반환합니다-> C++스타일의 문자열을 C스타일로
		str.size(),		// string 기준 문자열의 사이즈를 반환
		m_pTextFormat,
		RectF(writePos.x, writePos.y, (writePos.x + str.size()) * 10, writePos.y + 50), 
		m_pWhiteBrush
	);
}
#pragma endregion

#pragma region Draw Debug
//콜라이더가 미쳐 돌아가는 관계로, 기존의 함수들을 변경해서 디버그용 출력 함수를 만든다.
void D2DEngine::DrawDebugLine(const Vec2& startPos, const Vec2& endPos, eDebugBrush debugBrushType)
{
	ID2D1SolidColorBrush* paintBrush = nullptr;
	if (debugBrushType == eDebugBrush::EDB_RED)
	{
		paintBrush = m_pRedBrush;
	}
	else if (debugBrushType == eDebugBrush::EDB_GREEN)
	{
		paintBrush = m_pGreenBrush;
	}
	else if (debugBrushType == eDebugBrush::EDB_BLUE)
	{
		paintBrush = m_pBlueBrush;
	}
	else 
	{
		paintBrush = m_pWhiteBrush;
	}

	//시작지점 x,y를 받아서 하나의 포인트로 묶음
	D2D_POINT_2F sPoint;
	sPoint.x = startPos.x;
	sPoint.y = startPos.y;

	D2D1_POINT_2F dPoint;
	dPoint.x = endPos.x;
	dPoint.y = endPos.y;

	m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Translation(0, 0));
	m_pRenderTarget->DrawLine(sPoint, dPoint, paintBrush);
}

void D2DEngine::DrawDebugRect(const Vec2Rect& rect, eDebugBrush debugBrushType)
{
	ID2D1SolidColorBrush* paintBrush = nullptr;
	if (debugBrushType == eDebugBrush::EDB_RED)
	{
		paintBrush = m_pRedBrush;
	}
	else if (debugBrushType == eDebugBrush::EDB_GREEN)
	{
		paintBrush = m_pGreenBrush;
	}
	else if (debugBrushType == eDebugBrush::EDB_BLUE)
	{
		paintBrush = m_pBlueBrush;
	}
	else
	{
		paintBrush = m_pWhiteBrush;
	}

	m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Translation(0, 0));
	D2D_POINT_2F pointTL;
	pointTL.x = rect.topLeft.x;
	pointTL.y = rect.topLeft.y;

	D2D_POINT_2F pointTR;
	pointTR.x = rect.topRight.x;
	pointTR.y = rect.topRight.y;

	D2D_POINT_2F pointBL;
	pointBL.x = rect.bottomLeft.x;
	pointBL.y = rect.bottomLeft.y;

	D2D_POINT_2F pointBR;
	pointBR.x = rect.bottomRight.x;
	pointBR.y = rect.bottomRight.y;

	m_pRenderTarget->DrawLine(pointTL, pointTR, paintBrush);	// 좌측 상단에서 우측 상단
	m_pRenderTarget->DrawLine(pointTR, pointBR, paintBrush);	// 우측 상단에서 우측 하단
	m_pRenderTarget->DrawLine(pointBR, pointBL, paintBrush);	// 우측 하단에서 좌측 하단
	m_pRenderTarget->DrawLine(pointBL, pointTL, paintBrush);	// 좌측 하단에서 좌측 상단
}

void D2DEngine::DrawDebugCircle(const Vec2Circle& circle, eDebugBrush debugBrushType)
{
	ID2D1SolidColorBrush* paintBrush = nullptr;
	if (debugBrushType == eDebugBrush::EDB_RED)
	{
		paintBrush = m_pRedBrush;
	}
	else if (debugBrushType == eDebugBrush::EDB_GREEN)
	{
		paintBrush = m_pGreenBrush;
	}
	else if (debugBrushType == eDebugBrush::EDB_BLUE)
	{
		paintBrush = m_pBlueBrush;
	}
	else
	{
		paintBrush = m_pWhiteBrush;
	}

	D2D1_ELLIPSE Circle;
	Circle.point.x = circle.position.x;	// 중점 좌표
	Circle.point.y = circle.position.y;
	Circle.radiusX = circle.radius; // 반지름 길이
	Circle.radiusY = circle.radius;

	m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Translation(0, 0));
	m_pRenderTarget->DrawEllipse(Circle, m_pRedBrush);
}


#pragma endregion


#pragma region Draw Sprite
void D2DEngine::DrawSprite(int spriteIndex, int dstX, int dstY)
{
	D2DSprite* _D2DSprite = m_SpriteInfos[spriteIndex];
	if (_D2DSprite != NULL)
	{
		ID2D1Bitmap* _sheet = m_SpriteSheets[_D2DSprite->m_SheetIndex];
		if (_sheet != NULL)	// 인덱스 접근 시 실패체크도 해야 함
		{
			m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Translation(0, 0));
			m_pRenderTarget->DrawBitmap(_sheet,
				RectF(								//중점에서 찍겠다는 뜻
					(float)dstX - _D2DSprite->Width / 2,
					(float)dstY - _D2DSprite->Height / 2,
					(float)(dstX + _D2DSprite->Width / 2),
					(float)(dstY + _D2DSprite->Height / 2)),	// 비트맵 크기
				1.0f,
				D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
				RectF(
					_D2DSprite->m_OriX,
					_D2DSprite->m_OriY,
					_D2DSprite->m_OriX + (float)_D2DSprite->Width,
					_D2DSprite->m_OriY + (float)_D2DSprite->Height)	// 실제로 그리는 부분
			);
		}
	}
}

///[TW] Transform을 반영해서 도형을 그리려고 하는 함수.
void D2DEngine::DrawSprite(int spriteIndex, int dstX, int dstY, Transform* transform)
{
	D2DSprite* _D2DSprite = m_SpriteInfos[spriteIndex];
	if (_D2DSprite != NULL)
	{
		ID2D1Bitmap* _sheet = m_SpriteSheets[_D2DSprite->m_SheetIndex];
		if (_sheet != NULL)	// 인덱스 접근 시 실패체크도 해야 함
		{
			D2D1_RECT_F tmpRect = RectF(
				(float)dstX - _D2DSprite->Width / 2,
				(float)dstY - _D2DSprite->Height / 2,
				(float)(dstX + _D2DSprite->Width / 2),
				(float)(dstY + _D2DSprite->Height / 2));

			D2D1_MATRIX_3X2_F rotation = Matrix3x2F::Rotation(
				transform->GetRotation(),
				Point2F(
					transform->GetPosition().x,
					transform->GetPosition().y)
			);

			D2D1_SIZE_F sizeTrans = {
				transform->GetScale().x,
				transform->GetScale().y
			};

			D2D1_MATRIX_3X2_F scale =
				Matrix3x2F::Scale(sizeTrans,
					Point2F(
						transform->GetPosition().x,
						transform->GetPosition().y)
				);

			m_pRenderTarget->SetTransform(scale * rotation);

			m_pRenderTarget->DrawBitmap(_sheet,
				tmpRect,	// 비트맵 크기
				1.0f,
				D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
				RectF(
					_D2DSprite->m_OriX,
					_D2DSprite->m_OriY,
					_D2DSprite->m_OriX + (float)_D2DSprite->Width,
					_D2DSprite->m_OriY + (float)_D2DSprite->Height)	// 실제로 그리는 부분
			);
		}
	}
}
#pragma endregion
#pragma region Draw GIF
//실제로 GIF를 출력하는 함수
void D2DEngine::DrawGIF(int gifIndex, Transform* transform)
{
	GIFStruct* _gifSheet = m_GIFSheets[gifIndex];
	DrawGIFByStruct(*_gifSheet, transform);
}

void D2DEngine::DrawGIFByStruct(GIFStruct& gifStruct, Transform* transform)
{
	HRESULT hr = S_OK;
	ID2D1Bitmap* p_TmpFrameToRender = NULL;

	if (m_pRenderTarget && gifStruct.m_pFrameComposeRT)
	{
		if (!(m_pRenderTarget->CheckWindowState() & D2D1_WINDOW_STATE_OCCLUDED))
		{
			D2D1_RECT_F drawRect;
			GetRectFromGIFIndex(drawRect, gifStruct.m_GIFIndex, transform);
			///이제 여기서 이미지의 Width, Rect를 받아와야 한다.
			if (SUCCEEDED(hr))
			{
				// Get the bitmap to draw on the hwnd render target
				hr = gifStruct.m_pFrameComposeRT->GetBitmap(&p_TmpFrameToRender);
			}
			if (SUCCEEDED(hr))
			{
				//// Draw the bitmap onto the calculated rectangle
				//m_pRenderTarget->BeginDraw();
				//m_pRenderTarget->Clear(D2D1::ColorF(1, 0, 1, 0)); //Alpha값이 0인 Image로 Clear, 뒤에 있는 이미지가 출력될 수 있게 바꾸어 준다.

				D2D1_MATRIX_3X2_F rotation = Matrix3x2F::Rotation(
					transform->GetRotation(),
					Point2F(
						transform->GetPosition().x,
						transform->GetPosition().y)
				);

				D2D1_SIZE_F sizeTrans = {
					transform->GetScale().x,
					transform->GetScale().y
				};

				D2D1_MATRIX_3X2_F scale =
					Matrix3x2F::Scale(sizeTrans,
						Point2F(
							transform->GetPosition().x,
							transform->GetPosition().y)
					);

				m_pRenderTarget->SetTransform(scale * rotation);
				m_pRenderTarget->DrawBitmap(p_TmpFrameToRender, drawRect);

				if (gifStruct.m_cFrames > 0) //다음 프레임 쫙 잡기
				{
					hr = ComposeNextFrame(gifStruct);
					InvalidateRect(m_hWnd, NULL, FALSE);
				}
			}
		}
	}
	//Debug::Trace(" END DrawGIFByStruct: ", gifStruct.m_GIFIndex);
}


void D2DEngine::DrawGIFWithPos(int gifIndex, float posX, float posY, Transform* transform)
{
	//Debug::Trace("DrawGIFWithPos: ", gifIndex);

	GIFStruct* _gifSheet = m_GIFSheets[gifIndex];
	DrawGIFByStruct_Pos(*_gifSheet, posX, posY, transform);
}

void D2DEngine::DrawGIFByStruct_Pos(GIFStruct& gifStruct, float posX, float posY, Transform* transform)
{
	//Debug::Trace("DrawGIFByStruct_Pos: ", gifStruct.m_GIFIndex);

	HRESULT hr = S_OK;
	ID2D1Bitmap* p_TmpFrameToRender = NULL;

	if (m_pRenderTarget && gifStruct.m_pFrameComposeRT)
	{
		if (!(m_pRenderTarget->CheckWindowState() & D2D1_WINDOW_STATE_OCCLUDED))
		{
			D2D1_RECT_F drawRect;
			GetRectFromGIFIndexWithPos(drawRect, gifStruct.m_GIFIndex, posX, posY);
			///이제 여기서 이미지의 Width, Rect를 받아와야 한다.
			if (SUCCEEDED(hr))
			{
				// Get the bitmap to draw on the hwnd render target
				hr = gifStruct.m_pFrameComposeRT->GetBitmap(&p_TmpFrameToRender);
			}
			if (SUCCEEDED(hr))
			{
				//// Draw the bitmap onto the calculated rectangle
				//m_pRenderTarget->BeginDraw();

				//m_pRenderTarget->Clear(D2D1::ColorF(1, 0, 1, 0)); //Alpha값이 0인 Image로 Clear, 뒤에 있는 이미지가 출력될 수 있게 바꾸어 준다.

				D2D1_MATRIX_3X2_F rotation = Matrix3x2F::Rotation(
					transform->GetRotation(),
					Point2F(
						posX,
						posY)
				);

				D2D1_SIZE_F sizeTrans = {
					transform->GetScale().x,
					transform->GetScale().y
				};

				D2D1_MATRIX_3X2_F scale =
					Matrix3x2F::Scale(sizeTrans,
						Point2F(
							posX,
							posY)
					);

				m_pRenderTarget->SetTransform(scale * rotation);
				m_pRenderTarget->DrawBitmap(p_TmpFrameToRender, drawRect);

				if (gifStruct.m_cFrames > 0) //다음 프레임 쫙 잡기
				{
					hr = ComposeNextFrame(gifStruct);
					InvalidateRect(m_hWnd, NULL, FALSE);
				}
			}
		}
	}
	//Debug::Trace(" END DrawGIFByStruct_Pos: ", gifStruct.m_GIFIndex);
}
#pragma endregion

/// private
#pragma region Create
HRESULT D2DEngine::CreateDeviceResources()
{
	// D2D팩토리를 생성한다.
	m_hResult = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pFactory);
	// 갈색문장의 뜻-> 생성된 팩토리가 직렬로만 호출이 된다는 뜻이다.
	// 리소스에 대한 참조 카운트는 리소스 및 렌더와 연동됩니다
	// 다중 프로토콜 액세스로부터 대상 상태가 보호되지 않습니다.??

	// 위에있는 팩토리가 성공적으로 생성하면 if문으로 들어감
	if (SUCCEEDED(m_hResult))
	{
		RECT rect;
		// 사용자의 화면 크기를 받아온다.->실행시킬시 뜨는 윈도우 창의 크기를 받아온다.
		GetClientRect(m_hWnd, &rect);

		D2D1_RENDER_TARGET_PROPERTIES renderTargetProperties
			= D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_DEFAULT,
				D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED)); ///[TW] GIF 호환용

		D2D1_SIZE_U screenSize = D2D1::SizeU(rect.right, rect.bottom); ///[TW] GIF 호환용

		renderTargetProperties.dpiX = DEFAULT_DPI;
		renderTargetProperties.dpiY = DEFAULT_DPI;

		// 팩토리를 이용해서 랜더 타겟 생성->
		m_hResult = m_pFactory->CreateHwndRenderTarget(
			renderTargetProperties,
			HwndRenderTargetProperties
			(m_hWnd,
				screenSize),
			&m_pRenderTarget);

		//이미지 팩토리
		m_hResult = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER,
			IID_PPV_ARGS(&m_pWicFactory));

		// 텍스트 팩토리
		m_hResult = DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(IDWriteFactory),
			reinterpret_cast<IUnknown**>(&m_pDWriteFactory)
		);

		m_hResult = m_pDWriteFactory->CreateTextFormat(
			L"Gabriola",
			NULL,
			DWRITE_FONT_WEIGHT_REGULAR,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			50.0f,
			L"ko-KR",
			&m_pTextFormat
		);
	}
	return m_hResult;
}

void D2DEngine::CreateBrush()
{
	m_pRenderTarget->CreateSolidColorBrush(ColorF(ColorF::Red), &m_pRedBrush);
	m_pRenderTarget->CreateSolidColorBrush(ColorF(ColorF::Green), &m_pGreenBrush);
	m_pRenderTarget->CreateSolidColorBrush(ColorF(ColorF::Blue), &m_pBlueBrush);
	m_pRenderTarget->CreateSolidColorBrush(ColorF(ColorF::White), &m_pWhiteBrush);
	m_pRenderTarget->CreateSolidColorBrush(ColorF(ColorF::Black), &m_pBlackBrush);
}
#pragma endregion
#pragma region Load Image With filePath
void D2DEngine::LoadImageResources()
{
	/// 타이틀
	LoadSpriteSheet("Resource\\Image\\Title.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_TITLE, 0, 0, 441, 736, 1));

	///캐릭터
	LoadSpriteSheet("Resource\\Image\\Player\\Player.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_PLAYER, 0, 0, 441, 736, 1));

	///배경
	LoadSpriteSheet("Resource\\Image\\Background\\Stage1.jpg");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_STAGE1_BACKGROUND, 0, 0, 4800, 7200, 1));	// Stage1
	LoadSpriteSheet("Resource\\Image\\Background\\Stage2.jpg");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_STAGE2_BACKGROUND, 0, 0, 4800, 7200, 1));	// Stage2
	LoadSpriteSheet("Resource\\Image\\Background\\Stage3.jpg");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_STAGE3_BACKGROUND, 0, 0, 10000, 1500, 1));	// Stage3
	LoadSpriteSheet("Resource\\Image\\Background\\Planet_BG.jpg");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_PLANET_BACKGROUND, 0, 0, 4800, 7200, 1));	// 행성씬
	LoadSpriteSheet("Resource\\Image\\Background\\SnakePlanet.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_SNAKEPLANET_BACKGROUND, 0, 0, 1920, 1080, 1));	// 스네이크행성씬
	LoadSpriteSheet("Resource\\Image\\Background\\StoryPlanet.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_STORYPLANET_BACKGROUND, 0, 0, 1920, 1080, 1));	// 스토리행성씬


	///행성
	LoadSpriteSheet("Resource\\Image\\SpaceObject\\Planet\\IcePlanet.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_ICE_PLANET, 0, 0, 1500, 1500, 1));		// 얼음 행성
	LoadSpriteSheet("Resource\\Image\\SpaceObject\\Planet\\LavaPlanet.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_LAVA_PLANET, 0, 0, 1500, 1500, 1));	// 용암 행성
	LoadSpriteSheet("Resource\\Image\\SpaceObject\\Planet\\SnakePlanet.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_SNAKE_PLANET, 0, 0, 1500, 1500, 1));	// 뱀 행성
	LoadSpriteSheet("Resource\\Image\\SpaceObject\\Planet\\storyplanet.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_STORY_PLANET, 0, 0, 1500, 1500, 1));	// 이야기 행성

	///블랙홀, 포탈, 인공위성
	LoadSpriteSheet("Resource\\Image\\SpaceObject\\blackhole.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_BLACKHOLE, 0, 0, 500, 500, 1));
	LoadSpriteSheet("Resource\\Image\\SpaceObject\\Blackhole_side.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_BLACKHOLE_SIDE, 0, 0, 398, 1740, 1));

	LoadSpriteSheet("Resource\\Image\\SpaceObject\\portal.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_PORTAL, 0, 0, 500, 500, 1));
	LoadSpriteSheet("Resource\\Image\\SpaceObject\\Portal_Sea.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_PORTAL_SEA, 0, 0, 2670, 310, 1));

	LoadSpriteSheet("Resource\\Image\\SpaceObject\\satellite.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_SATELLITE, 0, 0, 200, 200, 1));

	///워링 표시
	//LoadSpriteSheet("Resource\\Image\\UI\\Warining.png");
	//m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_WARNING, 0, 0, 600, 600, 1));

	///별똥별
	LoadSpriteSheet("Resource\\Image\\SpaceObject\\Star\\ShootingStar.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_SHOOTING_STAR, 0, 0, 100, 100, 1));
	LoadSpriteSheet("Resource\\Image\\SpaceObject\\Star\\ShootingStarTail.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_SHOOTING_STAR_TAIL, 0, 0, 150, 150, 1));

	///별조각
	LoadSpriteSheet("Resource\\Image\\SpaceObject\\Star\\StarPiece1.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_STAR_PIECE1, 0, 0, 100, 100, 1));
	LoadSpriteSheet("Resource\\Image\\SpaceObject\\Star\\StarPiece2.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_STAR_PIECE2, 0, 0, 100, 100, 1));
	LoadSpriteSheet("Resource\\Image\\SpaceObject\\Star\\StarPiece3.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_STAR_PIECE3, 0, 0, 100, 100, 1));

	///유리병
	LoadSpriteSheet("Resource\\Image\\SpecialObject\\GlassBottle.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_GLASS_BOTTLE, 0, 0, 100, 100, 1));
	LoadSpriteSheet("Resource\\Image\\SpecialObject\\Potion.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_POTION, 0, 0, 100, 100, 1));

	///노트
	LoadSpriteSheet("Resource\\Image\\UI\\NoteMain.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_NOTE_MAIN, 0, 0, 1222, 824, 1));
	LoadSpriteSheet("Resource\\Image\\UI\\NoteButton.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_NOTE_BUTTON, 0, 0, 231, 168, 1));

	///조각상
	LoadSpriteSheet("Resource\\Image\\SpaceObject\\Statue\\Bear.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_BEAR_STATUE, 0, 0, 2000, 2000, 1));
	LoadSpriteSheet("Resource\\Image\\SpaceObject\\Statue\\Bird.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_BIRD_STATUE, 0, 0, 2000, 2000, 1));
	LoadSpriteSheet("Resource\\Image\\SpaceObject\\Statue\\Dear.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_DEAR_STATUE, 0, 0, 2000, 2000, 1));
	LoadSpriteSheet("Resource\\Image\\SpaceObject\\Statue\\Grandpa.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_GRANDPA_STATUE, 0, 0, 2000, 2000, 1));
	LoadSpriteSheet("Resource\\Image\\SpaceObject\\Statue\\Whale.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_WHALE_STATUE, 0, 0, 2000, 2000, 1));	
	LoadSpriteSheet("Resource\\Image\\SpaceObject\\Statue\\ColorUnder.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_UNDER_STATUE, 0, 0, 2000, 2000, 1));

	///부스터 게이지
	LoadSpriteSheet("Resource\\Image\\UI\\BoosterGage0.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_BOOSTER_GAGE0, 0, 0, 597, 158, 1));
	LoadSpriteSheet("Resource\\Image\\UI\\BoosterGage1.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_BOOSTER_GAGE1, 0, 0, 597, 158, 1));
	LoadSpriteSheet("Resource\\Image\\UI\\BoosterGage2.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_BOOSTER_GAGE2, 0, 0, 597, 158, 1));
	LoadSpriteSheet("Resource\\Image\\UI\\BoosterGage3.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_BOOSTER_GAGE3, 0, 0, 597, 158, 1));
	///부스터 화살표
	LoadSpriteSheet("Resource\\Image\\UI\\BoosterArrow.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_BOOSTER_ARROW, 0, 0, 150, 150, 1));


	// MAIN UI
	LoadSpriteSheet("Resource\\Image\\Background\\Main_With_Title.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_MAIN_BACKGROUND, 0, 0, 1920, 1080, 1));		// main_background
	LoadSpriteSheet("Resource\\Image\\UI\\Button\\StartGame.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_START, 0, 0, 600, 129, 1));					// start_button
	LoadSpriteSheet("Resource\\Image\\UI\\Button\\StartGame_A.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_START_A, 0, 0, 600, 129, 1));				// active_start_button
	LoadSpriteSheet("Resource\\Image\\UI\\Button\\Option.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_OPTION, 0, 0, 600, 129, 1));					// option_button
	LoadSpriteSheet("Resource\\Image\\UI\\Button\\Option_A.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_OPTION_A, 0, 0, 600, 129, 1));				// active_option_button
	LoadSpriteSheet("Resource\\Image\\UI\\Button\\Credit.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_CREDIT, 0, 0, 600, 129, 1));					// credit_button
	LoadSpriteSheet("Resource\\Image\\UI\\Button\\Credit_A.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_CREDIT_A, 0, 0, 600, 129, 1));				// active_credit_button
	LoadSpriteSheet("Resource\\Image\\UI\\Credit_INFO.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_CREDIT_I, 0, 0, 707, 707, 1));				// active_credit_button
	LoadSpriteSheet("Resource\\Image\\UI\\Button\\Quit.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_QUIT, 0, 0, 123, 46, 1));					// quit_button
	LoadSpriteSheet("Resource\\Image\\UI\\Button\\Quit_A.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_QUIT_A, 0, 0, 123, 46, 1));					// active_quit_button
	LoadSpriteSheet("Resource\\Image\\UI\\Option_Menu.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_OPTION_MENU, 0, 0, 707, 707, 1));					// active_quit_button
	LoadSpriteSheet("Resource\\Image\\UI\\Option_Bar.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_OPTION_BAR, 0, 0, 394, 24, 1));					// active_quit_button
	LoadSpriteSheet("Resource\\Image\\UI\\Option_Box.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_OPTION_BOX, 0, 0, 48, 41, 1));					// active_quit_button
	LoadSpriteSheet("Resource\\Image\\UI\\Button\\Option_Quit.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_OPTION_QUIT, 0, 0, 60, 60, 1));					// active_quit_button
	LoadSpriteSheet("Resource\\Image\\UI\\Button\\Option_gomain.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_OPTION_GO_MAIN, 0, 0, 82, 82, 1));					// active_quit_button
	LoadSpriteSheet("Resource\\Image\\UI\\Button\\Option_retry.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_OPTION_RETRY, 0, 0, 82, 82, 1));					// active_quit_button

	///노트UI
	LoadSpriteSheet("Resource\\Image\\UI\\Note1.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_NOTE1, 0, 0, 355, 349, 1));
	LoadSpriteSheet("Resource\\Image\\UI\\Note1Write.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_NOTE1_WRITE, 0, 0, 355, 349, 1));

	LoadSpriteSheet("Resource\\Image\\UI\\Note2.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_NOTE2, 0, 0, 416, 257, 1));
	LoadSpriteSheet("Resource\\Image\\UI\\Note2Write.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_NOTE2_WRITE, 0, 0, 416, 257, 1));

	LoadSpriteSheet("Resource\\Image\\UI\\Note3.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_NOTE3, 0, 0, 354, 347, 1));
	LoadSpriteSheet("Resource\\Image\\UI\\Note3Write.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_NOTE3_WRITE, 0, 0, 354, 347, 1));

	LoadSpriteSheet("Resource\\Image\\UI\\Note4.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_NOTE4, 0, 0, 186, 187, 1));
	LoadSpriteSheet("Resource\\Image\\UI\\Note4Write.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_NOTE4_WRITE, 0, 0, 186, 187, 1));

	LoadSpriteSheet("Resource\\Image\\UI\\Note5.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_NOTE5, 0, 0, 412, 187, 1));
	LoadSpriteSheet("Resource\\Image\\UI\\Note5Write.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_NOTE5_WRITE, 0, 0, 412, 187, 1));

	LoadSpriteSheet("Resource\\Image\\UI\\Heart.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_HEALTH_POINT, 0, 0, 68, 68, 1));

	LoadSpriteSheet("Resource\\Image\\UI\\OptionButton.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_OPTION_BUTTON, 0, 0, 68, 68, 1));	//디버그용. 콜리젼/물리 디버그 끝날 때까지는, 없애면 안됩니다.

	///미션UI
	LoadSpriteSheet("Resource\\Image\\UI\\Mission.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_MISSION_UI, 0, 0, 350, 343, 1));	//디버그용. 콜리젼/물리 디버그 끝날 때까지는, 없애면 안됩니다.

	LoadSpriteSheet("Resource\\Image\\Test\\DebugBrick.bmp");
	m_SpritePool.push_back(LoadSpriteFromSheet(DEBUG_BRICK, 0, 0, 512, 512, 1));

	LoadSpriteSheet("Resource\\Image\\Test\\DebugGrass.bmp");
	m_SpritePool.push_back(LoadSpriteFromSheet(DEBUG_GRASS, 0, 0, 512, 512, 1));

	LoadSpriteSheet("Resource\\Image\\Test\\DebugWood.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(DEBUG_WOOD, 0, 0, 398, 398, 1));

	/// 컷씬
	// Opening
	LoadSpriteSheet("Resource\\Image\\CutScene\\opening\\Opening1.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_OPENING_SCENE1, 0, 0, 1700, 850, 1));
	LoadSpriteSheet("Resource\\Image\\CutScene\\opening\\Opening2.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_OPENING_SCENE2, 0, 0, 1700, 850, 1));
	LoadSpriteSheet("Resource\\Image\\CutScene\\opening\\Opening3.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_OPENING_SCENE3, 0, 0, 700, 600, 1));
	LoadSpriteSheet("Resource\\Image\\CutScene\\opening\\Opening4.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_OPENING_SCENE4, 0, 0, 1000, 600, 1));
	LoadSpriteSheet("Resource\\Image\\CutScene\\opening\\Opening5.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_OPENING_SCENE5, 0, 0, 1700, 850, 1));

	// Normal
	LoadSpriteSheet("Resource\\Image\\CutScene\\Normal_Ending\\Normal1.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_NORMAL_SCENE, 0, 0, 1700, 850, 1));

	// Bad
	LoadSpriteSheet("Resource\\Image\\CutScene\\Bad_Ending\\Bad1.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_BAD_SCENE1, 0, 0, 1700, 850, 1));
	LoadSpriteSheet("Resource\\Image\\CutScene\\Bad_Ending\\Bad2.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_BAD_SCENE2, 0, 0, 1700, 850, 1));

	// True
	LoadSpriteSheet("Resource\\Image\\CutScene\\True_Ending\\True1.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_TRUE_SCENE1, 0, 0, 1700, 850, 1));
	LoadSpriteSheet("Resource\\Image\\CutScene\\True_Ending\\True2.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_TRUE_SCENE2, 0, 0, 1700, 850, 1));
	LoadSpriteSheet("Resource\\Image\\CutScene\\True_Ending\\True3.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_TRUE_SCENE3, 0, 0, 1700, 850, 1));
	LoadSpriteSheet("Resource\\Image\\CutScene\\True_Ending\\True4.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_TRUE_SCENE4, 0, 0, 1700, 850, 1));
	LoadSpriteSheet("Resource\\Image\\CutScene\\True_Ending\\True5.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_TRUE_SCENE5, 0, 0, 1700, 850, 1));
	LoadSpriteSheet("Resource\\Image\\CutScene\\True_Ending\\True6.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_TRUE_SCENE6, 0, 0, 1700, 850, 1));
	LoadSpriteSheet("Resource\\Image\\CutScene\\True_Ending\\True7.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_TRUE_SCENE7, 0, 0, 1700, 850, 1));
	LoadSpriteSheet("Resource\\Image\\CutScene\\True_Ending\\True8_1.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_TRUE_SCENE8_1, 0, 0, 700, 600, 1));
	LoadSpriteSheet("Resource\\Image\\CutScene\\True_Ending\\True8_2.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_TRUE_SCENE8_2, 0, 0, 1000, 600, 1));
	LoadSpriteSheet("Resource\\Image\\CutScene\\True_Ending\\True9.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_TRUE_SCENE9, 0, 0, 1000, 600, 1));
	LoadSpriteSheet("Resource\\Image\\CutScene\\True_Ending\\True10.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_TRUE_SCENE10, 0, 0, 1000, 600, 1));
	LoadSpriteSheet("Resource\\Image\\CutScene\\True_Ending\\True11.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_TRUE_SCENE11, 0, 0, 1000, 600, 1));
	LoadSpriteSheet("Resource\\Image\\CutScene\\True_Ending\\True12.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_TRUE_SCENE12, 0, 0, 1000, 600, 1));
	LoadSpriteSheet("Resource\\Image\\CutScene\\True_Ending\\True13.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_TRUE_SCENE13, 0, 0, 1700, 850, 1));

	// gameover
	LoadSpriteSheet("Resource\\Image\\UI\\Button\\GameOver.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_GAMEOVER, 0, 0, 800, 400, 1));

	LoadSpriteSheet("Resource\\Image\\UI\\Button\\GameOver_Main.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_GAMEOVER_MAIN, 0, 0, 800, 400, 1));

	LoadSpriteSheet("Resource\\Image\\UI\\Button\\GameOver_Retry.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_GAMEOVER_RETRY, 0, 0, 800, 400, 1));

	/// 컷씬 대사
	// Opening
	LoadSpriteSheet("Resource\\Image\\CutScene\\opening\\Opening_Line1.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_OPENING_LINE1, 0, 0, 836, 103, 1));
	LoadSpriteSheet("Resource\\Image\\CutScene\\opening\\Opening_Line2.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_OPENING_LINE2, 0, 0, 1018, 103, 1));
	LoadSpriteSheet("Resource\\Image\\CutScene\\opening\\Opening_Line3.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_OPENING_LINE3, 0, 0, 535, 43, 1));
	LoadSpriteSheet("Resource\\Image\\CutScene\\opening\\Opening_Line4.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_OPENING_LINE4, 0, 0, 594, 101, 1));
	LoadSpriteSheet("Resource\\Image\\CutScene\\opening\\Opening_Line5.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_OPENING_LINE5, 0, 0, 834, 99, 1));


	// Normal
	LoadSpriteSheet("Resource\\Image\\CutScene\\Normal_Ending\\Normal_Line1.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_NORMAL_LINE1, 0, 0, 894, 111, 1));


	// Bad
	LoadSpriteSheet("Resource\\Image\\CutScene\\Bad_Ending\\Bad_Line1.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_BAD_LINE1, 0, 0, 726, 51, 1));

	// True
	LoadSpriteSheet("Resource\\Image\\CutScene\\True_Ending\\True_Line1.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_TRUE_LINE1, 0, 0, 182, 61, 1));
	LoadSpriteSheet("Resource\\Image\\CutScene\\True_Ending\\True_Line2.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_TRUE_LINE2, 0, 0, 544, 59, 1));
	LoadSpriteSheet("Resource\\Image\\CutScene\\True_Ending\\True_Line3.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_TRUE_LINE3, 0, 0, 640, 62, 1));
	LoadSpriteSheet("Resource\\Image\\CutScene\\True_Ending\\True_Line4.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_TRUE_LINE4, 0, 0, 924, 61, 1));
	LoadSpriteSheet("Resource\\Image\\CutScene\\True_Ending\\True_Line5.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_TRUE_LINE5, 0, 0, 1238, 59, 1));
	LoadSpriteSheet("Resource\\Image\\CutScene\\True_Ending\\True_Line6.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_TRUE_LINE6, 0, 0, 564, 61, 1));
	LoadSpriteSheet("Resource\\Image\\CutScene\\True_Ending\\True_Line7.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_TRUE_LINE7, 0, 0, 1194, 61, 1));
	LoadSpriteSheet("Resource\\Image\\CutScene\\True_Ending\\True_Line8.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_TRUE_LINE8, 0, 0, 668, 60, 1));
	LoadSpriteSheet("Resource\\Image\\CutScene\\True_Ending\\True_Line9.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_TRUE_LINE9, 0, 0, 780, 62, 1));
	LoadSpriteSheet("Resource\\Image\\CutScene\\True_Ending\\True_Line10.png");
	m_SpritePool.push_back(LoadSpriteFromSheet(IMAGE_TRUE_LINE10, 0, 0, 500, 87, 1));

}

void D2DEngine::LoadGIFResources()
{
	//GIF출력 위해서는 LoadGIF / DrawGIF 해야 한다.
//자동으로 push_back을 해준다, 밀어넣을 필요X.
//LoadGIF가 호출된 순서는 GIFIndex에 직접적인 영향을 미친다.
//LoadGIF를 쓰는 순서 = GIFIndex, 0에서 시작. (..1..2..3..)

LoadGIF(L"Resource\\Image\\Player\\standing.gif"); 
LoadGIF(L"Resource\\Image\\Player\\standing_L.gif"); 
LoadGIF(L"Resource\\Image\\Player\\up_R.gif"); 
LoadGIF(L"Resource\\Image\\Player\\up_L.gif"); 
LoadGIF(L"Resource\\Image\\Player\\side_R_standing.gif"); 
LoadGIF(L"Resource\\Image\\Player\\side_L_standing.gif"); 
LoadGIF(L"Resource\\Image\\Player\\L_down.gif");
LoadGIF(L"Resource\\Image\\Player\\R_down.gif");
LoadGIF(L"Resource\\Image\\Player\\side_L_go.gif"); 
LoadGIF(L"Resource\\Image\\Player\\side_R_go.gif"); 

LoadGIF(L"Resource\\Image\\UI\\fade\\fadein.gif");	// 페이드 아웃
LoadGIF(L"Resource\\Image\\UI\\fade\\fadeout.gif");	// 페이드 인


LoadGIF(L"Resource\\Image\\SpaceObject\\Statue\\Bear_op.gif");	
LoadGIF(L"Resource\\Image\\SpaceObject\\Statue\\Bird_op.gif");	
LoadGIF(L"Resource\\Image\\SpaceObject\\Statue\\Dear_op.gif");	
LoadGIF(L"Resource\\Image\\SpaceObject\\Statue\\Whale_op.gif");	
LoadGIF(L"Resource\\Image\\SpaceObject\\Statue\\Grandpa_op.gif");	

//[TW] 마지막 걸로 되는 듯.
}
#pragma endregion
#pragma region Load Sprite
int D2DEngine::LoadSpriteSheet(const char* filePath)
{
	HRESULT hr;
	ID2D1Bitmap* pNewBitmap;

	wchar_t* _wcstring = this->ConvertCStoWCS(filePath);

	hr = LoadBitmapFromFile(
		m_pRenderTarget,
		m_pWicFactory,
		_wcstring,
		0,
		0,
		&pNewBitmap
	);

	delete[] _wcstring;

	if (SUCCEEDED(hr))
	{
		m_SpriteSheets.insert(pair<int, ID2D1Bitmap*>(m_SpriteSheetCount, pNewBitmap));
		m_SpriteSheetCount++;

		return (m_SpriteSheetCount - 1);
	}
	else
	{
		return -1;
	}
}

DRSprite* D2DEngine::LoadSpriteFromSheet(int sheetIndex, int oriX, int oriY, int width, int height, int delayFrame)
{
	D2DSprite* _newSprite = new D2DSprite(sheetIndex, oriX, oriY, m_SpriteCount, width, height,
		0, 0, 0, delayFrame, RECT(), RECT(), 1);
	m_SpriteInfos.push_back(_newSprite);
	m_SpriteCount++;

	///[TW] 게임 내에서 Width와 Height을 받는게 얘네들밖에 없는 상태,
	/// 콜라이더 구현을 위해 CollideInfoMap 헤더를 연결, 따로 연결고리를 만들 것임.
	CollideInfoMap::GetInstance().AddWidthHeightToMap(sheetIndex, width, height);

	return _newSprite;
}
#pragma endregion
#pragma region Load GIF

void D2DEngine::LoadGIF(wstring filePath)
{
	HRESULT hr = S_OK;
	static int tmpGIFIndex = 0;
	//Debug::Trace("Loaded GIF..", tmpGIFIndex);
	GIFStruct* tmpGif = new GIFStruct(); //지옥 GIF 디버깅 시작.

	hr = MakeGIF(filePath, *tmpGif, tmpGIFIndex);

	if (SUCCEEDED(hr))
	{
		tmpGif->m_GIFIndex = tmpGIFIndex;
		m_GIFSheets.insert(pair<int, GIFStruct*>(tmpGIFIndex, tmpGif));
		tmpGIFIndex++;
	}
}

//GIF를 로드하는 함수, 매개변수로 FilePath를 받는다.
HRESULT D2DEngine::MakeGIF(wstring filePath, GIFStruct& gifStruct, int gifIndex)
{
	//Debug::Trace("Made GIF",gifIndex);
	HRESULT hr = S_OK;
	WCHAR szFileName[MAX_PATH];
	RECT rcClient = {};
	RECT rcWindow = {};

	const wchar_t* tmpFilePath = filePath.c_str(); //FilePath를 받는 경로.

	//[TW] Index를 원래대로 배정.
	gifStruct.m_GIFIndex = gifIndex;

	gifStruct.m_uNextFrameIndex = 0;
	gifStruct.m_uFrameDisposal = DM_NONE;  // No previous frame, use disposal none
	gifStruct.m_uLoopNumber = 0;
	gifStruct.m_fHasLoop = FALSE;
	SafeReleaseGIF(gifStruct.m_pSavedFrame);

	//GIF 출력을 위한 디코더를 준비한다. [TW] -> 추후에 이를 한번만 실행해도 되는지 볼것.
	SafeReleaseGIF(gifStruct.m_pBitDecoder);
	hr = m_pWicFactory->CreateDecoderFromFilename(
		tmpFilePath, /// [TW] 이거를 바꿔보겠음.
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&(gifStruct.m_pBitDecoder));

	if (SUCCEEDED(hr))
	{
		//Global Metadata?
		//GIF 메타데이터는 일반적으로 파일마다 있는 정보를 인코딩하고,
		//이미지 설명, 지역 색깔 테이블, 그리고 확장자 정보를 담고 있다.
		//GIF 출력을 위해 필수적인 것.
		hr = GetGlobalMetadata(gifStruct, gifIndex);
	}
	hr = RecreateBitmapRT(gifStruct);

	if (gifStruct.m_cFrames > 0) //다음 프레임 쫙 잡기
	{
		hr = ComposeNextFrame(gifStruct);
		InvalidateRect(m_hWnd, NULL, FALSE);
	}
	//Debug::Trace("END MakeGIF: ", gifStruct.m_GIFIndex);
	return hr;
}
#pragma endregion
#pragma region GIF 
HRESULT D2DEngine::GetRawFrame(UINT uFrameIndex, GIFStruct& gifStruct)
{
	//Debug::Trace("GetRawFrame: ", gifStruct.m_GIFIndex);

	IWICFormatConverter* pConverter = NULL;
	IWICBitmapFrameDecode* pWicFrame = NULL;
	IWICMetadataQueryReader* pFrameMetadataQueryReader = NULL;

	PROPVARIANT propValue;
	PropVariantInit(&propValue);

	// Retrieve the current frame
	HRESULT hr = gifStruct.m_pBitDecoder->GetFrame(uFrameIndex, &pWicFrame);
	if (SUCCEEDED(hr))
	{
		// Format convert to 32bppPBGRA which D2D expects
		hr = m_pWicFactory->CreateFormatConverter(&pConverter);
	}

	if (SUCCEEDED(hr))
	{
		hr = pConverter->Initialize(
			pWicFrame,
			GUID_WICPixelFormat32bppPBGRA,
			WICBitmapDitherTypeNone,
			NULL,
			0.f,
			WICBitmapPaletteTypeCustom);
	}

	if (SUCCEEDED(hr))
	{
		// Create a D2DBitmap from IWICBitmapSource
		SafeRelease(&(gifStruct.m_pRawFrame));
		hr = m_pRenderTarget->CreateBitmapFromWicBitmap(
			pConverter,
			NULL,
			&(gifStruct.m_pRawFrame));
	}

	if (SUCCEEDED(hr))
	{
		// Get Metadata Query Reader from the frame
		hr = pWicFrame->GetMetadataQueryReader(&pFrameMetadataQueryReader);
	}

	// Get the Metadata for the current frame
	if (SUCCEEDED(hr))
	{
		hr = pFrameMetadataQueryReader->GetMetadataByName(L"/imgdesc/Left", &propValue);
		if (SUCCEEDED(hr))
		{
			hr = (propValue.vt == VT_UI2 ? S_OK : E_FAIL);
			if (SUCCEEDED(hr))
			{
				(gifStruct.m_framePosition).left = static_cast<FLOAT>(propValue.uiVal);
			}
			PropVariantClear(&propValue);
		}
	}

	if (SUCCEEDED(hr))
	{
		hr = pFrameMetadataQueryReader->GetMetadataByName(L"/imgdesc/Top", &propValue);
		if (SUCCEEDED(hr))
		{
			hr = (propValue.vt == VT_UI2 ? S_OK : E_FAIL);
			if (SUCCEEDED(hr))
			{
				(gifStruct.m_framePosition).top = static_cast<FLOAT>(propValue.uiVal);
			}
			PropVariantClear(&propValue);
		}
	}

	if (SUCCEEDED(hr))
	{
		hr = pFrameMetadataQueryReader->GetMetadataByName(L"/imgdesc/Width", &propValue);
		if (SUCCEEDED(hr))
		{
			hr = (propValue.vt == VT_UI2 ? S_OK : E_FAIL);
			if (SUCCEEDED(hr))
			{
				(gifStruct.m_framePosition).right = static_cast<FLOAT>(propValue.uiVal)
					+ (gifStruct.m_framePosition).left;
			}
			PropVariantClear(&propValue);
		}
	}

	if (SUCCEEDED(hr))
	{
		hr = pFrameMetadataQueryReader->GetMetadataByName(L"/imgdesc/Height", &propValue);
		if (SUCCEEDED(hr))
		{
			hr = (propValue.vt == VT_UI2 ? S_OK : E_FAIL);
			if (SUCCEEDED(hr))
			{
				(gifStruct.m_framePosition).bottom = static_cast<FLOAT>(propValue.uiVal)
					+ (gifStruct.m_framePosition).top;
			}
			PropVariantClear(&propValue);
		}
	}

	if (SUCCEEDED(hr))
	{
		// Get delay from the optional Graphic Control Extension
		if (SUCCEEDED(pFrameMetadataQueryReader->GetMetadataByName(
			L"/grctlext/Delay",
			&propValue)))
		{
			hr = (propValue.vt == VT_UI2 ? S_OK : E_FAIL);
			if (SUCCEEDED(hr))
			{
				// Convert the delay retrieved in 10 ms units to a delay in 1 ms units
				hr = UIntMult(propValue.uiVal, 10, &(gifStruct.m_uFrameDelay));
			}
			PropVariantClear(&propValue);
		}
		else
		{
			// Failed to get delay from graphic control extension. Possibly a
			// single frame image (non-animated gif)
			gifStruct.m_uFrameDelay = 0;
		}

		if (SUCCEEDED(hr))
		{
			// Insert an artificial delay to ensure rendering for gif with very small
			// or 0 delay.  This delay number is picked to match with most browsers' 
			// gif display speed.
			//
			// This will defeat the purpose of using zero delay intermediate frames in 
			// order to preserve compatibility. If this is removed, the zero delay 
			// intermediate frames will not be visible.
			if (gifStruct.m_uFrameDelay < 3)
			{
				gifStruct.m_uFrameDelay = 3;
			}
		}
	}

	if (SUCCEEDED(hr))
	{
		if (SUCCEEDED(pFrameMetadataQueryReader->GetMetadataByName(
			L"/grctlext/Disposal",
			&propValue)))
		{
			hr = (propValue.vt == VT_UI1) ? S_OK : E_FAIL;
			if (SUCCEEDED(hr))
			{
				gifStruct.m_uFrameDisposal = propValue.bVal;
			}
		}
		else
		{
			// Failed to get the disposal method, use default. Possibly a 
			// non-animated gif.
			gifStruct.m_uFrameDisposal = DM_UNDEFINED;
		}
	}
	PropVariantClear(&propValue);

	SafeRelease(&pConverter);
	SafeRelease(&pWicFrame);
	SafeRelease(&pFrameMetadataQueryReader);

	//Debug::Trace("END GetRawFrame: ", gifStruct.m_GIFIndex);

	return hr;
}

//GIF 출력 과정에서 그대로 쓰임. 수정 완
HRESULT D2DEngine::GetGlobalMetadata(GIFStruct& gifStruct, int gifIndex)
{
	//Debug::Trace("GetGlobalMetadata: ", gifStruct.m_GIFIndex);

	PROPVARIANT propValue;
	PropVariantInit(&propValue);
	IWICMetadataQueryReader* pMetadataQueryReader = NULL;

	// Get the frame count
	HRESULT hr = gifStruct.m_pBitDecoder->GetFrameCount(&(gifStruct.m_cFrames));
	if (SUCCEEDED(hr))
	{
		// Create a MetadataQueryReader from the decoder
		hr = gifStruct.m_pBitDecoder->GetMetadataQueryReader(
			&pMetadataQueryReader);
	}

	if (SUCCEEDED(hr))
	{
		// Get background color
		if (FAILED(GetBackgroundColor(pMetadataQueryReader,gifStruct)))
		{
			// Default to transparent if failed to get the color
			m_backgroundColor = ColorF(0, 0.f);
		}
	}

	// Get global frame size
	if (SUCCEEDED(hr))
	{
		// Get width
		hr = pMetadataQueryReader->GetMetadataByName(
			L"/logscrdesc/Width",
			&propValue);
		if (SUCCEEDED(hr))
		{
			hr = (propValue.vt == VT_UI2 ? S_OK : E_FAIL);
			if (SUCCEEDED(hr))
			{
				gifStruct.m_cxGifImage = propValue.uiVal;
			}
			PropVariantClear(&propValue);
		}
	}

	if (SUCCEEDED(hr))
	{
		// Get height
		hr = pMetadataQueryReader->GetMetadataByName(
			L"/logscrdesc/Height",
			&propValue);
		if (SUCCEEDED(hr))
		{
			hr = (propValue.vt == VT_UI2 ? S_OK : E_FAIL);
			if (SUCCEEDED(hr))
			{
				gifStruct.m_cyGifImage = propValue.uiVal;
			}
			PropVariantClear(&propValue);
		}
	}

	///[TW] 이제, 여기서도 CollideInfoMap이 들어갈 예정.
	CollideInfoMap::GetInstance().AddWidthHeightToGIFMap(gifIndex, gifStruct.m_cxGifImage, gifStruct.m_cyGifImage);

	if (SUCCEEDED(hr))
	{
		// Get pixel aspect ratio
		hr = pMetadataQueryReader->GetMetadataByName(
			L"/logscrdesc/PixelAspectRatio",
			&propValue);
		if (SUCCEEDED(hr))
		{
			hr = (propValue.vt == VT_UI1 ? S_OK : E_FAIL);
			if (SUCCEEDED(hr))
			{
				UINT uPixelAspRatio = propValue.bVal;

				if (uPixelAspRatio != 0)
				{
					// Need to calculate the ratio. The value in uPixelAspRatio 
					// allows specifying widest pixel 4:1 to the tallest pixel of 
					// 1:4 in increments of 1/64th
					FLOAT pixelAspRatio = (uPixelAspRatio + 15.f) / 64.f;

					// Calculate the image width and height in pixel based on the
					// pixel aspect ratio. Only shrink the image.
					if (pixelAspRatio > 1.f)
					{
						gifStruct.m_cxGifImagePixel = gifStruct.m_cxGifImage;
						gifStruct.m_cyGifImagePixel = static_cast<UINT>(gifStruct.m_cyGifImage / pixelAspRatio);
					}
					else
					{
						gifStruct.m_cxGifImagePixel = static_cast<UINT>(gifStruct.m_cxGifImage * pixelAspRatio);
						gifStruct.m_cyGifImagePixel = gifStruct.m_cyGifImage;
					}
				}
				else
				{
					// The value is 0, so its ratio is 1
					gifStruct.m_cxGifImagePixel = gifStruct.m_cxGifImage;
					gifStruct.m_cyGifImagePixel = gifStruct.m_cyGifImage;
				}
			}
			PropVariantClear(&propValue);
		}
	}

	// Get looping information
	if (SUCCEEDED(hr))
	{
		// First check to see if the application block in the Application Extension
		// contains "NETSCAPE2.0" and "ANIMEXTS1.0", which indicates the gif animation
		// has looping information associated with it.
		// 
		// If we fail to get the looping information, loop the animation infinitely.
		if (SUCCEEDED(pMetadataQueryReader->GetMetadataByName(
			L"/appext/application",
			&propValue)) &&
			propValue.vt == (VT_UI1 | VT_VECTOR) &&
			propValue.caub.cElems == 11 &&  // Length of the application block
			(!memcmp(propValue.caub.pElems, "NETSCAPE2.0", propValue.caub.cElems) ||
				!memcmp(propValue.caub.pElems, "ANIMEXTS1.0", propValue.caub.cElems)))
		{
			PropVariantClear(&propValue);

			hr = pMetadataQueryReader->GetMetadataByName(L"/appext/data", &propValue);
			if (SUCCEEDED(hr))
			{
				//  The data is in the following format:
				//  byte 0: extsize (must be > 1)
				//  byte 1: loopType (1 == animated gif)
				//  byte 2: loop count (least significant byte)
				//  byte 3: loop count (most significant byte)
				//  byte 4: set to zero
				if (propValue.vt == (VT_UI1 | VT_VECTOR) &&
					propValue.caub.cElems >= 4 &&
					propValue.caub.pElems[0] > 0 &&
					propValue.caub.pElems[1] == 1)
				{
					gifStruct.m_uTotalLoopCount = MAKEWORD(propValue.caub.pElems[2],
						propValue.caub.pElems[3]);

					// If the total loop count is not zero, we then have a loop count
					// If it is 0, then we repeat infinitely
					if (gifStruct.m_uTotalLoopCount != 0)
					{
						gifStruct.m_fHasLoop = TRUE;
					}
				}
			}
		}
	}
	PropVariantClear(&propValue);
	SafeRelease(&pMetadataQueryReader);

	//Debug::Trace("END GetGlobalMetadata: ", gifStruct.m_GIFIndex);

	return hr;
}

//백그라운드 컬러를 가져옴
HRESULT D2DEngine::GetBackgroundColor(IWICMetadataQueryReader* pMetadataQueryReader, GIFStruct& gifStruct)
{
	DWORD dwBGColor;
	BYTE backgroundIndex = 0;
	WICColor rgColors[256];
	UINT cColorsCopied = 0;
	PROPVARIANT propVariant;
	PropVariantInit(&propVariant);
	IWICPalette* pWicPalette = NULL;

	// If we have a global palette, get the palette and background color
	HRESULT hr = pMetadataQueryReader->GetMetadataByName(
		L"/logscrdesc/GlobalColorTableFlag",
		&propVariant);
	if (SUCCEEDED(hr))
	{
		hr = (propVariant.vt != VT_BOOL || !propVariant.boolVal) ? E_FAIL : S_OK;
		PropVariantClear(&propVariant);
	}

	if (SUCCEEDED(hr))
	{
		// Background color index
		hr = pMetadataQueryReader->GetMetadataByName(
			L"/logscrdesc/BackgroundColorIndex",
			&propVariant);
		if (SUCCEEDED(hr))
		{
			hr = (propVariant.vt != VT_UI1) ? E_FAIL : S_OK;
			if (SUCCEEDED(hr))
			{
				backgroundIndex = propVariant.bVal;
			}
			PropVariantClear(&propVariant);
		}
	}

	// Get the color from the palette
	if (SUCCEEDED(hr))
	{
		hr = m_pWicFactory->CreatePalette(&pWicPalette);
	}

	if (SUCCEEDED(hr))
	{
		// Get the global palette
		hr = gifStruct.m_pBitDecoder->CopyPalette(pWicPalette);
	}

	if (SUCCEEDED(hr))
	{
		hr = pWicPalette->GetColors(
			ARRAYSIZE(rgColors),
			rgColors,
			&cColorsCopied);
	}

	if (SUCCEEDED(hr))
	{
		// Check whether background color is outside range 
		hr = (backgroundIndex >= cColorsCopied) ? E_FAIL : S_OK;
	}

	if (SUCCEEDED(hr))
	{
		// Get the color in ARGB format
		dwBGColor = rgColors[backgroundIndex];

		// The background color is in ARGB format, and we want to 
		// extract the alpha value and convert it in FLOAT
		FLOAT alpha = (dwBGColor >> 24) / 255.f;
		m_backgroundColor = ColorF(dwBGColor, alpha);
	}

	SafeRelease(&pWicPalette);
	return hr;
}

//Transform에서, GIF가 출력될 수 있는 영역이 결정되어야 한다.
void D2DEngine::GetRectFromGIFIndex(D2D1_RECT_F& rect, int gifIndex, Transform* transform)
{
	//Debug::Trace("GetRectFromGIFIndex: ", gifIndex);
	float tmpWidth = CollideInfoMap::GetInstance().GetWidthByGIFIndex(gifIndex);
	float tmpHeight = CollideInfoMap::GetInstance().GetHeightByGIFIndex(gifIndex);

	Vec2 tmpPos = transform->GetPosition();

	rect = { tmpPos.x - tmpWidth / 2.0f, tmpPos.y - tmpHeight / 2.0f,
						   tmpPos.x + tmpWidth / 2.0f, tmpPos.y + tmpHeight / 2.0f };
}

void D2DEngine::GetRectFromGIFIndexWithPos(D2D1_RECT_F& rect, int gifIndex, float posX, float posY)
{
	//Debug::Trace("GetRectFromGIFIndexWithPos: ", gifIndex);
	float tmpWidth = CollideInfoMap::GetInstance().GetWidthByGIFIndex(gifIndex);
	float tmpHeight = CollideInfoMap::GetInstance().GetHeightByGIFIndex(gifIndex);

	rect = { posX - tmpWidth / 2.0f, posY - tmpHeight / 2.0f,
						   posX + tmpWidth / 2.0f, posY + tmpHeight / 2.0f };
}

//다음 프레임을 들여옴
HRESULT D2DEngine::OverlayNextFrame(GIFStruct& gifStruct)
{
	//Debug::Trace("OverlayNextFrame: ", gifStruct.m_GIFIndex);
	// Get Frame information
	HRESULT hr = GetRawFrame(gifStruct.m_uNextFrameIndex, gifStruct);
	if (SUCCEEDED(hr))
	{
		// For disposal 3 method, we would want to save a copy of the current
		// composed frame
		if (gifStruct.m_uFrameDisposal == DM_PREVIOUS)
		{
			hr = SaveComposedFrame(gifStruct);
		}
	}

	if (SUCCEEDED(hr))
	{
		// Start producing the next bitmap
		gifStruct.m_pFrameComposeRT->BeginDraw();

		// If starting a new animation loop
		if (gifStruct.m_uNextFrameIndex == 0)
		{
			// Draw background and increase loop count
			gifStruct.m_pFrameComposeRT->Clear(m_backgroundColor);
			(gifStruct.m_uLoopNumber)++;
		}

		// Produce the next frame
		gifStruct.m_pFrameComposeRT->DrawBitmap(
			gifStruct.m_pRawFrame,
			gifStruct.m_framePosition);

		hr = gifStruct.m_pFrameComposeRT->EndDraw();
	}

	// To improve performance and avoid decoding/composing this frame in the 
	// following animation loops, the composed frame can be cached here in system 
	// or video memory.

	if (SUCCEEDED(hr))
	{
		// Increase the frame index by 1
		gifStruct.m_uNextFrameIndex = (++(gifStruct.m_uNextFrameIndex)) % (gifStruct.m_cFrames);
	}

	//Debug::Trace("OverlayNextFrame: ", gifStruct.m_GIFIndex);
	return hr;
}

HRESULT D2DEngine::ComposeNextFrame(GIFStruct& gifStruct)
{
	//Debug::Trace("ComposeNextFrame: ", gifStruct.m_GIFIndex);
	HRESULT hr = S_OK;

	// Check to see if the render targets are initialized
	if (m_pRenderTarget && gifStruct.m_pFrameComposeRT)
	{
		// First, kill the timer since the delay is no longer valid
		KillTimer(m_hWnd, DELAY_TIMER_ID);

		// Compose one frame
		hr = DisposeCurrentFrame(gifStruct);
		if (SUCCEEDED(hr))
		{
			hr = OverlayNextFrame(gifStruct);
		}

		// Keep composing frames until we see a frame with delay greater than
		// 0 (0 delay frames are the invisible intermediate frames), or until
		// we have reached the very last frame.
		while (SUCCEEDED(hr) && (gifStruct.m_uFrameDelay) == 0 && !IsLastFrame(gifStruct))
		{
			hr = DisposeCurrentFrame(gifStruct);
			if (SUCCEEDED(hr))
			{
				hr = OverlayNextFrame(gifStruct);
			}
		}

		// If we have more frames to play, set the timer according to the delay.
		// Set the timer regardless of whether we succeeded in composing a frame
		// to try our best to continue displaying the animation.
		if (!EndOfAnimation(gifStruct) && (gifStruct.m_cFrames) > 1)
		{
			// Set the timer according to the delay
			SetTimer(m_hWnd, DELAY_TIMER_ID, gifStruct.m_uFrameDelay, NULL);
		}
	}
	//Debug::Trace("END ComposeNextFrame: ", gifStruct.m_GIFIndex);

	return hr;
}

//프레임 움직임 작업을 해주는 경우
HRESULT D2DEngine::DisposeCurrentFrame(GIFStruct& gifStruct)
{
	//Debug::Trace("DisposeCurrentFrame: ", gifStruct.m_GIFIndex);
	HRESULT hr = S_OK;

	switch (gifStruct.m_uFrameDisposal)
	{
	case DM_UNDEFINED:
	case DM_NONE:
		// We simply draw on the previous frames. Do nothing here.
		break;
	case DM_BACKGROUND:
		// Dispose background
		// Clear the area covered by the current raw frame with background color
		hr = ClearCurrentFrameArea(gifStruct);
		break;
	case DM_PREVIOUS:
		// Dispose previous
		// We restore the previous composed frame first
		hr = RestoreSavedFrame(gifStruct);
		break;
	default:
		// Invalid disposal method
		hr = E_FAIL;
	}
	//Debug::Trace("END DisposeCurrentFrame: ", gifStruct.m_GIFIndex);
	return hr;
}

//오류 시 저장되었던 프레임 복구
HRESULT D2DEngine::RestoreSavedFrame(GIFStruct& gifStruct)
{
	//Debug::Trace("RestoreSavedFrame: ", gifStruct.m_GIFIndex);
	HRESULT hr = S_OK;

	ID2D1Bitmap* pFrameToCopyTo = NULL;

	hr = (gifStruct.m_pSavedFrame) ? S_OK : E_FAIL;

	if (SUCCEEDED(hr))
	{
		hr = gifStruct.m_pFrameComposeRT->GetBitmap(&pFrameToCopyTo);
	}

	if (SUCCEEDED(hr))
	{
		// Copy the whole bitmap
		hr = pFrameToCopyTo->CopyFromBitmap(NULL, gifStruct.m_pSavedFrame, NULL);
	}

	SafeRelease(&pFrameToCopyTo);
	//Debug::Trace("END RestoreSavedFrame: ", gifStruct.m_GIFIndex);
	return hr;
}

//GIF 내부, 현상태 저장.
HRESULT D2DEngine::SaveComposedFrame(GIFStruct& gifStruct)
{
	//Debug::Trace("SaveComposedFrame: ", gifStruct.m_GIFIndex);
	HRESULT hr = S_OK;

	ID2D1Bitmap* pFrameToBeSaved = NULL;

	hr = gifStruct.m_pFrameComposeRT->GetBitmap(&pFrameToBeSaved);
	if (SUCCEEDED(hr))
	{
		// Create the temporary bitmap if it hasn't been created yet 
		if (gifStruct.m_pSavedFrame == NULL)
		{
			D2D1_SIZE_U bitmapSize = pFrameToBeSaved->GetPixelSize();
			D2D1_BITMAP_PROPERTIES bitmapProp;
			pFrameToBeSaved->GetDpi(&bitmapProp.dpiX, &bitmapProp.dpiY);
			bitmapProp.pixelFormat = pFrameToBeSaved->GetPixelFormat();

			hr = gifStruct.m_pFrameComposeRT->CreateBitmap(
				bitmapSize,
				bitmapProp,
				&(gifStruct.m_pSavedFrame));
		}
	}

	if (SUCCEEDED(hr))
	{
		// Copy the whole bitmap
		hr = (gifStruct.m_pSavedFrame)->CopyFromBitmap(NULL, pFrameToBeSaved, NULL);
	}

	SafeRelease(&pFrameToBeSaved);
	//Debug::Trace("END SaveComposedFrame: ", gifStruct.m_GIFIndex);
	return hr;
}

//그대로 써도 됨, 현재 GIF가 출력되는 영역을 정리하는 함수.
HRESULT D2DEngine::ClearCurrentFrameArea(GIFStruct& gifStruct)
{
	//Debug::Trace("ClearCurrentFrameArea: ", gifStruct.m_GIFIndex);
	gifStruct.m_pFrameComposeRT->BeginDraw();

	// Clip the render target to the size of the raw frame
	gifStruct.m_pFrameComposeRT->PushAxisAlignedClip(
		&(gifStruct.m_framePosition),
		D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);

	gifStruct.m_pFrameComposeRT->Clear(m_backgroundColor);

	// Remove the clipping
	gifStruct.m_pFrameComposeRT->PopAxisAlignedClip();

	//Debug::Trace("END ClearCurrentFrameArea: ", gifStruct.m_GIFIndex);

	return gifStruct.m_pFrameComposeRT->EndDraw();
}

HRESULT D2DEngine::RecreateBitmapRT(GIFStruct& gifStruct)
{
	//Debug::Trace("RecreateBitmapRT: ", gifStruct.m_GIFIndex);
	HRESULT hr = S_OK;
	if (m_pRenderTarget != nullptr)
	{
		SafeReleaseGIF(gifStruct.m_pFrameComposeRT);
		hr = m_pRenderTarget->CreateCompatibleRenderTarget(
			D2D1::SizeF(
				static_cast<FLOAT>(gifStruct.m_cxGifImage),
				static_cast<FLOAT>(gifStruct.m_cyGifImage)),
			&(gifStruct.m_pFrameComposeRT));
	}

	//Debug::Trace("END RecreateBitmapRT: ", gifStruct.m_GIFIndex);
	return hr;
}

//마지막 프레임인지 확인해줌.
BOOL D2DEngine::IsLastFrame(GIFStruct& gifStruct)
{
	//Debug::Trace("IsLastFrame: ", gifStruct.m_GIFIndex);
	return (gifStruct.m_uNextFrameIndex == 0);
}

//Animation이 끝났는지 확인해줌.
BOOL D2DEngine::EndOfAnimation(GIFStruct& gifStruct)
{
	//Debug::Trace("EndOfAnimation: ", gifStruct.m_GIFIndex);
	return (gifStruct.m_fHasLoop) && IsLastFrame(gifStruct) && (gifStruct.m_uLoopNumber) == (gifStruct.m_uTotalLoopCount + 1);
}

///[TW] Note-To-Self.
/// 1. Bitmap Render Target, 프레임을 GIF에서 만들기 위해 활용.
/// Resize 안됨, 항상 다시 만들어야 한다.

#pragma endregion
#pragma region Etc
HRESULT D2DEngine::LoadBitmapFromFile(ID2D1RenderTarget* pRenderTarget, IWICImagingFactory* pIWICFactory, PCWSTR uri, UINT destinationWidth, UINT destinationHeight, ID2D1Bitmap** ppBitmap)
{
	HRESULT hr = S_OK;

	IWICBitmapDecoder* pDecoder = NULL;
	IWICBitmapFrameDecode* pSource = NULL;
	IWICStream* pStream = NULL;
	IWICFormatConverter* pConverter = NULL;
	IWICBitmapScaler* pScaler = NULL;

	hr = pIWICFactory->CreateDecoderFromFilename(
		uri,
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&pDecoder
	);
	if (SUCCEEDED(hr))
	{

		// Create the initial frame.
		hr = pDecoder->GetFrame(0, &pSource);
	}

	if (SUCCEEDED(hr))
	{
		// Convert the image format to 32bppPBGRA
		// (DXGI_FORMAT_B8G8R8A8_UNORM + D2D1_ALPHA_MODE_PREMULTIPLIED).
		hr = pIWICFactory->CreateFormatConverter(&pConverter);
	}
	if (SUCCEEDED(hr))
	{
		// If a new width or height was specified, create an
		// IWICBitmapScaler and use it to resize the image.
		if (destinationWidth != 0 || destinationHeight != 0)
		{
			UINT originalWidth, originalHeight;
			hr = pSource->GetSize(&originalWidth, &originalHeight);
			if (SUCCEEDED(hr))
			{
				if (destinationWidth == 0)
				{
					FLOAT scalar = static_cast<FLOAT>(destinationHeight) / static_cast<FLOAT>(originalHeight);
					destinationWidth = static_cast<UINT>(scalar * static_cast<FLOAT>(originalWidth));
				}
				else if (destinationHeight == 0)
				{
					FLOAT scalar = static_cast<FLOAT>(destinationWidth) / static_cast<FLOAT>(originalWidth);
					destinationHeight = static_cast<UINT>(scalar * static_cast<FLOAT>(originalHeight));
				}

				hr = pIWICFactory->CreateBitmapScaler(&pScaler);
				if (SUCCEEDED(hr))
				{
					hr = pScaler->Initialize(
						pSource,
						destinationWidth,
						destinationHeight,
						WICBitmapInterpolationModeCubic
					);
				}
				if (SUCCEEDED(hr))
				{
					hr = pConverter->Initialize(
						pScaler,
						GUID_WICPixelFormat32bppPBGRA,
						WICBitmapDitherTypeNone,
						NULL,
						0.f,
						WICBitmapPaletteTypeMedianCut
					);
				}
			}
		}
		else // Don't scale the image.
		{
			hr = pConverter->Initialize(
				pSource,
				GUID_WICPixelFormat32bppPBGRA,
				WICBitmapDitherTypeNone,
				NULL,
				0.f,
				WICBitmapPaletteTypeMedianCut
			);
		}
	}
	if (SUCCEEDED(hr))
	{
		// Create a Direct2D bitmap from the WIC bitmap.
		hr = pRenderTarget->CreateBitmapFromWicBitmap(
			pConverter,
			NULL,
			ppBitmap
		);
	}

	SafeRelease(&pDecoder);
	SafeRelease(&pSource);
	SafeRelease(&pStream);
	SafeRelease(&pConverter);
	SafeRelease(&pScaler);

	return hr;
}

wchar_t* D2DEngine::ConvertCStoWCS(const char* orig)
{
	size_t newsize = strlen(orig) + 1;
	wchar_t* wcstring = new wchar_t[newsize];

	// Convert char* string to a wchar_t* string.
	size_t convertedChars = 0;
	mbstowcs_s(&convertedChars, wcstring, newsize, orig, _TRUNCATE);

	return wcstring;
}
#pragma endregion

//void D2DEngine::DrawDebugBox(const Vec2Rect& tmpRect, eDebugBrush brushType)
//{
//	ID2D1SolidColorBrush* brush;
//
//	if (brushType == eDebugBrush::EDB_RED)
//	{
//		brush = m_pRedBrush;
//	}
//	else if (brushType == eDebugBrush::EDB_GREEN)
//	{
//		brush = m_pGreenBrush;
//	}
//
//	//시작지점 x,y를 받아서 하나의 포인트로 묶음
//	D2D1_POINT_2F tmpPoint;
//	D2D1_POINT_2F tmpPoint2;
//
//	tmpPoint.x = tmpRect.topLeft.x;
//	tmpPoint.y = tmpRect.topLeft.y;
//
//	tmpPoint2.x = tmpRect.topRight.x;
//	tmpPoint2.y = tmpRect.topRight.y;
//
//	m_pRenderTarget->DrawLine(tmpPoint, tmpPoint2, brush);
//
//	tmpPoint.x = tmpRect.topRight.x;
//	tmpPoint.y = tmpRect.topRight.y;
//
//	tmpPoint2.x = tmpRect.bottomRight.x;
//	tmpPoint2.y = tmpRect.bottomRight.y;
//
//	m_pRenderTarget->DrawLine(tmpPoint, tmpPoint2, brush);
//
//	tmpPoint.x = tmpRect.bottomRight.x;
//	tmpPoint.y = tmpRect.bottomRight.y;
//
//	tmpPoint2.x = tmpRect.bottomLeft.x;
//	tmpPoint2.y = tmpRect.bottomLeft.y;
//
//	m_pRenderTarget->DrawLine(tmpPoint, tmpPoint2, brush);
//
//	tmpPoint.x = tmpRect.bottomLeft.x;
//	tmpPoint.y = tmpRect.bottomLeft.y;
//
//	tmpPoint2.x = tmpRect.topLeft.x;
//	tmpPoint2.y = tmpRect.topLeft.y;
//
//	m_pRenderTarget->DrawLine(tmpPoint, tmpPoint2, brush);
//}


//HRESULT D2DEngine::LoadResourceBitmap(ID2D1RenderTarget* pRenderTarget, IWICImagingFactory* pIWICFactory, PCWSTR resourceName, PCWSTR resourceType, UINT destinationWidth, UINT destinationHeight, ID2D1Bitmap** ppBitmap)
//{
//	HRESULT hr = S_OK;
//	IWICBitmapDecoder* pDecoder = NULL;
//	IWICBitmapFrameDecode* pSource = NULL;
//	IWICStream* pStream = NULL;
//	IWICFormatConverter* pConverter = NULL;
//	IWICBitmapScaler* pScaler = NULL;
//
//	HRSRC imageResHandle = NULL;
//	HGLOBAL imageResDataHandle = NULL;
//	void* pImageFile = NULL;
//	DWORD imageFileSize = 0;
//
//	// Locate the resource.
//	imageResHandle = FindResourceW(HINST_THISCOMPONENT, resourceName, resourceType);
//
//	hr = imageResHandle ? S_OK : E_FAIL;
//	if (SUCCEEDED(hr))
//	{
//		// Load the resource.
//		imageResDataHandle = LoadResource(HINST_THISCOMPONENT, imageResHandle);
//
//		hr = imageResDataHandle ? S_OK : E_FAIL;
//	}
//	if (SUCCEEDED(hr))
//	{
//		// Lock it to get a system memory pointer.
//		pImageFile = LockResource(imageResDataHandle);
//
//		hr = pImageFile ? S_OK : E_FAIL;
//	}
//	if (SUCCEEDED(hr))
//	{
//		// Calculate the size.
//		imageFileSize = SizeofResource(HINST_THISCOMPONENT, imageResHandle);
//
//		hr = imageFileSize ? S_OK : E_FAIL;
//	}
//	if (SUCCEEDED(hr))
//	{
//		// Create a WIC stream to map onto the memory.
//		hr = pIWICFactory->CreateStream(&pStream);
//	}
//	if (SUCCEEDED(hr))
//	{
//		// Initialize the stream with the memory pointer and size.
//		hr = pStream->InitializeFromMemory(
//			reinterpret_cast<BYTE*>(pImageFile),
//			imageFileSize
//		);
//	}
//	if (SUCCEEDED(hr))
//	{
//		// Create a decoder for the stream.
//		hr = pIWICFactory->CreateDecoderFromStream(
//			pStream,
//			NULL,
//			WICDecodeMetadataCacheOnLoad,
//			&pDecoder
//		);
//	}
//	if (SUCCEEDED(hr))
//	{
//		// Create the initial frame.
//		hr = pDecoder->GetFrame(0, &pSource);
//	}
//	if (SUCCEEDED(hr))
//	{
//		// Convert the image format to 32bppPBGRA
//		// (DXGI_FORMAT_B8G8R8A8_UNORM + D2D1_ALPHA_MODE_PREMULTIPLIED).
//		hr = pIWICFactory->CreateFormatConverter(&pConverter);
//	}
//	if (SUCCEEDED(hr))
//	{
//		// If a new width or height was specified, create an
//		// IWICBitmapScaler and use it to resize the image.
//		if (destinationWidth != 0 || destinationHeight != 0)
//		{
//			UINT originalWidth, originalHeight;
//			hr = pSource->GetSize(&originalWidth, &originalHeight);
//			if (SUCCEEDED(hr))
//			{
//				if (destinationWidth == 0)
//				{
//					FLOAT scalar = static_cast<FLOAT>(destinationHeight) / static_cast<FLOAT>(originalHeight);
//					destinationWidth = static_cast<UINT>(scalar * static_cast<FLOAT>(originalWidth));
//				}
//				else if (destinationHeight == 0)
//				{
//					FLOAT scalar = static_cast<FLOAT>(destinationWidth) / static_cast<FLOAT>(originalWidth);
//					destinationHeight = static_cast<UINT>(scalar * static_cast<FLOAT>(originalHeight));
//				}
//
//				hr = pIWICFactory->CreateBitmapScaler(&pScaler);
//				if (SUCCEEDED(hr))
//				{
//					hr = pScaler->Initialize(
//						pSource,
//						destinationWidth,
//						destinationHeight,
//						WICBitmapInterpolationModeCubic
//					);
//					if (SUCCEEDED(hr))
//					{
//						hr = pConverter->Initialize(
//							pScaler,
//							GUID_WICPixelFormat32bppPBGRA,
//							WICBitmapDitherTypeNone,
//							NULL,
//							0.f,
//							WICBitmapPaletteTypeMedianCut
//						);
//					}
//				}
//			}
//		}
//		else
//		{
//			hr = pConverter->Initialize(
//				pSource,
//				GUID_WICPixelFormat32bppPBGRA,
//				WICBitmapDitherTypeNone,
//				NULL,
//				0.f,
//				WICBitmapPaletteTypeMedianCut
//			);
//		}
//	}
//	if (SUCCEEDED(hr))
//	{
//		//create a Direct2D bitmap from the WIC bitmap.
//		hr = pRenderTarget->CreateBitmapFromWicBitmap(
//			pConverter,
//			NULL,
//			ppBitmap
//		);
//	}
//
//	SafeRelease(&pDecoder);
//	SafeRelease(&pSource);
//	SafeRelease(&pStream);
//	SafeRelease(&pConverter);
//	SafeRelease(&pScaler);
//
//	return hr;
//}


