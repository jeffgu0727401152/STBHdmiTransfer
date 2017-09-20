#pragma once

#include "types.h"
#include "BaseLock.h"
#include "ImageBufferSP.h"

#define MAKELINECOLOR(a,r,g,b) MAKEUINT32(a,r,g,b)

class CImageBuffer
{
public:
	CImageBuffer();
	virtual ~CImageBuffer();

public:
	void CreateFromData(
		const BYTE* pImgData,
		int nWidth,
		int nHeight,
		int nBytesPerPixel);

	void BindBuffer(
		BYTE* pImgData,
		int nWidth,
		int nHeight,
		int nBytesPerPixel);

	void CreateFromText(
		CFontLib *pFontLib,
		const wchar_t *wszText,
		int nFontXSize,
		int nFontYSize,
		UINT32 uFontColor,
		BOOL bMultiLine,
		BOOL bNeedDotIfOutbound,
		int nHorzDirect,
		int nBoundWidth,
		int nBoundHeight,
		int nCharXSpace=0,
		int nCharYSpace=0,
		POINT *pStartCharTopPos=NULL,
		POINT *pStartCharBottomPos=NULL,
		POINT *pEndCharTopPos=NULL,
		POINT *pEndCharBottomPos=NULL);

	void CreateFromText(
		CFontLib *pFontLib,
		const char* cText,
		int nFontXSize,
		int nFontYSize,
		UINT32 uFontColor,
		BOOL bMultiLine,
		BOOL bNeedDotIfOutbound,
		int nHorzDirect,
		int nBoundWidth,
		int nBoundHeight,
		int nCharXSpace=0,
		int nCharYSpace=0,
		POINT *pStartCharTopPos=NULL,
		POINT *pStartCharBottomPos=NULL,
		POINT *pEndCharTopPos=NULL,
		POINT *pEndCharBottomPos=NULL);

	void CreateFromImgFile(
		const char *cImgFileName);

	// cTmpFolder: 如果jpeg不支持 buffer方式解码，需要暂存成文件，再解码
	void CreateFromCompressedData(
		const BYTE *pImageBuffer,
		int nBufferLen,
		const char* cTmpFolder);

	void Delete();

	void SetImageBuffer(
		CImageBuffer *pImageBuffer);

public:
	void ModifyImageBufferInfo(
		int nWidth,
		int nHeight,
		int nBytesPerPixel);

	void RevertRGB();

	void RevertBottomUp();

	void RGB24ToRGB32(
		BOOL bRevertRGB);
	void RGB32ToRGB24(
		BOOL bRevertRGB);
	void AlphaToRGB32(
		UINT32 uColor);
	void AlphaToRGB24(
		UINT32 uFrontColor,
		UINT32 uBackColor);

	void StretchScale(
		float fScaleX,
		float fScaleY,
		int nDrawMode);
	void Stretch(
		int nWidth,
		int nHeight,
		int nDrawMode);

	void DrawLine(
		int xStart,
		int yStart,
		int xEnd,
		int yEnd,
		int nBolder,
		const void* pColorBuf);
	void DrawLine(
		POINT ptStart,
		POINT ptEnd,
		int nBolder,
		const void* pColorBuf);

	void DrawRectBolder(
		RECT rcBolder,
		int nBorder,
		const void* pColorBuf);

	void SetByteValue(
		RECT* prcRect,
		BYTE bValue);
	void DrawColor(
		RECT* prcRect,
		UINT32 uColor);
	void SetAlpha(
		RECT* prcRect,
		BYTE bAlpha);
	void SetAlphaRatio(
		RECT* prcRect,
		BYTE bAlphaRatio);

	void DrawFromImageBuffer(
		CImageBuffer *pFrom,
		RECT* prcCopyTo,
		RECT* prcCopyFrom,
		BOOL bStretch=FALSE,
		BOOL bTransparent=FALSE,
		int nDrawMode=DRAWMODE_NONE);

	void DrawToImageBuffer(
		CImageBuffer *pTo,
		RECT* prcCopyTo,
		RECT* prcCopyFrom,
		BOOL bStretch=FALSE,
		BOOL bTransparent=FALSE,
		int nDrawMode=DRAWMODE_NONE);

	void SaveToBmpFile(
		const char* cFileName);
	void SaveToJpegFile(
		const char* cFileName,
		int nQuality);
	void SaveToPngFile(
		const char* cFileName);

	int GetWidth();
	int GetHeight();
	int GetBytesPerPixel();
	const BYTE* GetBuffer();

private:
	void SetImageBufferSP(
		CImageBufferSP *pImageBufferSP);

	// must call this in locked
	CImageBufferSP* GetImageBufferSP();

protected:
	CImageBufferSP* mpImageBufferSP;
	CBaseLock mOperatorLock;
};
