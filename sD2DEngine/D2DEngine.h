#pragma once			// �����Ϸ����� �ѹ��� �������϶�� �˷��ش�.
#include "Syn.h"
#include "D2DSprite.h"

//[TW] GIF ��� ���� GIFStruct
#include "GIFStruct.h"

//RenderGIF�� ���� �߰�, ��ȣ ���� �ƴ�.
#include "../SuperNova/Vec2.h"
#include "../SuperNova/Transform.h"
#include "../SuperNova/EnumDefine.h"
#include "../SuperNova/StructDefine.h"

// ���� ���� ���ӽ����̽��ϱ� ���ӽ����̽� ���
using namespace D2D1;

class Transform; //[TW] Transform Ȱ�� ���� ���ؼ� D2D �Լ� �����ε��� ��.

/// <summary>
/// 23.02.02
/// ������ sD2D���� �������
/// ���ٵ�� �ִ���
/// 
/// 23.02.06
/// ���� �׸�,�� ���
/// �ϳ��� ����� D2D����� �� ��ũ�θ� �־��
/// </summary>
class D2DEngine
{
public:
	D2DEngine();	// ������
	~D2DEngine();	// �Ҹ���

	void Initalize(HINSTANCE hInstance, HWND hWnd);		// �ʱ�ȭ
	void Finalize();	// ����

	void BeginRender(ColorF bgcolor);	// �׸��� ����
	void EndRender();	// �׸��� ��

	///�׸��� ����
	void DrawLine(float sposx, float sposy, float dposx, float dposy);
	//void DrawDebugBox(const Vec2Rect& tmpRect, eDebugBrush brushType);//����׸� ����.
	void DrawRect(float cposx, float cposy, float width, float height);
	void DrawFillRectangle();
	void DrawCircle(float cPosx, float cPosy, float scale);

	void InfoText(Vec2 writePos, std::wstring str);	//�ؽ�Ʈ ���

	//�ݶ��̴� ������.
	void DrawDebugLine(const Vec2& startPos, const Vec2& endPos, eDebugBrush debugBrushType);
	void DrawDebugRect(const Vec2Rect& rect, eDebugBrush debugBrushType);
	void DrawDebugCircle(const Vec2Circle& circle, eDebugBrush debugBrushType);

	///PNG�̹���
	// ��������Ʈ ���
	// ���� ��ġ ���� ������ ������ �����̸� ������ �ִ�.
	void DrawSprite(int spriteIndex, int dstX, int dstY);
	void DrawSprite(int spriteIndex, int dstX, int dstY, Transform* transform); //[TW] Transform Render
	//void DrawSprite(DRSprite* sprite, int dstX, int dstY);

	///GIF
	void DrawGIF(int gifIndex, Transform* transform);
	void DrawGIFByStruct(GIFStruct& gifStruct, Transform* transform);
	void DrawGIFWithPos(int gifIndex, float posX, float posY, Transform* transform);	//[TW] Transform�� Position�� �����ϰ� ���� ���� ��ġ��� ���.
	void DrawGIFByStruct_Pos(GIFStruct& gifStruct, float posX, float posY, Transform* transform);

private:
	HWND m_hWnd;	// ������ ����
	HRESULT m_hResult;

	RECT m_ScreenRect;	 // ȭ�� ũ�� �ޱ�
	D2D1_COLOR_F m_backgroundColor; 

	ID2D1Factory* m_pFactory;			// ���丮 ����
	IDWriteFactory* m_pDWriteFactory;	// �ؽ�Ʈ ���
	IWICImagingFactory* m_pWicFactory;	// WIC ���� Factory ��ü

	ID2D1HwndRenderTarget* m_pRenderTarget;	// ���� Ÿ�� ����
	ID2D1RenderTarget* m_pImgRenderTarget;	// �̹��� ���� Ÿ��
	ID2D1DCRenderTarget* m_pDCRenderTarget;	// gif �� ���� ����Ÿ��

	/// �⺻ �귯���� ���� ����
	ID2D1SolidColorBrush* m_pTempBrush;		// �׸��� �Լ� ������ �� �귯��
	ID2D1SolidColorBrush* m_pNowBrush;		// �����ϱ� ���� �귯��
	ID2D1SolidColorBrush* m_pRedBrush;
	ID2D1SolidColorBrush* m_pGreenBrush;
	ID2D1SolidColorBrush* m_pBlueBrush;
	ID2D1SolidColorBrush* m_pWhiteBrush;
	ID2D1SolidColorBrush* m_pBlackBrush;

	/// �ؽ�Ʈ�� ����ϱ� ���� ���丮
	IDWriteTextFormat* m_pTextFormat;

	HRESULT CreateDeviceResources();			// MS ��ť��Ʈ���ִ� ���丮 �ʱ�ȭ�� �Լ�
	void CreateBrush();							// ��ĥ����
	wchar_t* ConvertCStoWCS(const char* orig);	

private:
	/// ��������Ʈ ����
	int m_SpriteCount;			// ��������Ʈ�� ���� (�ε����� 0����)
	int m_SpriteSheetCount;		// ��������Ʈ ��Ʈ�� ���� (�ε����� 0����)

	std::vector<DRSprite*> m_SpritePool;
	std::vector<D2DSprite*> m_SpriteInfos;		// ��������Ʈ�� ����. ��Ʈ �ε� ����̶�� �� ���� Ŭ������ �� �͵� ����. ��������Ʈ Ŭ�������� ��ӹ޾Ƽ� 2���� �������� ���� ������, ������ ��Ʈ���� �о ��������Ʈ Ŭ���� ���ο� �����ϴ� ��� �����̴�.

	std::map<int, ID2D1Bitmap*> m_SpriteSheets;	// ��������Ʈ ��Ʈ

	void LoadImageResources();	// map vector�� �ִ� �Լ�
	
	int LoadSpriteSheet(const char* filePath);	// ���ϰ������� �Լ�
	DRSprite* LoadSpriteFromSheet(int sheetIndex, int oriX, int oriY, int width, int height, int delayFrame);

	/// ���̵��� ���̵� �ƿ�
	float m_FadeinDuration = 2.0f;
	float m_FrameTime = 1.0f / 60.0f;
	float opacity = 0.0f;
	float timeElapsed = 0.0f;


private:
	//��Ʈ�� ���� Ÿ���� GIF�� ���� �ݵ�� �ʿ�,
	//�ٸ�, �� �������� �ٽ� �������� �Ѵ�. (���� �Ұ�.)

	// gif����� ���� �������ĭ
	// gif ����� ���� ��Ʈ ���ڴ�, �ϳ��� ������ ��
	
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

	void LoadGIFResources();	// map vector�� �ִ� �Լ�

	void LoadGIF(std::wstring filePath);

	/// GIF �̹���
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
