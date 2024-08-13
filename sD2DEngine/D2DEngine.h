#pragma once			// 컴파일러에게 한번만 컴파일하라고 알려준다.
#include "Syn.h"
#include "D2DSprite.h"

//[TW] GIF 출력 위한 GIFStruct
#include "GIFStruct.h"

//RenderGIF를 위한 추가, 상호 종속 아님.
#include "../SuperNova/Vec2.h"
#include "../SuperNova/Transform.h"
#include "../SuperNova/EnumDefine.h"
#include "../SuperNova/StructDefine.h"

// 자주 쓰는 네임스페이스니까 네임스페이스 사용
using namespace D2D1;

class Transform; //[TW] Transform 활용 렌더 위해서 D2D 함수 오버로드할 것.

/// <summary>
/// 23.02.02
/// 윤제의 sD2D엔진 헤더파일
/// 쓰다듬어 주는중
/// 
/// 23.02.06
/// 선과 네모,원 출력
/// 하나의 헤더에 D2D헤더들 과 매크로를 넣어놈
/// </summary>
class D2DEngine
{
public:
	D2DEngine();	// 생성자
	~D2DEngine();	// 소멸자

	void Initalize(HINSTANCE hInstance, HWND hWnd);		// 초기화
	void Finalize();	// 종료

	void BeginRender(ColorF bgcolor);	// 그리기 시작
	void EndRender();	// 그리기 끝

	///그리기 관련
	void DrawLine(float sposx, float sposy, float dposx, float dposy);
	//void DrawDebugBox(const Vec2Rect& tmpRect, eDebugBrush brushType);//디버그를 위해.
	void DrawRect(float cposx, float cposy, float width, float height);
	void DrawFillRectangle();
	void DrawCircle(float cPosx, float cPosy, float scale);

	void InfoText(Vec2 writePos, std::wstring str);	//텍스트 출력

	//콜라이더 디버깅용.
	void DrawDebugLine(const Vec2& startPos, const Vec2& endPos, eDebugBrush debugBrushType);
	void DrawDebugRect(const Vec2Rect& rect, eDebugBrush debugBrushType);
	void DrawDebugCircle(const Vec2Circle& circle, eDebugBrush debugBrushType);

	///PNG이미지
	// 스프라이트 출력
	// 원본 위치 등의 정보는 엔진별 구현이며 숨겨져 있다.
	void DrawSprite(int spriteIndex, int dstX, int dstY);
	void DrawSprite(int spriteIndex, int dstX, int dstY, Transform* transform); //[TW] Transform Render
	//void DrawSprite(DRSprite* sprite, int dstX, int dstY);

	///GIF
	void DrawGIF(int gifIndex, Transform* transform);
	void DrawGIFByStruct(GIFStruct& gifStruct, Transform* transform);
	void DrawGIFWithPos(int gifIndex, float posX, float posY, Transform* transform);	//[TW] Transform의 Position을 무시하고 따로 들어온 위치대로 출력.
	void DrawGIFByStruct_Pos(GIFStruct& gifStruct, float posX, float posY, Transform* transform);

private:
	HWND m_hWnd;	// 윈도우 정의
	HRESULT m_hResult;

	RECT m_ScreenRect;	 // 화면 크기 받기
	D2D1_COLOR_F m_backgroundColor; 

	ID2D1Factory* m_pFactory;			// 팩토리 생성
	IDWriteFactory* m_pDWriteFactory;	// 텍스트 출력
	IWICImagingFactory* m_pWicFactory;	// WIC 관련 Factory 객체

	ID2D1HwndRenderTarget* m_pRenderTarget;	// 랜더 타겟 생성
	ID2D1RenderTarget* m_pImgRenderTarget;	// 이미지 랜더 타겟
	ID2D1DCRenderTarget* m_pDCRenderTarget;	// gif 를 위한 랜더타겟

	/// 기본 브러쉬들 색깔 설정
	ID2D1SolidColorBrush* m_pTempBrush;		// 그리는 함수 내에서 쓸 브러쉬
	ID2D1SolidColorBrush* m_pNowBrush;		// 재사용하기 위한 브러쉬
	ID2D1SolidColorBrush* m_pRedBrush;
	ID2D1SolidColorBrush* m_pGreenBrush;
	ID2D1SolidColorBrush* m_pBlueBrush;
	ID2D1SolidColorBrush* m_pWhiteBrush;
	ID2D1SolidColorBrush* m_pBlackBrush;

	/// 텍스트를 출력하기 위한 팩토리
	IDWriteTextFormat* m_pTextFormat;

	HRESULT CreateDeviceResources();			// MS 도큐먼트에있는 팩토리 초기화용 함수
	void CreateBrush();							// 색칠놀이
	wchar_t* ConvertCStoWCS(const char* orig);	

private:
	/// 스프라이트 관련
	int m_SpriteCount;			// 스프라이트의 갯수 (인덱스는 0부터)
	int m_SpriteSheetCount;		// 스프라이트 시트의 갯수 (인덱스는 0부터)

	std::vector<DRSprite*> m_SpritePool;
	std::vector<D2DSprite*> m_SpriteInfos;		// 스프라이트의 정보. 시트 로드 방식이라면 한 개의 클래스로 될 것도 같다. 스프라이트 클래스조차 상속받아서 2개의 구현으로 가는 이유는, 실제로 비트맵을 읽어서 스프라이트 클래스 내부에 내장하는 경우 때문이다.

	std::map<int, ID2D1Bitmap*> m_SpriteSheets;	// 스프라이트 시트

	void LoadImageResources();	// map vector에 넣는 함수
	
	int LoadSpriteSheet(const char* filePath);	// 파일가져오는 함수
	DRSprite* LoadSpriteFromSheet(int sheetIndex, int oriX, int oriY, int width, int height, int delayFrame);

	/// 페이드인 페이드 아웃
	float m_FadeinDuration = 2.0f;
	float m_FrameTime = 1.0f / 60.0f;
	float opacity = 0.0f;
	float timeElapsed = 0.0f;


private:
	//비트맵 렌더 타겟은 GIF을 위해 반드시 필요,
	//다만, 매 순간마다 다시 만들어줘야 한다. (저장 불가.)

	// gif출력을 위한 멤버변수칸
	// gif 출력을 위한 비트 디코더, 하나만 있으면 됨
	
	std::map<int, GIFStruct*> m_GIFSheets;	//GIF

	//HRESULT LoadResourceBitmap(
	//	ID2D1RenderTarget* pRenderTarget,
	//	IWICImagingFactory* pIWICFactory,
	//	PCWSTR resourceName,
	//	PCWSTR resourceType,
	//	UINT destinationWidth,
	//	UINT destinationHeight,
	//	ID2D1Bitmap** ppBitmap
	//);

	HRESULT LoadBitmapFromFile(
		ID2D1RenderTarget* pRenderTarget,
		IWICImagingFactory* pIWICFactory,
		PCWSTR uri,
		UINT destinationWidth,
		UINT destinationHeight,
		ID2D1Bitmap** ppBitmap
	);

	void LoadGIFResources();	// map vector에 넣는 함수

	void LoadGIF(std::wstring filePath);

	/// GIF 이미지
	HRESULT MakeGIF(std::wstring filePath, GIFStruct& gifStruct, int gifIndex);

	HRESULT GetRawFrame(UINT uFrameIndex, GIFStruct& gifStruct);
	HRESULT GetGlobalMetadata(GIFStruct& gifStruct, int gifIndex);
	HRESULT GetBackgroundColor(IWICMetadataQueryReader* pMetadataQueryReader, GIFStruct& gifStruct);

	void GetRectFromGIFIndex(D2D1_RECT_F& rect, int gifIndex, Transform* transform);
	void GetRectFromGIFIndexWithPos(D2D1_RECT_F& rect, int gifIndex, float posX, float posY);

	HRESULT OverlayNextFrame(GIFStruct& gifStruct);
	HRESULT ComposeNextFrame(GIFStruct& gifStruct);
	HRESULT DisposeCurrentFrame(GIFStruct& gifStruct);
	HRESULT RestoreSavedFrame(GIFStruct& gifStruct);
	HRESULT SaveComposedFrame(GIFStruct& gifStruct);
	HRESULT ClearCurrentFrameArea(GIFStruct& gifStruct);

	HRESULT RecreateBitmapRT(GIFStruct& gifStruct);
	BOOL IsLastFrame(GIFStruct& gifStruct);
	BOOL EndOfAnimation(GIFStruct& gifStruct);	
};
