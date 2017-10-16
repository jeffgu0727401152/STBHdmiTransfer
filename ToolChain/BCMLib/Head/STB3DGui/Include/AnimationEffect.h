#pragma once

#include "AnimationFrame.h"
#include "BaseWnd.h"

class CAnimationEffect;

class IAnimationEffectListener
{
public:
	virtual ~IAnimationEffectListener(void) {}

	virtual void OnAnimationFrameChange(
		CAnimationEffect *pEffect,
		CImageBuffer *pImageBuffer,
		int nCurIndex,
		int nTotalIndex,
		UINT64 uUserData)=0;
};

class CAnimationEffect : public IMessageOwner
{
public:
	CAnimationEffect();
	virtual ~CAnimationEffect();

	// interface
public:
	virtual const char* GetEffectName();

	virtual void Create(
		IAnimationEffectListener *pAnimationEffectListener,
		UINT64 uUserData);
	virtual void Delete();

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

	virtual void StartEffect();
	virtual void StopEffect();

	virtual void OnMsg(
		UINT32 uType,
		UINT64 wParam,
		UINT64 lParam);

private:
	void UpdateFrame();

private:
	CAnimationFrame mAnimationFrame;

	IAnimationEffectListener *mpAnimationEffectListener;
	UINT64 mUserData;
};
