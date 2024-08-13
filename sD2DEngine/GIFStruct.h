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
	IWICBitmapDecoder* m_pBitDecoder = nullptr; //GIF ��� ���� ������ �ʿ�?

	ID2D1Bitmap* m_pRawFrame = nullptr;			// gif 
	ID2D1Bitmap* m_pSavedFrame = nullptr;			// gif
	ID2D1BitmapRenderTarget* m_pFrameComposeRT; //Bitmap Render Target, GIF ��� ���� ���� �Ҽ� �ʿ�
	int m_GIFIndex;
};

///[TW] �� GIF�� �̰� �� �ʿ��ϴ�. ��� �����ϰ�, �̸� �ϰ�������
/// ���������� GIF ���� �Լ����� �ް� �ϴ� ���� ���� ��!
