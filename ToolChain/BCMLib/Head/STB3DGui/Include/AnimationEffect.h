#pragma once

#include "AnimationFrame.h"
#include "IWndEffect.h"
#include "BaseWnd.h"

class CAnimationEffect;

class IAnimationFrameListener
{
public:
	virtual ~IAnimationFrameListener(void) {}

	virtual void OnAnimationFrameChange(
		CAnimationEffect *pEffect,
		CBaseWnd *pWnd,
		int nCurIndex,
		int nTotalIndex,
		UINT64 uUserData)=0;
};

class CAnimationEffect :
	public IWndEffect,
	public IMessageOwner
{
public:
	CAnimationEffect();
	virtual ~CAnimationEffect();

	// interface
public:
	virtual const char* GetEffectName();

	virtual void Create(
		CBaseWnd *pEffectWnd);
	virtual void Delete();

	virtual void ParserFromXmlNode(
		XMLNode *pNode);

	virtual void StartEffect();
	virtual void StopEffect();

	virtual void OnMsg(
		UINT32 uType,
		UINT64 wParam,
		UINT64 lParam);

public:
	void SetAnimationFrameListener(
		IAnimationFrameListener *pAnimationFrameListener,
		UINT64 uUserData);

private:
	void UpdateFrame();

private:
	CAnimationFrame mAnimationFrame;

	IAnimationFrameListener *mpAnimationFrameListener;
	UINT64 mUserData;

	CBaseWnd *mpEffectWnd;
};
