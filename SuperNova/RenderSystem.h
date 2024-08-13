#pragma once
#include <string>
#include "StructDefine.h"
#include "EnumDefine.h"
//#include <windows.h>

class DRSprite;
class D2DEngine;
class Transform;

class RenderSystem
{
public:
	static RenderSystem& GetInstance()
	{
		static RenderSystem inst;
		return inst;
	}

	void SetEnginePointer(D2DEngine* pEngine)
	{
		m_pRenderEngine = pEngine;
	}

	void DrawLine(float sposx, float sposy, float dposx, float dposy);
	void DrawRect(float cposx, float cposy, float width, float height);
	void DrawCircle(float cPosx, float cPosy, float scale);

	void Fadein();
	//void DrawDebugBox(const Vec2Rect& tmpRect, eDebugBrush brushType);
	void InfoText(Vec2 writePos, std::wstring str);

	void DrawSprite(int spriteIndex, int dstX, int dstY);	// Rotation,Scale이 필요 없는 sprite를 위해
	void DrawSprite(int spriteIndex, int dstX, int dstY, Transform* transform); //Transform
	void DrawGIF(int gifIndex, Transform* transform); //GIF를 그리기 위해.
	void DrawGIFWithPos(int gifIndex, float posX, float posY, Transform* transform); //GIF를 그리기 위해.

	void BeginRender();
	void EndRender();

	//디버깅용 함수
	void DrawDebugLine(const Vec2& startPos, const Vec2& endPos, eDebugBrush debugBrushType);
	void DrawDebugRect(const Vec2Rect& rect, eDebugBrush debugBrushType);
	void DrawDebugCircle(const Vec2Circle& circle, eDebugBrush debugBrushType);

	// HWND* m_phWnd;
private:

	D2DEngine* m_pRenderEngine;

};

