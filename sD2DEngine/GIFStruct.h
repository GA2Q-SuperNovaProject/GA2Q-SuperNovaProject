#pragma once
#include "Syn.h"

struct GIFStruct
{
	UINT    m_uNextFrameIndex;
	UINT    m_uTotalLoopCount;  // The number of loops for which the animation will be played
	UINT    m_uLoopNumber;      // The current animation loop number (e.g. 1 when the animation is first played)
	BOOL    m_fHasLoop;         // Whether the gif has a loop
	UINT    m_cFrames;
	UINT    m_uFrameDisposal;
	UINT    m_uFrameDelay;
	UINT    m_cxGifImage;
	UINT    m_cyGifImage;
	UINT    m_cxGifImagePixel;  // Width of the displayed image in pixel calculated using pixel aspect ratio
	UINT    m_cyGifImagePixel;  // Height of the displayed image in pixel calculated using pixel aspect ratio
	D2D1_RECT_F m_framePosition;
	IWICBitmapDecoder* m_pBitDecoder = nullptr; //GIF 출력 위해 개별적 필요?

	ID2D1Bitmap* m_pRawFrame = nullptr;			// gif 
	ID2D1Bitmap* m_pSavedFrame = nullptr;			// gif
	ID2D1BitmapRenderTarget* m_pFrameComposeRT; //Bitmap Render Target, GIF 출력 위해 개별 소속 필요
	int m_GIFIndex;
};

///[TW] 한 GIF당 이게 다 필요하다. 묶어서 전달하고, 이를 일괄적으로
/// 참조형으로 GIF 관련 함수들이 받게 하는 것이 맞을 것!
