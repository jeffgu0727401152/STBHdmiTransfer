#pragma once

#include "gif.h"


typedef struct tagGif_DecPreviousInfo
{
	int x;
	int y;
	int w;
	int h;
    unsigned char* pImageBuffer;
} Gif_DecPreviousInfo;

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
	void Gif_DecFromImage(
		Gif_Image *pImage);

private:
    Gif_Stream* mGifStream;

    Gif_Colormap *mpGlobalColormap;
    unsigned int mBackColor;
    int mCurImageIndex;
    unsigned char* mpCurImageBuffer;
    int mCurDelayMS;

    uint8_t mPreviousDisposal;
    Gif_DecPreviousInfo mPreviousInfo;
};
