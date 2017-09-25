#pragma once

#include "types.h"
#include "TextureSP.h"
#include "BaseLock.h"
#include "ImageBuffer.h"

// images should be ARGB32

class CE3DCommand;
class CTexture
{
public:
	CTexture();
	virtual ~CTexture();

public:
	void CreateFromImageBuffer(
		CE3DCommand *pE3DEngine,
		CImageBuffer *pImageBuffer);
	void CreateFromKHR(
		CE3DCommand *pE3DEngine,
		int nWidth,
		int nHeight,
		BOOL bBGROrder);

	void Delete();

	void SetTextureData(
		CImageBuffer *pImageBuffer);

	void UpdateTextureData(
		CImageBuffer *pImageBuffer,
		RECT  *prcUpdate=NULL);

	void SetTexture(
		CTexture *pTexture);

public:
	BOOL HasTexture();
	CE3DTexture* GetE3DTexture();
	int  GetWidth();
	int  GetHeight();
	int GetBytesPerPixel();
	int GetRefCount();

	BYTE *GetKHRImageBuffer();
	void FlushKHRImage();

	void Dump();

private:
	void SetTextureSP(
		CTextureSP *pTextureSP);

	// must call this in locked
	CTextureSP* GetTextureSP();

private:
	CTextureSP* mpTextureSP;
	CBaseLock mOperatorLock;
};
