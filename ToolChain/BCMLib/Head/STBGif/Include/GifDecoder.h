#pragma once

#include "gif_lib.h"


typedef struct tagGIFBUFINFO
{
	unsigned char *pBuffer;
	int nBufLen;
	int nBufPos;
	int nGifStartPos;
} GIFBUFINFO;

typedef struct tagGIFRECT
{
	int x;
	int y;
	int w;
	int h;
} GIFRECT;

class CGifDecoder
{
public:
	CGifDecoder();
	virtual ~CGifDecoder();

public:
	bool LoadFromGifData(
		const unsigned char* pGifData,
		int nGifDataLength);
	void Unload();

	int GetGifWidth();
	int GetGifHeight();

	int GetFrameCount();
	int GetCurFrameIndex();
	void ResetGifFrameIndex();
	unsigned char* GetGifFrameBuffer();
	void DecNextFrame();
	int GetDelayTimeMS();

private:
	void Gif_Statistics();
	void Gif_DecCopyBuf(
		unsigned char* pSrcBuffer,
		int srcPixelsPerLine,
		int srcX,
		int srcY,
		unsigned char* pDstBuffer,
		int dstPixelsPerLine,
		int dstX,
		int dstY,
		int copyW,
		int copyH);
	void Gif_DecSetColor(
		int x,
		int y,
		int w,
		int h,
		int color);
	void Gif_DecFromImage();

private:
	GifFileType* mpGifFile;
	GIFBUFINFO mGifBufInfo;

	bool mTransparentBackground;
    int mTotalImageCount;
    int mCurImageIndex;
    unsigned char* mpCurImageBuffer;
    unsigned char* mpPrevImageBuffer;
    int mPrevDisposal;
    GIFRECT mPrevRect;
    int mCurDelayMS;
};
