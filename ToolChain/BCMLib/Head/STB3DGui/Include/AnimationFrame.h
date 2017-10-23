#pragma once

#include "ImageBuffer.h"
#include "XMLParser.h"
#include "PtrControl.h"
#include "GifDecoder.h"

typedef struct tagANIMATIONFRAMEINFO
{
	CImageBuffer sImageBuffer;
	int nDelayTime;
}ANIMATIONFRAMEINFO;

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

	void Stretch(
		int nWidth,
		int nHeight,
		int nDrawMode);
	void RevertRGB();

	int GetAnimationFrameCount();
	int GetCurAnimationFrameIndex();
	void ResetAnimationFrameIndex();
	ANIMATIONFRAMEINFO* GetCurAnimationFrame();
	ANIMATIONFRAMEINFO* DecoderNextAnimationFrame();

private:
	int mImageWidth;
	int mImageHeight;
	int mStretchMode;
	BOOL mRevertRGB;

	int mAnimationFrameCount;
	ANIMATIONFRAMEINFO mCurrentFrame;

	BOOL mIsGifImage;
	CGifDecoder mGifDecoder;
};
