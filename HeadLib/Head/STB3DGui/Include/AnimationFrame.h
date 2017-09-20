#pragma once

#include "ImageBuffer.h"
#include "XMLParser.h"
#include "PtrControl.h"

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

	void StretchScale(
		float fScaleX,
		float fScaleY,
		int nDrawMode);
	void Stretch(
		int nWidth,
		int nHeight,
		int nDrawMode);
	void RevertRGB();

	ANIMATIONFRAMEINFO* GetAnimationFrameByIndex(
		int nIndex);
	ANIMATIONFRAMEINFO* GetCurAnimationFrame();
	ANIMATIONFRAMEINFO* GetNextAnimationFrame();
	void ResetAnimationFrameIndex();
	int GetAnimationFrameIndex();
	int GetAnimationFrameCount();

private:
	int mImageWidth;
	int mImageHeight;
	CPtrListCtrl mAnimationFrameInfoList;
	int mAnimationFrameIndex;
};
