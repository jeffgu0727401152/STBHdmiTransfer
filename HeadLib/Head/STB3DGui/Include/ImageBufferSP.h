#pragma once

#include "types.h"
#include "FontLib.h"
#include "BitmapOperator.h"

typedef enum eBUFFER_TYPE
{
	NONE_BUFFER=0,
	DATA_BUFFER,
	BIND_BUFFER,
	TEXT_BUFFER,
	FILEIMAGE_BUFFER
} BUFFER_TYPE;

#define MAKELINECOLOR(a,r,g,b) MAKEUINT32(a,r,g,b)

class CImageBufferSP
{
public:
	CImageBufferSP(
		BOOL bBindBuffer,
		const BYTE* pImgData,
		int nWidth,
		int nHeight,
		int nBytesPerPixel);

	CImageBufferSP(
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

	CImageBufferSP(
		const char *cImgFileName);

	// cTmpFolder: 如果jpeg不支持 buffer方式解码，需要暂存成文件，再解码
	CImageBufferSP(
		const BYTE *pImageBuffer,
		int nBufferLen,
		const char* cTmpFolder);

	virtual ~CImageBufferSP();

public:
	void AddRef();
	void Release();
	int GetRefCount();

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

	void DrawFromBuffer(
		const BYTE *pFromBuffer,
		int nFromWidth,
		int nFromHeight,
		int nFromBytesPerPixel,
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

	int GetWidth() const;
	int GetHeight() const;
	int GetBytesPerPixel() const;
	const BYTE* GetBuffer() const;

private:
	void Delete();
	void SetBuffer(
		BYTE* pImgData,
		int nBufLen,
		int nWidth,
		int nHeight,
		int nBytesPerPixel);

protected:
	int mRefCount;

	BYTE *mpBuffer;
	int mBufLen;
	int mWidth;
	int mHeight;
	int mBytesPerPixel;

	BUFFER_TYPE mBufferType;

	// for font release
	CFontLib *mpFontLib;
};
