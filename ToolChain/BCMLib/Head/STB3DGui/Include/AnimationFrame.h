#pragma once

#include "ImageBuffer.h"
#include "XMLParser.h"
#include "PtrControl.h"
#include "GifDecoder.h"

class CAnimationFrame
{
public:
	CAnimationFrame();
	virtual ~CAnimationFrame();

public:
	void LoadEffectFromXmlNode(
		XMLNode *pNode);
	void LoadEffectFromChildXmlNode(
		XMLNode *pNode,
		const char* cChildNodeName);
	BOOL LoadFromImageFile(
		const char* cImageFileName);
	BOOL LoadFromImageBuffer(
		CImageBuffer *pImageBuf);
	BOOL LoadFromGifFile(
		const char* cGifFileName);
	BOOL LoadFromGifBuffer(
		CBuffer *pGifBuf);
	void Unload();

	int GetWidth();
	int GetHeight();

	// nWidth==0 || nHeight==0 will cancel stretch
	void Stretch(
		int nWidth,
		int nHeight,
		int nDrawMode);
	void RevertRGB();

	int GetAnimationFrameCount();
	int GetCurAnimationFrameIndex();
	void ResetAnimationFrameIndex();
	void GetCurAnimationFrame(
		CImageBuffer* pImageBuffer,
		int* pnDelayTime);
	void DecoderNextAnimationFrame();

private:
	CBaseLock mLock;

	int mImageWidth;
	int mImageHeight;
	int mStretchMode;
	BOOL mRevertRGB;

	BOOL mIsGif;
	CImageBuffer mImageBuffer;
	CGifDecoder mGifDecoder;
};
