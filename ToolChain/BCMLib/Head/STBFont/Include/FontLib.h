#pragma once

#include "types.h"
#include "IFontInterface.h"

class CFontLib
{
public:
	CFontLib();
	virtual ~CFontLib();

public:
	BOOL LoadFont(
		const char* cFontName);
	void UnloadFont(void);
	BOOL GetTextColorBuffer(
		const wchar_t* wszString,
		int nFontXSize,
		int nFontYSize,
		UINT32 uFontColor,
		BOOL bAutoMultiLine,
		BOOL bNeedDotIfOutbound,
		int nHorzDirect,
		int& nWidth,
		int& nHeight,
		int nCharXSpace,
		int nCharYSpace,
		BYTE **ppTextAlphaBuffer,
		POINT *pStartCharTopPos,
		POINT *pStartCharBottomPos,
		POINT *pEndCharTopPos,
		POINT *pEndCharBottomPos);
	void FreeTextBuffer(
		BYTE *pTextBuffer);

private:
	IFontInterface *mpFontInterface;
};
