#pragma once

#include "types.h"

#define DRAWMODE_NONE			0x00000000
#define DRAWMODE_HCENTER		0x00000001
#define DRAWMODE_LEFT			0x00000002
#define DRAWMODE_RIGHT			0x00000004
#define DRAWMODE_VCENTER		0x00000010
#define DRAWMODE_TOP			0x00000020
#define DRAWMODE_BOTTOM			0x00000040

BOOL LoadBmpImageFromFile(
	const char *cFileName,
	int *pnWidth,
	int *pnHeight,
	int *pnBitCount,
	BYTE **ppImageData);
BOOL LoadBmpImageFromData(
	const BYTE* pImageBuffer,
	int nBufferLen,
	int *pnWidth,
	int *pnHeight,
	int *pnBitCount,
	BYTE **ppImageData);
void DeleteBmpImageData(
	BYTE *pImageData);

void SaveRgbBufferToBmpFile(
	const BYTE *pRGBBuffer,
	int nImageWidth,
	int nImageHeight,
	int nBitCount,
	const UINT32 *pColorTable,
	int nColorCount,
	const char *cFileName);

void SaveRgbBufferToBmpFileV5(
	const BYTE *pRGBBuffer,
	int nImageWidth,
	int nImageHeight,
	int nBitCount,
	UINT32 uRedMask,
	UINT32 uGreenMask,
	UINT32 uBlueMask,
	UINT32 uAlphaMask,
	const UINT32 *pColorTable,
	int nColorCount,
	const char *cFileName);

void SaveRgb565BufferToBmpFile(
	const BYTE *pRGB565Buffer,
	int nImageWidth,
	int nImageHeight,
	const char *cFileName);

void MemsetBuffer(
	BYTE *pBuffer,
	int xStart,
	int yStart,
	int nWidth,
	int nHeight,
	int nBytePerPixel,
	int nStride,
	BYTE bValue);

void ConvertAlphaToRGB32Buffer(
	const BYTE *pAlphaBuffer,
	int nAlphaStride,
	BYTE *pRGB32Buffer,
	int nRGB32Stride,
	int nWidth,
	int nHeight,
	UINT32 uColor);

void ConvertAlphaToRGB24Buffer(
	const BYTE *pAlphaBuffer,
	int nAlphaStride,
	BYTE *pRGB24Buffer,
	int nRGB24Stride,
	int nWidth,
	int nHeight,
	UINT32 uFrontColor,
	UINT32 uBackColor);

void SetRGB32AlphaRatio(
	BYTE *pRGB32Buffer,
	int nStride,
	int nWidth,
	int nHeight,
	BYTE bAlpha256);

void SetRGB32Alpha(
	BYTE *pRGB32Buffer,
	int nStride,
	int nWidth,
	int nHeight,
	BYTE bAlpha256);

void ConvertRGB24ToRGB32(
	const BYTE *pRGB24Buffer,
	int nRGB24Stride,
	BYTE *pRGB32Buffer,
	int nRGB32Stride,
	int nWidth,
	int nHeight,
	BOOL bRevertRGB);

void ConvertRGB32ToRGB24(
	const BYTE *pRGB32Buffer,
	int nRGB32Stride,
	BYTE *pRGB24Buffer,
	int nRGB24Stride,
	int nWidth,
	int nHeight,
	BOOL bRevertRGB);

void ConvertRGB24ToGray(
	const BYTE* pRGB24,
	int nRGB24Stride,
	BYTE *pGray,
	int nGrayStride,
	int nWidth,
	int nHeight,
	BOOL bRevertRGB);

void ConvertRGB32ToGray(
	const BYTE* pRGB32,
	int nRGB32Stride,
	BYTE *pGray,
	int nGrayStride,
	int nWidth,
	int nHeight,
	BOOL bRevertRGB);

void RevertRGB32ToBGR32(
	BYTE* pRGB32Buffer,
	int nStride,
	int nWidth,
	int nHeight);

void RevertRGB24ToBGR24(
	BYTE* pRGB24Buffer,
	int nStride,
	int nWidth,
	int nHeight);

void RevertBottomUpBuffer(
	BYTE *pBuffer,
	int xStart,
	int yStart,
	int nWidth,
	int nHeight,
	int nBytePerPixel,
	int nStride);

void RotateYUV420Data_90(
	BYTE * pSrc[3],
	BYTE * pDst[3],
	int w,
	int h) ;

void RotateYUV420Data_270(
	BYTE * pSrc[3],
	BYTE * pDst[3],
	int w,
	int h) ;

void RotateYUV420Data_180(
	BYTE * pSrc[3],
	BYTE * pDst[3],
	int w,
	int h) ;

void RotateYUV420SPData_90(
	BYTE * pSrc[2],
	BYTE * pDst[2],
	int w,
	int h) ;

void RotateYUV420SPData_270(
	BYTE * pSrc[2],
	BYTE * pDst[2],
	int w,
	int h) ;

void RotateYUV420SPData_180(
	BYTE * pSrc[2],
	BYTE * pDst[2],
	int w,
	int h) ;

void RotateRGBData270(
	BYTE *pSrc,
	BYTE *pDst,
	int nWidth,
	int nHeight,
	int nBytesPerPixel) ;

void RotateRGBData90(
	BYTE *pSrc,
	BYTE *pDst,
	int nWidth,
	int nHeight,
	int nBytesPerPixel) ;

void RotateRGBData180(
	BYTE *pSrc,
	BYTE *pDst,
	int nWidth,
	int nHeight,
	int nBytesPerPixel) ;

// nBufWidth: width of image buffer
// nBufHeight: height of image buffer
void DrawLineOnBuffer(
	BYTE *pDst,
	POINT ptStart,
	POINT ptEnd,
	int nDstBoundWidth,
	int nDstBoundHeight,
	int nDstStride,
	int nBytesPerPixel,
	int nBolder,
	const void* pColorBuf);

// prcDst - destination bound buffer rect
// prcClip - clip rect of destination
// prcSrc - source buffer rect
// pDstBuffer - destination buffer start address
// pSrcBuffer - source buffer start address
// nDstStride - destination buffer stride(in bytes)
// nSrcStride - source buffer stride(in bytes)
// nBytesPerPixel - Bytes per pixel, 24bpp is 3, 32 bpp is 4, 16bpp is 2, etc.
void StretchBufferOnBuffer(
	BYTE* pDst,
	const RECT& rcCopyTo,
	int   nDstStride,
	const BYTE *pSrc,
	const RECT& rcCopyFrom,
	int   nSrcStride,
	int   nBytesPerPixel);

// prcDst - destination bound buffer rect
// prcClip - clip rect of destination
// prcSrc - source buffer rect
// pDstBuffer - destination buffer start address
// pSrcBuffer - source buffer start address
// nDstStride - destination buffer stride(in bytes)
// nSrcStride - source buffer stride(in bytes)
void AlphaStretchBufferOnBuffer_ARGB(
	BYTE* pDst,
	const RECT& rcCopyTo,
	int   nDstStride,
	const BYTE *pSrc,
	const RECT& rcCopyFrom,
	int   nSrcStride);

void SetAlphaBufferColor_ARGB(
	UINT32 uColor,
	BYTE *pDst,
	const RECT& rcDst,
	int nDstStride,
	const BYTE *pSrc,
	const RECT& rcSrc,
	int nSrcStride);

void DrawColorOnBuffer(
	UINT32 uColor,
	BYTE *pBuffer,
	const RECT *prcRect,
	int nStride);

void DrawBufferOnBuffer(
	BYTE *pDst,
	const RECT& rcCopyTo,
	int nDstStride,
	const BYTE *pSrc,
	const RECT& rcCopyFrom,
	int nSrcStride,
	int nBytesPerPixel);

void DrawBuffer(
	BYTE *pDst,
	RECT rcCopyTo,
	int nDstStride,
	const BYTE *pSrc,
	RECT rcCopyFrom,
	int nSrcStride,
	int nBytesPerPixel,
	BOOL bStretch,
	BOOL bTransparent,
	int nDrawMode);

void GetRectByMode(
	RECT& rcCopyTo,
	RECT& rcCopyFrom,
	BOOL bStretch,
	int nDrawMode);
