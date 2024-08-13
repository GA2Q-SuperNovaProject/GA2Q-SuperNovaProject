#pragma once

#include <windows.h>
#include <iomanip>
#include <d2d1.h>
#include <d2d1_1.h>
#include <d2d1_1helper.h>
#include <d2d1_2.h>
#include <d2d1_3.h>
#include <d2d1_3helper.h>
#include <d2d1effectauthor.h>
#include <d2d1effectauthor_1.h>
#include <d2d1effecthelpers.h>
//#include <d2d1effecthelpers.hlsli>
#include <d2d1effects.h>
#include <d2d1effects_1.h>
#include <d2d1effects_2.h>
#include <d2d1helper.h>
#include <d2d1svg.h>
#include <dcommon.h>
#include <iostream>
#include <string>
#include <sstream>
#include <wincodec.h>
#include <map>
#include <vector>
#include <Wincodec.h>

#include <commdlg.h>

#include <dwrite.h>

// 라이브러리의 링크를 명시적으로 알려줌
#pragma comment(lib,"d2d1.lib")
#pragma comment(lib,"dwrite.lib")

template<class Interface>
inline void SafeRelease(
	Interface** ppInterfaceToRelease)
{
	if (*ppInterfaceToRelease != NULL)
	{
		(*ppInterfaceToRelease)->Release();
		(*ppInterfaceToRelease) = NULL;
	}
}

//GIF와 관련된 SafeRelease를 수행할 예정.
template <typename T>
inline void SafeReleaseGIF(T*& pI)
{
	if (NULL != pI)
	{
		pI->Release();
		pI = NULL;
}
}

#ifndef Assert
#if defined( DEBUG ) || defined( _DEBUG )
#define Assert(b) do {if (!(b)) {OutputDebugStringA("Assert: " #b "\n");}} while(0)
#else
#define Assert(b)
#endif //DEBUG || _DEBUG
#endif

#ifndef HINST_THISCOMPONENT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif


