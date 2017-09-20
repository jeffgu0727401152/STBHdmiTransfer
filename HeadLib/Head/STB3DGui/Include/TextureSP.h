#pragma once

#include "types.h"
#include "ImageBuffer.h"

class CE3DCommand;
class CTextureSP
{
public:
	// for normal buffer
	CTextureSP(
		CE3DCommand *pE3DEngine,
		CImageBuffer *pImageBuffer);

	// for KHR Use
	CTextureSP(
		CE3DCommand *pE3DEngine,
		int nWidth,
		int nHeight,
		BOOL bBGROrder);

	virtual ~CTextureSP();

public:
	void AddRef();
	void Release();
	int GetRefCount();

public:
	void SetTextureData(
		CImageBuffer *pImageBuffer);
	void UpdateTextureData(
		CImageBuffer *pImageBuffer,
		int xStart,
		int yStart,
		int nWidth,
		int nHeight);

	UINT32 GetTextureID();
	int GetWidth();
	int GetHeight();
	int GetBytesPerPixel();

	BYTE *GetKHRImageBuffer();
	void FlushKHRImage();

public:
	void Dump();

private:
	CE3DCommand *mE3DEngine;
	BOOL mUseKHR;

	int mRefCount;
	int mWidth;
	int mHeight;
	int mBytesPerPixel;
	UINT32 mTextureID;
};

#ifdef PC_VERSION
#define DETECT_TEXTURE_LEAK
#endif

#ifdef DETECT_TEXTURE_LEAK
void DeleteAllTexture();
void DumpUnFreeTexture();
#endif
