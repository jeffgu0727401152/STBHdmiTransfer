#pragma once

#include "types.h"

class IFontInterface
{
public:
	virtual ~IFontInterface(void) {}

	virtual BOOL LoadFont(
		const char* cFontName)=0;
	virtual void UnloadFont(void)=0;
	virtual BOOL GetTextColorBuffer(
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
		POINT *pEndCharBottomPos)=0;
	virtual void FreeTextBuffer(
		BYTE *pTextBuffer)=0;
};
