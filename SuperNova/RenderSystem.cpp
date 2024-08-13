#include "RenderSystem.h"
#include "D2DEngine.h"
#include "Syn.h"
#include "Transform.h"
#include "Debug.h"
using namespace std;

void RenderSystem::DrawLine(float sposx, float sposy, float dposx, float dposy)
{
	m_pRenderEngine->DrawLine(sposx, sposy, dposx, dposy);
}

void RenderSystem::DrawRect(float cposx, float cposy, float width, float height)
{
	m_pRenderEngine->DrawRect(cposx, cposy, width, height);
}

void RenderSystem::DrawCircle(float cPosx, float cPosy, float scale)
{
	m_pRenderEngine->DrawCircle(cPosx, cPosy, scale);
}

void RenderSystem::Fadein()
{
	m_pRenderEngine->DrawFillRectangle();
}

//void RenderSystem::DrawDebugBox(const Vec2Rect& tmpRect, eDebugBrush brushType)
//{
//	m_pRenderEngine->DrawDebugBox(tmpRect, brushType);
//}

void RenderSystem::InfoText(Vec2 writePos, wstring str)
{
	m_pRenderEngine->InfoText(writePos, str);
}

void RenderSystem::DrawSprite(int spriteIndex, int dstX, int dstY) ///[TW] Deprecated
{
	m_pRenderEngine->DrawSprite(spriteIndex, dstX, dstY);
}

/// 이 함수를 써야 앞으로 오류가 나지 않는다. (SetTransform) 반영.
void RenderSystem::DrawSprite(int spriteIndex, int dstX, int dstY, Transform* transform)
{
	m_pRenderEngine->DrawSprite(spriteIndex, dstX, dstY, transform);
}

//GIF 출력용 함수.
void RenderSystem::DrawGIF(int gifIndex, Transform* transform)
{
	m_pRenderEngine->DrawGIF(gifIndex, transform);
}

void RenderSystem::DrawGIFWithPos(int gifIndex, float posX, float posY, Transform* transform)
{
	m_pRenderEngine->DrawGIFWithPos(gifIndex, posX, posY, transform);
}

void RenderSystem::BeginRender()
{
	m_pRenderEngine->BeginRender(D2D1::ColorF(1, 0, 1, 0));
}

void RenderSystem::EndRender()
{
	m_pRenderEngine->EndRender();
}


void RenderSystem::DrawDebugLine(const Vec2& startPos, const Vec2& endPos, eDebugBrush debugBrushType)
{
	if (Debug::GetCanDebug())
	{
		m_pRenderEngine->DrawDebugLine(startPos, endPos, debugBrushType);
	}
}

void RenderSystem::DrawDebugRect(const Vec2Rect& rect, eDebugBrush debugBrushType)
{
	if (Debug::GetCanDebug())
	{
		m_pRenderEngine->DrawDebugRect(rect, debugBrushType);
	}
}

void RenderSystem::DrawDebugCircle(const Vec2Circle& circle, eDebugBrush debugBrushType)
{
	if (Debug::GetCanDebug())
	{
		m_pRenderEngine->DrawDebugCircle(circle, debugBrushType);
	}
}

//Scene단위에서 이를 호출 현재 하고 있음 [TW]


